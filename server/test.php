<?php
session_start();
/**
 * Created by PhpStorm.
 * File: test.php.
 * Created: bigtows.
 * Created date: 29/05/2017  20:46
 * Description:
 */
?>
<div id="resp"></div>
<script>
    var xhr = new XMLHttpRequest();
    xhr.open("POST","request/getProfile/");
    var data = new FormData();
    data.append("token","e2euqsurg23nr5smgl1f4tpl144");
    data.append("type_user","2");
    xhr.onreadystatechange = function () {
        if (this.status===200 && this.readyState===4)
        document.getElementById("resp").innerHTML = this.responseText;
    };
    xhr.send(data)
</script>
