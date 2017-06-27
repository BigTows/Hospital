<?php
session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/Response.php";
require_once $root . "application/class/constant/Constant.php";
require_once "../class/ControlUtils.php";
$token = $_POST['token'] ?? null;
$idUser = AuthUtils::isAuth($token,1);
if ($idUser!=-1) {
    $response = new Response("Success","Send data",ControlUtils::getRecordsUser($token,1),0);
} else {
    $response = new Response("You are not authorized", "Please use method %auth%", [], 2);
}
$response->execute();