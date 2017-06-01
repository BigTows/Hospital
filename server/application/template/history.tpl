{capture name=content}
<ul class="collapsible" data-collapsible="accordion">
    {foreach key=key item=item from=$data.history}
        <li>
            <div class="collapsible-header"><i class="material-icons">schedule</i>{$item.date}</div>
            <div class="collapsible-body"><span>{$item.text}</span></div>
        </li>
    {/foreach}

</ul>
{/capture}
{include 'util/body.tpl'}