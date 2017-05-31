<?php
session_start();
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require 'smarty.config.php';
require $root.'request/class/AuthUtils.php';
$smarty->template_dir = $root . 'application/template/';
$data = [
    "profile"=>null,
    "e"=>2
];

$pages = [
  "main"=>"index.tpl"
];

function getPage($template){
    global $pages;
    global $smarty;
    global $data;
    //Check for undefined Template
    $template = $template['tmp'] ?? "main";

    //Get template name
    $template = $pages[$template] ?? $pages["main"];
    $userID = AuthUtils::isAuth(session_id());
    if ($userID!=-1){
       $data["profile"]=json_decode(json_encode(AuthUtils::getProfile($userID)),true);
    }
    $smarty->assign("data",$data);
    return $template;
}