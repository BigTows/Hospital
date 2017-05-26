<?php
/**
 * Created by PhpStorm.
 * User: bigtows
 * Date: 26/05/2017
 * Time: 23:32
 * Here Settings Project
 */
$root = $_SERVER['DOCUMENT_ROOT']."/hospital/server/";
require_once $root."application/class/DataBase.php";
/**
 * The data from the database
 */
$nameDataBase = "Hospital"; //DataBase name
$userDataBase = "UserName"; //User for connect to DataBase
$passwordDataBase = "PasswordName"; //Password from User
$driver = "mysql"; //The driver used to connect to the DataBase
$locationAddress = "localhost"; //Location Address
/**
 *
 */
$dns = $driver.":dbname=".$nameDataBase.";host=".$locationAddress;

$DBConnect = new DataBase($dns,$userDataBase,$passwordDataBase);