<?php
/**
 * Created by PhpStorm.
 * User: bigtows
 * Date: 26/05/2017
 * Time: 23:28
 */
session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/Response.php";
$requestFolder = $root . "application/request/";
require_once $requestFolder . "doctors/index.php";
require_once $requestFolder . "auth/AuthUtils.php";

/**
 * @api {post}
 */
if (isset($_POST['getDoctors'])) {
    $response = new Response("");
} else {
    $response = new Response("Method not founded", "", [], 1);
}
$response->execute();