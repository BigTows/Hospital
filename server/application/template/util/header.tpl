<nav>
    <div class="nav-wrapper green lighten-1">
        <ul class="left hide-on-med-and-down">
            {foreach item=page key=key from=$data.header}
                {if $key == $data.page}
                    <li class="active"><a href="{$page[1]}">{$page[0]}</a></li>
                {else}
                    <li ><a href="{$page[1]}">{$page[0]}</a></li>
                {/if}
            {/foreach}
        </ul>
        <ul class="right input-field">


            <form>
                <input placeholder="Поиск" id="search" type="search" required>
                <label class="label-icon" for="search"><i class="material-icons">search</i></label>
                <i class="material-icons">close</i>
            </form>

        </ul>
    </div>
</nav>