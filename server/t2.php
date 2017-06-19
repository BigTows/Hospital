<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);
?>

<script>
    var xhr = new XMLHttpRequest();
    var data = new FormData();
    data.append("token","155i095h6hru0mtc5vael4mi62");
    data.append("id_user","1234123412341234");
    xhr.open("POST","request/getHistory/");
    xhr.onreadystatechange = function () {
        if (this.readyState==4){
            console.log(this.responseText);
        }
    };
    xhr.send(data)

</script>

