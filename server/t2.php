<?php
echo session_id();
?>


<script>
    var xhr = new XMLHttpRequest();
    var data = new FormData();
    data.append("token","mfbsq251irf3gg7ir6onl47lc7");
    data.append("id_user","1234123412341234");
    data.append("text","l55uf4606drr4h288mi512d1q1");
    xhr.open("POST","request/addHistory/");
    xhr.onreadystatechange = function () {
        if (this.readyState==4){
            console.log(this.responseText);
        }
    };
    xhr.send(data)

</script>

