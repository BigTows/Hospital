<?php
session_start();
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require 'smarty.config.php';
require $root.'request/class/AuthUtils.php';
$smarty->template_dir = $root . 'application/template/';
$data = [
    "profile"=>null
];

$pages = [
  "main"=>"index.tpl",
    "profile"=>"profile.tpl",
    "exit"=>"exit.tpl",
    "history"=>"history.tpl",
    "recover"=>"recover.tpl"
];


function getPage($template){
    global $pages;
    global $smarty;
    global $data;
    //Check for undefined Template
    $template = $template['tmp'] ?? "main";
    $userID = AuthUtils::isAuth(session_id());
    actionOnPage($template,$userID);
    if ($userID!=-1){
        $data["profile"]=json_decode(json_encode(AuthUtils::getProfile($userID)),true);
    }
    //Get template name
    $template = $pages[$template] ?? $pages["main"];
    $smarty->assign("data",$data);
    return $template;
}

function actionOnPage($page,$idUser){
    global $data;
    switch ($page){
        case "exit":{
            AuthUtils::logout(session_id());
            break;
        }
        case "history":{
            $data["history"]=AuthUtils::getHistory($idUser);
            break;
        }
    }
}