<?php
echo session_id();
?>


<script>
    var xhr = new XMLHttpRequest();
    var data = new FormData();
    data.append("token","2");
    xhr.open("POST","request/getRecords/");
    xhr.onreadystatechange = function () {
        if (this.readyState==4){
            console.log(this.responseText);
        }
    };
    xhr.send(data)

</script>

