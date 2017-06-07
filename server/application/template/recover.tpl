{capture name=content}
    <div class="col s10 card-panel">
        <form id="recover">
            <div class="row">
                <div class="input-field col s12 l12">
                    <i class="material-icons prefix" style="margin-top: 12px">person</i>
                    <input id="recover-login" type="text" class="validate">
                    <label for="login">Полис</label>
                </div>
            </div>
            <div class="row">
                <div class="col s12 center">
                    <input type="submit" class="btn" value="Войти">
                </div>
            </div>
        </form>
        <!--- !-->
        <form id="recover-code-form">
            <div class="row">
                <div class="input-field col s12 l12">
                    <i class="material-icons prefix" style="margin-top: 12px">person</i>
                    <input id="recover-code" type="text" class="validate">
                    <label for="login">Код из смс</label>
                </div>
            </div>
            <div class="row">
                <div class="col s12 center">
                    <input type="submit" class="btn" value="Войти">
                </div>
            </div>
        </form>
        <script>
            $('#recover-code-form').hide();
            $('#recover').submit(function (event) {
                $.ajax({
                    method: "POST",
                    cache: true,
                    url: "request/recover/",
                    data: {
                        name:$('#recover-login').val()
                    }
                }).done(function (msg) {
                    console.log(msg);
                    if (JSON.parse(msg).level > 0) {
                        Materialize.toast('Проверьте данные для входа', 3000);
                    } else {
                       document.getElementById("recover-code").style.visibility="visible";
                       document.getElementById("recover").remove();
                        $('#recover-code-form').show();
                    }
                });
                event.preventDefault();
            });

            $('#recover-code-form').submit(function (event) {
                $.ajax({
                    method: "POST",
                    cache: true,
                    url: "request/recover/",
                    data: {
                        code:$('#recover-code').val(),
                        state_recover: 2
                    }
                }).done(function (msg) {
                    console.log(msg);
                    if (JSON.parse(msg).level > 0) {
                        Materialize.toast('Не верный код', 3000);
                    } else {
                        Materialize.toast('Новый пароль отправлен на телефон', 3000);
                    }
                });
                event.preventDefault();
            });
        </script>
    </div>
{/capture}
{include 'util/body.tpl'}