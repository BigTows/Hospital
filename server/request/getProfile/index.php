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
    $response = new Response("Success","Send data",AuthUtils::getProfile($idUser,$typeUser),0);
} else {
    $response = new Response("You are not authorized", "Please use method %auth%", [], 2);
}
$response->execute();