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

    public static function getRecords($token,$date=null):array {
        $doctorID  = AuthUtils::getIDUserFromToken($token,2);
        if ($doctorID>0){
            $sqlQuery ="SELECT * FROM ".Constant::RECORD_VIEW." WHERE id_doctor=:id AND ";
            global $DBConnect;
            if ($date==null){
                $sqlQuery.="date(date)>=date(NOW())";
                $stmt = $DBConnect->sendQuery($sqlQuery,[
                    "id"=>$doctorID
                ]);
            }else{
                $sqlQuery.="date(date)=date(:date)";
                $stmt = $DBConnect->sendQuery($sqlQuery,[
                    "id"=>$doctorID,
                    "date"=>$date
                ]);
            }
            if ($DBConnect->hasError()){
                return array();
            }else{
                return $stmt->fetchAll(PDO::FETCH_OBJ);
            }
        }
        return array();

    }

    public static function addRecord($token,$idUser,$text):bool{
        $idDoctor  = AuthUtils::getIDUserFromToken($token,2);
        if ($idDoctor>0){
            $sqlQuery = "INSERT INTO `record`(`id_user`, `id_doctor`, `date`) VALUES (:idUser,:idDoctor,CURRENT_TIMESTAMP())";
            global $DBConnect;
            $stmt = $DBConnect->sendQuery($sqlQuery,[
                "idUser"=>$idUser,
                "idDoctor"=>$idDoctor]);
            if ($DBConnect->hasError()){
                return false;
            }else{
                return true;
            }
        }else{
            return false;
        }
    }

    public static function getListDoctors($token){
        if (AuthUtils::isAuth($token)){

            global $DBConnect;
            $stmt = $DBConnect->sendQuery("SELECT * FROM Doctors");
            if ($DBConnect->hasError()){
                return null;
            }else{
                return $stmt->fetchAll();
            }
        }else{
            return null;
        }
    }

}