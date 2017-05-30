<?php
session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/Response.php";
require_once $root . "application/class/constant/Constant.php";
require_once "../class/AuthUtils.php";
$token = $_POST['token'] ?? null;
$typeUser = $_POST['type_user'] ?? 1;
$idUser = AuthUtils::isAuth($token,$typeUser);
if ($idUser!=-1) {
    global $DBConnect;
    if ($typeUser==Constant::DOCTOR_TYPE){
        $sqlQuery  = "SELECT first_name,second_name,middle_name,sex,phone,date,email FROM ".Constant::DOCTOR_TABLE." WHERE id_doctor=:id";
    }else{
        $sqlQuery  = "SELECT first_name,second_name,middle_name,sex,phone,date,email FROM ".Constant::USER_TABLE." WHERE id_user=:id";
    }
    $stmt = $DBConnect->sendQuery($sqlQuery,["id"=>$idUser]);
    $response = new Response("Success","Send data",$stmt->fetchAll(PDO::FETCH_OBJ),0);
} else {
    $response = new Response("You are not authorized", "Please use method %auth%", [], 2);
}
$response->execute();