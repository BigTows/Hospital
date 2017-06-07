{capture name=content}
<ul class="collapsible" data-collapsible="accordion">
    {foreach key=date item=item from=$data.history}
        <li>
            <div class="collapsible-header"><i class="material-icons">schedule</i>Дата: {$date}</div>

            {foreach item=record from=$item}
            <div class="collapsible-body">
                <div class="collection">
                    <a class="collection-item">Доктор: {$record.second_name} {$record.first_name|truncate:2:"."}{$record.middle_name|truncate:2:"."} ({$record.namePost})</a>
                    <a class="collection-item"> Время: {$record.time}</a>
                    <a  class="collection-item">Описание: {$record.text}</a>
                </div>
            </div>
            {/foreach}
        </li>
    {/foreach}

</ul>
{/capture}
{include 'util/body.tpl'}