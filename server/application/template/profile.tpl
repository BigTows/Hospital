{capture name=content}
    <div class="col s10 card-panel">
        <div class="card-title">
            <div class="row">
                <div class="col s12 center-align">
                    <img src="{$data.profile.photo}" alt="Ваше фото" style="width: 100px;height: 100px; margin-top: 20px;" class="circle">
                </div>
            </div>
            <div class="row">
                <div class="col s1"></div>
                <div class="col s10">
                    <ul class="collection">
                        <li class="collapsible-header center-align">Карта поциента</li>
                        <li class="collection-item dismissable">
                            <div>Полис
                                <a class="secondary-content">{$data.profile.polis}</a>
                            </div>
                        </li>
                        <li class="collection-item dismissable">
                            <div>Имя
                                <a class="secondary-content">{$data.profile.first_name}</a>
                            </div>
                        </li>
                        <li class="collection-item dismissable">
                            <div>Отчесвто
                                <a class="secondary-content">{$data.profile.middle_name}</a>
                            </div>
                        </li>
                        <li class="collection-item dismissable">
                            <div>Фамилия
                                <a class="secondary-content">{$data.profile.second_name}</a>
                            </div>
                        </li>
                        <li class="collection-item dismissable">
                            <div>Дата рождения
                                <a class="secondary-content">{$data.profile.date}</a>
                            </div>
                        </li>
                        <li class="collection-item dismissable">
                            <div>Телефон
                                <a class="secondary-content">{$data.profile.phone}</a>
                            </div>
                        </li>
                        <li class="collection-item dismissable">
                            <div>Почта
                                <a class="secondary-content">{$data.profile.email}</a>
                            </div>
                        </li>
                    </ul>
                </div>

            </div>
        </div>
        <div class="card-content">

        </div>
    </div>
{/capture}
{include 'util/body.tpl'}