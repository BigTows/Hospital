<!DOCTYPE html>
<html lang="ru">
{include 'util/head.tpl'}
<body class="grey lighten-4">
{include 'util/header.tpl'}
<main>
    <div class="row">
        <div class="col s1 l1"></div>
        <div class="col s7 l7 card-panel">
            <div class="card-title">
                Перезагрузка через, <a id="seconds">3</a> секунд
            </div>
            <div class="card-content">
                <p>Вы успешно вышли, дождитесь перезагрузки страницы!</p>
            </div>
        </div>
        <script>
            var seconds = 2;
            setInterval(function () {
                $("#seconds").text(seconds+"");
                seconds--;
                if (seconds===-1){
                    location.href="../server";
                }
            },1000);
        </script>
    </div>
</main>

{include 'util/footer.tpl'}
</body>
