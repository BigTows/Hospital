<?php
session_start();
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require 'smarty.config.php';
require $root . 'request/class/AuthUtils.php';
require $root . 'request/class/ControlUtils.php';
$smarty->template_dir = $root . 'application/template/';
$data = [
    "header" => [
        "main" => [
            "Главная" , "/hospital/server/"],
        "doctors" => [
            "Врачи" , ""],
        "help" => [
            "Помощь" , "help"]
    ],
    "profile" => null
];


$pages = [
    "main" => "index.tpl",
    "recover" => "recover.tpl",
    "help" => "help.tpl"
];

$pagesWithAccess = [
    "profile" => "profile.tpl",
    "exit" => "exit.tpl",
    "history" => "history.tpl",
    "record" => "record.tpl"
];

function getPage($template)
{
    global $pages;
    global $smarty;
    global $data;
    global $pagesWithAccess;
    //Check for undefined Template
    $template = $template['tmp'] ?? "main";
    $userID = AuthUtils::isAuth(session_id());
    if (($pagesWithAccess[$template] ?? false) && $userID > 0) {
        getDataForPage($template, $userID);
        $data["page"] = $template;
        $template = $pagesWithAccess[$template];
    } else if ($pages[$template] ?? false) {
        $data["page"] = $template;
        $template = $pages[$template];
    } else {
        $data["page"] = "main";
        $template = $pages["main"];
    }
    if ($userID > 0)
        $data["profile"] = json_decode(json_encode(AuthUtils::getProfile($userID)), true);
    $smarty->assign("data", $data);
    return $template;
}

function getDataForPage($page, $idUser)
{
    global $data;
    switch ($page) {
        case "exit": {
            AuthUtils::logout(session_id());
            break;
        }
        case "history": {
            $data["history"] = AuthUtils::getHistory($idUser);
            break;
        }
        case "record": {
            $data["record"] = ControlUtils::getListDoctors(session_id());
        }
        case "profile":{
            $data["records"] = json_decode(json_encode(ControlUtils::getRecordsUser(session_id(),true,null)),true);
        }
    }
}