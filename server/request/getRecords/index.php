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
$userName = $_POST['name'] ?? null;
$password = $_POST['password'] ?? null;
$typeUser = $_POST['type_user'] ?? 1;
if (AuthUtils::isGoodInputParameters($typeUser, $userName, $password)) {
    if (AuthUtils::authUser($typeUser, $userName)) {
        $response = new Response("Success", "You is auth", ["token" => session_id()], 0);
    } else {
        $response = new Response("Bad input data", "", [], 2);
    }
} else {
    $response = new Response("Bad input data", "", [], 2);
}
$response->execute();