<!DOCTYPE html>
<html lang="ru">
{include 'util/head.tpl'}
<body class="grey lighten-4">
{include 'util/header.tpl'}
<main>
    <div class="row">
        <div class="col s0 l1"></div>
        <div class="col s12 l7" style="margin-top: 20px">
            {if $smarty.capture.content ne ''}
                {$smarty.capture.content}
            {/if}
        </div>
        <div class="col s12 l3" style="margin-top: 20px;">
            <div class="auth-panel card-panel">
                {if $data.profile === NULL}
                <span class="card-title">Авторизация</span>
                <div class="card-content">

                    <form id="auth">
                        <div class="row">
                            <div class="input-field col s12 l12">
                                <i class="material-icons prefix" style="margin-top: 12px">person</i>
                                <input id="auth-login" type="text" class="validate">
                                <label for="login">Полис</label>
                            </div>
                            <div class="input-field col s12 l12">
                                <i class="material-icons prefix" style="margin-top: 12px">lock</i>
                                <input id="auth-password" type="password" class="validate">
                                <label for="password">Пароль</label>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col s12 center">
                                <input type="submit" class="btn" value="Войти">
                            </div>
                        </div>
                        <div class="row">
                            <div class="col s12 l7">
                                <a href="recover">Вы здесь впервые?</a>
                            </div>
                            <div class="col s12 l5">
                                <a href="recover">Забыли пароль?</a>
                            </div>
                        </div>
                    </form>
                    {else}
                    <ul class="collection with-header">
                        <li class="collection-header">
                            Здравствуйте, {$data.profile.second_name} {$data.profile.first_name|truncate:2:"."}{$data.profile.middle_name|truncate:2:"."}
                        </li>
                        <a href="profile" class="collection-item">
                            Профиль
                            <span class="badge">
                                <i class="material-icons">perm_identity</i>
                            </span>
                        </a>
                        <a href="record" class="collection-item">
                            Записаться к врачу
                            <span class="badge">
                                <i class="material-icons">mode_edit</i>
                            </span>
                        </a>
                        <a href="history" class="collection-item">
                            История болезни
                            <span class="badge">
                                <i class="material-icons">queue</i>
                            </span>
                        </a>
                        <a href="exit" class="collection-item">
                            Выйти
                            <span class="badge">
                                <i class="material-icons">open_in_browser</i>
                            </span>
                        </a>
                    </ul>

                    {/if}
                </div>
            </div>
        </div>
    </div>
</main>

{include 'util/footer.tpl'}
</body>
</html>