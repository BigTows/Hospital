<?php

/**
 * Created by PhpStorm.
 * File: ControlUtils.php.
 * Created: bigtows.
 * Created date: 08/06/2017  18:13
 * Description:
 */

$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/constant/Constant.php";
require_once 'AuthUtils.php';

class ControlUtils
{

    public static function getRecords($token, $period = false, $date = null): array
    {
        $doctorID = AuthUtils::getIDUserFromToken($token, 2);
        if ($doctorID > 0) {
            $sqlQuery = "SELECT * FROM " . Constant::RECORD_VIEW . " WHERE id_doctor=:id AND ";
            global $DBConnect;
            if ($date == null) {
                $sqlQuery .= "date(date)>=date(NOW()) ORDER BY date";
                $stmt = $DBConnect->sendQuery($sqlQuery, [
                    "id" => $doctorID
                ]);
            } else {

                $sqlQuery .= "date(date)";
                if ($period) $sqlQuery .= ">";
                $sqlQuery .= "=date(:date) ORDER BY date";
                $stmt = $DBConnect->sendQuery($sqlQuery, [
                    "id" => $doctorID,
                    "date" => $date
                ]);
            }
            if ($DBConnect->hasError()) {
                return array();
            } else {
                return $stmt->fetchAll(PDO::FETCH_OBJ);
            }
        }
        return array();

    }

    public static function getRecordsUser($token, $period = false, $date = null): array
    {
        $doctorID = AuthUtils::getIDUserFromToken($token, 1);
        if ($doctorID > 0) {
            $sqlQuery = "SELECT * FROM " . Constant::RECORD_VIEW . " WHERE id_user=:id AND ";
            global $DBConnect;
            if ($date == null) {
                $sqlQuery .= "date(date)>=date(NOW())";
                $stmt = $DBConnect->sendQuery($sqlQuery, [
                    "id" => $doctorID
                ]);
            } else {

                $sqlQuery .= "date(date)";
                if ($period) $sqlQuery .= ">";
                $sqlQuery .= "=date(:date)";
                $stmt = $DBConnect->sendQuery($sqlQuery, [
                    "id" => $doctorID,
                    "date" => $date
                ]);
            }
            if ($DBConnect->hasError()) {
                return array();
            } else {
                return $stmt->fetchAll(PDO::FETCH_OBJ);
            }
        }
        return array();

    }

    public static function addHistory($token, $idUser, $text): bool
    {
        $idDoctor = AuthUtils::getIDUserFromToken($token, 2);
        if ($idDoctor > 0) {
            $sqlQuery = "INSERT INTO `history_user` (`id_user`, `id_doctor`, `text`,`date`) VALUES (:idUser,:idDoctor,:text,CURRENT_TIMESTAMP())";
            global $DBConnect;
            $stmt = $DBConnect->sendQuery($sqlQuery, [
                "idUser" => $idUser,
                "idDoctor" => $idDoctor,
                "text" => $text]);
            if ($DBConnect->hasError()) {
                return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    public static function getHistory($idUser, $count = 5)
    {
        $sqlQuery = "SELECT * FROM `history_user` WHERE id_user=:id LIMIT :count";
        global $DBConnect;
        $stmt = $DBConnect->sendQuery($sqlQuery, [
            "id" => $idUser,
            "count" => $count], PDO::PARAM_INT
        );
        if ($DBConnect->hasError()) {
            echo json_encode($stmt->errorInfo());
            return [];
        } else {
            return json_decode(json_encode($stmt->fetchAll(PDO::FETCH_OBJ)));
        }
    }

    public static function getListDoctors($token)
    {
        if (AuthUtils::isAuth($token)) {

            global $DBConnect;
            $stmt = $DBConnect->sendQuery("SELECT * FROM Doctors");
            if ($DBConnect->hasError()) {
                return null;
            } else {
                $array = [];
                $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);
                foreach ($rows as $row) {
                    if (isset($array[$row['name']])) {
                        array_push($array[$row['name']], $row);
                    } else {
                        $array[$row['name']][0] = $row;
                    }
                }
                return $array;
            }
        } else {
            return null;
        }
    }

    public static function getFreeTimeInDay($idDoctor, $date)
    {
        global $DBConnect;
        $stmt = $DBConnect->sendQuery("SELECT HOUR (date) as h,MINUTE(date) as m FROM `record` WHERE Date(:date)=Date(date) AND id_doctor = :id",
            ["date" => $date,
                "id" => $idDoctor]);
        if ($DBConnect->hasError()) {
            return null;
        } else {
            return $stmt->fetchAll(PDO::FETCH_OBJ);
        }
    }

    public static function recordUser($idUser, $idDoctor, $date)
    {
        global $DBConnect;
        $st = $DBConnect->sendQuery("INSERT INTO `record`(`id_record`, `id_user`, `id_doctor`, `date`) VALUES (NULL,:idUser,:idDoc, DATE_FORMAT(:date,'%Y-%m-%d %H:%i'))", [
            "idUser" => $idUser,
            "idDoc" => $idDoctor,
            "date" => $date
        ]);
        if ($DBConnect->hasError()) {
            echo json_encode($st->errorInfo());
            return false;
        } else {
            return true;
        }
    }

}