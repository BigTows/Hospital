<?php
/**
 * Created by PhpStorm.
 * File: Auth.php.
 * Created: bigtows.
 * Created date: 29/05/2017  20:11
 * Description:
 */
$root = $_SERVER['DOCUMENT_ROOT']."/hospital/server/";
require_once $root."application/config/config.php";
require_once $root."application/class/constant/Constant.php";

/**
 * Class AuthUtils
 */
class AuthUtils{
    /**
     * @param $typeUser
     * @param $userName
     * @param $password
     * @return bool
     */
    public static function isGoodInputParameters($typeUser, $userName, $password):bool {
        if (!self::checkInputData($userName,$password)) return false;
        global $DBConnect;
        $password = hash("sha256",$password);
        $sqlQuery ="SELECT COUNT(*) as countUsers FROM ";
        if ($typeUser==Constant::DOCTOR_TYPE) {
            $sqlQuery=$sqlQuery.Constant::DOCTOR_TABLE." WHERE login = :id AND password=:password";
        }else{
            $sqlQuery=$sqlQuery.Constant::USER_TABLE." WHERE id_user = :id AND password=:password";
        }
       $stmt = $DBConnect->sendQuery($sqlQuery,[
           "id"=>$userName,
           "password"=>$password
       ]);
       return  !$DBConnect->hasError() && $stmt->fetch()['countUsers'];
    }

    /**
     * @param $token
     * @param int $typeUser
     * @return int
     */
    public static function isAuth($token, $typeUser=1):int{
        global $DBConnect;
        if ($typeUser==Constant::DOCTOR_TYPE){
            $sqlQuery = "SELECT id_doctor as ID FROM ".Constant::SESSION_DOCTOR_TABLE." WHERE token=:token";
        }else{
            $sqlQuery = "SELECT id_user as ID FROM ".Constant::SESSION_USER_TABLE." WHERE token=:token";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery,[
            "token"=>$token
        ]);
        $id = $stmt->fetch()['ID'];
        return $id ? intval($id) : -1;
    }

    /**
     * @param $typeUser
     * @param $userName
     * @return bool
     */
    public static function authUser($typeUser, $userName):bool {
        if (!self::checkInputData($userName)) return false;
        global $DBConnect;
        if ($typeUser==Constant::DOCTOR_TYPE) {
            $userName = self::getIDUser($typeUser,$userName);
            if ($userName==-1) return false;
            $sqlQuery = "INSERT INTO ".Constant::SESSION_DOCTOR_TABLE." VALUES (:id,:token,CURRENT_TIMESTAMP()) ON DUPLICATE KEY UPDATE token=:token,date=CURRENT_TIMESTAMP();";
        }else{
            $sqlQuery = "INSERT INTO ".Constant::SESSION_USER_TABLE." VALUES (:id,:token,CURRENT_TIMESTAMP()) ON DUPLICATE KEY UPDATE token=:token,date=CURRENT_TIMESTAMP();";
        }

        $DBConnect->sendQuery($sqlQuery,[
            "id"=>$userName,
            "token"=>session_id()
        ]);
        return  !$DBConnect->hasError() ? true: false;
    }


    /**
     * @param $typeUser
     * @param $userName
     * @return int
     */
    public static function getIDUser($typeUser, $userName):int{
        if (!self::checkInputData($typeUser,$userName)) return -1;
        global $DBConnect;
        if ($typeUser==Constant::DOCTOR_TYPE) {
            $sqlQuery="SELECT id_doctor as idU FROM ".Constant::DOCTOR_TABLE." WHERE login = :id";
        }else{
            $sqlQuery="SELECT id_user as idU FROM ".Constant::USER_TABLE." WHERE id_user = :id";
        }
        $stmt = $DBConnect->sendQuery($sqlQuery,[
            "id"=>$userName
        ]);
        $id = $stmt->fetch()['idU'];
        return $id ? intval($id) : -1;

    }

    public static function getProfile($userID,$typeUser=1) {
        global $DBConnect;
        if ($typeUser==Constant::DOCTOR_TYPE){
            $sqlQuery  = "SELECT first_name,second_name,middle_name,sex,phone,date,email,photo FROM ".Constant::DOCTOR_TABLE." WHERE id_doctor=:id";
        }else{
            $sqlQuery  = "SELECT id_user as polis,first_name,second_name,middle_name,sex,phone,date,email,photo FROM ".Constant::USER_TABLE." WHERE id_user=:id";
        }
        return $DBConnect->sendQuery($sqlQuery,["id"=>$userID])->fetch(PDO::FETCH_OBJ);
    }

    public static function logout($token,$typeUser=1){
        global $DBConnect;
        if ($typeUser==Constant::DOCTOR_TYPE){
            $sqlQuery  = "DELETE FROM ".Constant::SESSION_DOCTOR_TABLE." WHERE token=:token";
        }else{
            $sqlQuery  = "DELETE FROM ".Constant::SESSION_USER_TABLE." WHERE token=:token";
        }
        $DBConnect->sendQuery($sqlQuery,["token"=>$token]);
    }

    /**
     * @param array ...$data
     * @return bool
     */
    private static function checkInputData(... $data):bool {
        foreach ($data as $item){
            if ($item==null) return false;
        }
        return true;
    }
}