<?php
/**
 * Created by PhpStorm.
 * User: bigtows
 * Date: 26/05/2017
 * Time: 23:28
 */
$root = $_SERVER['DOCUMENT_ROOT']."/hospital/server/";
require_once $root."application/config/config.php";
$requestFolder=$root."application/request/";
require_once $requestFolder."doctors/index.php";
require_once $requestFolder."auth/index.php";

/**
 * @api {post}
 */
if ($_POST['AuthUtils']) {
    $userName =  $_POST['name'] ?? null;
    $password =  hash($_POST['password'],'sha1') ?? null;
    $typeUser = $_POST['type_user'] ?? 1;
    AuthUtils::isGoodInputParameters($typeUser,$userName,$password);

}else if ($_POST['getDoctors']){

}