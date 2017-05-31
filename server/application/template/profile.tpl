{capture name=content}
    <div class="col s10 card-panel">
       <div class="card-title"><i>Профиль:</i> {$data.profile.second_name} {$data.profile.first_name}{$data.profile.middle_name}</div>
    </div>
{/capture}
{include 'util/body.tpl'}