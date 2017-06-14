<?php
/**
 * Created by PhpStorm.
 * File: index.php.
 * Created: bigtows.
 * Created date: 14/06/2017  20:36
 * Description:
 */
session_start();
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/Response.php";
require_once "../class/AuthUtils.php";
require_once "../class/ControlUtils.php";
$token=$_POST['token'] ?? null;
$idUser = $_POST['id_user'] ?? null;
$text = $_POST['text'] ?? null;
if (AuthUtils::isAuth($token, 2)>0) {
    $response = new Response("Success", "You is auth", ControlUtils::getRecords($token,$date), 0);
} else {
    $response = new Response("Bad input data", "", [], 2);
}
$response->execute();