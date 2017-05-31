<!DOCTYPE html>
<html lang="ru">
{include 'util/head.tpl'}
<body class="grey lighten-4">
{include 'util/header.tpl'}
<main>
    {if $smarty.capture.content ne ''}
        {$smarty.capture.content}
    {/if}
</main>
{include 'util/footer.tpl'}
</body>
</html>