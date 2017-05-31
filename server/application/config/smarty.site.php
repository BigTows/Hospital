<?php
require 'smarty.config.php';
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
$smarty->template_dir = $root . 'application/template/';
$smarty->display("index.tpl");