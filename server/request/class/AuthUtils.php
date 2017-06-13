<?php
/**
 * Created by PhpStorm.
 * File: Auth.php.
 * Created: bigtows.
 * Created date: 29/05/2017  20:11
 * Description:
 */
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/constant/Constant.php";

/**
 * Class AuthUtils
 */
class AuthUtils
{
    /**
     * @param $typeUser
     * @param $userName
     * @param $password
     * @return bool
     */
    public static function isGoodInputParameters($typeUser, $userName, $password): bool
    {
        if (!self::checkInputData($userName, $password)) return false;
        global $DBConnect;
        $password = hash("sha256", $password);
        $sqlQuery = "SELECT COUNT(*) as countUsers FROM ";
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = $sqlQuery . Constant::DOCTOR_TABLE . " WHERE login = :id AND password=:password";
        } else {
            $sqlQuery = $sqlQuery . Constant::USER_TABLE . " WHERE id_user = :id AND password=:password";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery, [
            "id" => $userName,
            "password" => $password
        ]);
        return !$DBConnect->hasError() && $stmt->fetch()['countUsers'];
    }


    /**
     * @param $typeUser
     * @param $userName
     * @return bool
     */
    public static function isGoodId($typeUser, $userName): bool
    {
        if (!self::checkInputData($userName)) return false;
        global $DBConnect;
        $sqlQuery = "SELECT COUNT(*) as countUsers FROM ";
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = $sqlQuery . Constant::DOCTOR_TABLE . " WHERE login = :id";
        } else {
            $sqlQuery = $sqlQuery . Constant::USER_TABLE . " WHERE id_user = :id";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery, [
            "id" => $userName,
        ]);
        return !$DBConnect->hasError() && $stmt->fetch()['countUsers'];
    }

    /**
     * @param $token
     * @param int $typeUser
     * @return int
     */
    public static function isAuth($token, $typeUser = 1): int
    {
        if ($token==null) return -1;
        global $DBConnect;
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = "SELECT id_doctor as ID FROM " . Constant::SESSION_DOCTOR_TABLE . " WHERE token=:token";
        } else {
            $sqlQuery = "SELECT id_user as ID FROM " . Constant::SESSION_USER_TABLE . " WHERE token=:token";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery, [
            "token" => $token
        ]);
        $id = $stmt->fetch()['ID'];
        return $id ? intval($id) : -1;
    }

    /**
     * @param $typeUser
     * @param $userName
     * @return bool
     */
    public static function authUser($typeUser, $userName): bool
    {
        if (!self::checkInputData($userName)) return false;
        global $DBConnect;
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $userName = self::getIDUserFromName($typeUser, $userName);
            if ($userName == -1) return false;
            $sqlQuery = "INSERT INTO " . Constant::SESSION_DOCTOR_TABLE . " VALUES (:id,:token,CURRENT_TIMESTAMP()) ON DUPLICATE KEY UPDATE token=:token,date=CURRENT_TIMESTAMP();";
        } else {
            $sqlQuery = "INSERT INTO " . Constant::SESSION_USER_TABLE . " VALUES (:id,:token,CURRENT_TIMESTAMP()) ON DUPLICATE KEY UPDATE token=:token,date=CURRENT_TIMESTAMP();";
        }

        $DBConnect->sendQuery($sqlQuery, [
            "id" => $userName,
            "token" => session_id()
        ]);
        return !$DBConnect->hasError() ? true : false;
    }


    /**
     * @param $typeUser
     * @param $userName
     * @return int
     */
    public static function getIDUserFromName($typeUser, $userName): int
    {
        if (!self::checkInputData($typeUser, $userName)) return -1;
        global $DBConnect;
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = "SELECT id_doctor as idU FROM " . Constant::DOCTOR_TABLE . " WHERE login = :id";
        } else {
            $sqlQuery = "SELECT id_user as idU FROM " . Constant::USER_TABLE . " WHERE id_user = :id";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery, [
            "id" => $userName
        ]);
        $id = $stmt->fetch()['idU'];
        return $id ? intval($id) : -1;

    }


    public static function getIDUserFromToken($token,$typeUser = 1):int{

        if (!self::checkInputData($typeUser, $token)) return -1;
        global $DBConnect;
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = "SELECT id_doctor as idU FROM " . Constant::SESSION_DOCTOR_TABLE . " WHERE token = :token";
        } else {
            $sqlQuery = "SELECT id_user as idU FROM " . Constant::SESSION_USER_TABLE . " WHERE token = :token";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery, [
            "token" => $token
        ]);
        $id = $stmt->fetch()['idU'];
        return $id ? intval($id) : -1;

    }


    /**
     * @param $userID
     * @param int $typeUser
     * @return mixed
     */
    public static function getProfile($userID, $typeUser = 1)
    {
        global $DBConnect;
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = "SELECT first_name,second_name,middle_name,sex,phone,date,email,photo FROM " . Constant::DOCTOR_TABLE . " WHERE id_doctor=:id";
        } else {
            $sqlQuery = "SELECT id_user as polis,first_name,second_name,middle_name,sex,phone,date,email,photo FROM " . Constant::USER_TABLE . " WHERE id_user=:id";
        }
        return $DBConnect->sendQuery($sqlQuery, ["id" => $userID])->fetch(PDO::FETCH_OBJ);
    }

    /**
     * @param $userID
     * @return array
     */
    public static function getHistory($userID)
    {
        global $DBConnect;
        /**
         * @TODO Fix 0,1,2 index on Array
         */
        $array = [];
        $index = 0;
        $sqlQuery = "SELECT Date(history_user.date) as date,Time(history_user.date) as time,history_user.text, doctor.first_name,doctor.second_name,doctor.middle_name,
        post.name as namePost
 FROM history_user
        INNER JOIN doctor on doctor.id_doctor = history_user.id_doctor
          INNER JOIN appointments on appointments.id_doctor = doctor.id_doctor
          INNER JOIN post on post.id_post = appointments.id_post
          WHERE id_user=:id ORDER by history_user.date DESC";
        $stat = $DBConnect->sendQuery($sqlQuery, ["id" => $userID]);
        while ($row = $stat->fetch()) {
            if (isset($array[$row['date']])){
                $array[$row['date']]+= [count($array[$row['date']])=>json_decode(json_encode($row),true)];
            }else{
                $array[$row['date']]=[json_decode(json_encode($row),true)];
            }
            $index++;
        }
        json_decode(json_encode($array),true);
        //echo json_encode($array,JSON_UNESCAPED_UNICODE);
        return $array;
    }

    /**
     * @param $token
     * @param int $typeUser
     */
    public static function logout($token, $typeUser = 1)
    {
        global $DBConnect;
        if ($typeUser == Constant::DOCTOR_TYPE) {
            $sqlQuery = "DELETE FROM " . Constant::SESSION_DOCTOR_TABLE . " WHERE token=:token";
        } else {
            $sqlQuery = "DELETE FROM " . Constant::SESSION_USER_TABLE . " WHERE token=:token";
        }
        $DBConnect->sendQuery($sqlQuery, ["token" => $token]);
    }

    /**
     * @param array ...$data
     * @return bool
     */
    private static function checkInputData(... $data): bool
    {
        foreach ($data as $item) {
            if ($item == null) return false;
        }
        return true;
    }
}