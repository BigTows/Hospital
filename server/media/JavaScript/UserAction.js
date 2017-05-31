
$('#auth').submit(function(event){
    $.ajax({
        method: "POST",
        cache: true,
        url:"request/auth/",
        data:{
            name:$('#auth-login').val(),
            password:$('#auth-password').val()
    }}).done(function(msg) {
        if (JSON.parse(msg).level>0){
            Materialize.toast('Проверьте данные для входа', 3000);
        }else{
            location.reload();
        }
        });
    event.preventDefault();
});