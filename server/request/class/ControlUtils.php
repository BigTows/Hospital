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

    public static function getRecords($token){
        $userID  = AuthUtils::getIDUserFromToken($token,2);
        if ($userID<1){

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