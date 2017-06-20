<?php
/**
 * Created by PhpStorm.
 * File: index.php.
 * Created: bigtows.
 * Created date: 08/06/2017  18:05
 * Description:
 */
session_start();
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/Response.php";
require_once "../class/AuthUtils.php";
require_once "../class/ControlUtils.php";
$token=$_POST['token'] ?? session_id();
$date = $_POST['date'] ?? null;
$idDoctor =$_POST['id_doctor'] ?? false;
if (AuthUtils::isAuth($token, 1)>0) {
    $response = new Response("Success", "You is auth", ControlUtils::recordUser(AuthUtils::isAuth($token, 1),$idDoctor,$date), 0);
} else {
    $response = new Response("Bad input data", "", [], 2);
}
$response->execute();