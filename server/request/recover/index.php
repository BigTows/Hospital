<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);
session_start();
$root = $_SERVER['DOCUMENT_ROOT'] . "/hospital/server/";
require_once $root . "application/config/config.php";
require_once $root . "application/class/Response.php";
require_once "../class/AuthUtils.php";
$userName = $_POST['name'] ?? null;
$typeUser = $_POST['type_user'] ?? 1;
$code = $_POST['code'] ?? null;
$stateRecover = $_POST['state_recover'] ?? 1;
if ($stateRecover == 1) {
    if (AuthUtils::isGoodId(1, $userName)) {
        global $DBConnect;
        $rand = rand(10000000, 99999999);
        $stmt = $DBConnect->sendQuery("INSERT INTO recover_code VALUES(:id,:rand)", [
            "id" => $userName,
            "rand" => $rand
        ]);
        if ($DBConnect->hasError()) {
            $response = new Response("Error", "", "", 2);
        } else {
            $stmt = $DBConnect->sendQuery("SELECT phone FROM user WHERE id_user = :id", [
                "id" => $userName
            ]);
            $phone = $stmt->fetch()["phone"];
            $curl = curl_init();
            curl_setopt($curl, CURLOPT_URL, 'https://smsimple.ru/http_send.php?user=BigTows&or_id=0&pass=DERmerty98&phone='.$phone.'&message=Ваш код: ' .$rand);
            curl_setopt($curl, CURLOPT_RETURNTRANSFER,true);
            $out = curl_exec($curl);
            curl_close($curl);
            $response = new Response("Success", "Send message to " . $phone, "", 0);
        }
    } else {
        $response = new Response("Error", "", [], 2);
    }
} else if ($stateRecover == 2) {
    global $DBConnect;
    if ($code != null) {
        $stmt = $DBConnect->sendQuery("SELECT id_user,code FROM recover_code WHERE code=:code", ["code" => $code]);
        if ($DBConnect->hasError()) {
            $response = new Response("Error", "", "", 2);
        } else {
            $row = $stmt->fetch();
            $codeDB = $row["code"];

            if ($code == $codeDB) {
                $userID = $row["id_user"];
                $stmt = $DBConnect->sendQuery("DELETE FROM recover_code WHERE code=:code AND id_user=:id", ["code" => $code, "id" => $userID]);

                $stmt = $DBConnect->sendQuery("SELECT phone FROM user WHERE id_user = :id", [
                    "id" => $userID
                ]);
                $phone = $stmt->fetch()["phone"];
                $password = '';

                $desired_length = rand(8, 12);

                for ($length = 0; $length < $desired_length; $length++) {
                    $password .= chr(rand(65, 122));
                }
                $DBConnect->sendQuery("UPDATE user SET password=:pass WHERE id_user=:id", [
                    "pass" => hash('sha256', $password),
                    "id" => $userID
                ]);
                //@TODO SEND New password
                $curl = curl_init();
                curl_setopt($curl, CURLOPT_URL, "https://smsimple.ru/http_send.php?user=BigTows&or_id=0&pass=DERmerty98&phone=" . $phone . "&message=Ваш новый пароль: " . $password);
                curl_setopt($curl, CURLOPT_RETURNTRANSFER,true);
                $out = curl_exec($curl);
                curl_close($curl);
                //http_get("https://smsimple.ru/http_send.php?user=BigTows&or_id=0&pass=DERmerty98&phone=" . $phone . "&message=Ваш новый пароль: " . $password);
                //http_get("https://gate.smsaero.ru/send/?user=gasfull@mail.ru&password=4qtYj8feNiv7hsSKwkTADodaZ7Iu&to=".$phone."&text=Ваш новый пароль ".$password."&from=news");
                $response = new Response("Success", "", "", 0);
            } else {
                $response = new Response("Error", "Bad Code", "", 2);
            }
        }
    } else {
        $response = new Response("Error", "code is NULL", "", 2);
    }
}
$response->execute();