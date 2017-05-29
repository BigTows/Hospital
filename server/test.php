<?php
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
    xhr.open("POST","application/request/index.php");
    var data = new FormData();
    data.append("auth","");
    data.append("name","doctor_1");
    data.append("password","test");
    data.append("type_user","2");
    xhr.onreadystatechange = function () {
        if (this.status===200 && this.readyState===4)
        document.getElementById("resp").innerHTML = this.responseText;
    };
    xhr.send(data)
</script>
