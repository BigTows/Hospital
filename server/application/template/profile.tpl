{capture name=content}
    <div class="col s10 card-panel">
        <div class="card-title">
            <div class="row">
                <div class="col s12 center-align">
                    <img src="{$data.profile.photo}" alt="Ваше фото"
                         style="width: 100px;height: 100px; margin-top: 20px;" class="circle">
                </div>
            </div>
            <div class="row">
                <div class="col s1"></div>
                <div class="col s10">
                    <ul class="collection">
                        <li class="collapsible-header center-align">Карта пациента</li>
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
                    <ul class="collection">
                        <li class="collapsible-header center-align">Записи к врачам</li>
                        {foreach item=record key=key from=$data.records}
                            <li class="collection-item dismissable">
                                <div>{$record.d_second_name} {$record.d_first_name|truncate:2:"."}{$record.d_middle_name|truncate:2:"."} ({$record.post_name})
                                    <a class="secondary-content">{$record.date}</a>
                                </div>
                            </li>
                        {/foreach}
                    </ul>
                </div>

            </div>
        </div>
        <div class="card-content">

        </div>
    </div>
{/capture}
{include 'util/body.tpl'}