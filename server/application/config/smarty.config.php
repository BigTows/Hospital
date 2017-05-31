<?php
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require $root . 'application/lib/Smarty.class.php';
$smarty = new Smarty();
$smarty->compile_dir = $root . 'application/template/ready';
$smarty->config_dir = $root . 'application/config';
$smarty->cache_dir = $root . 'application/template/cache';
