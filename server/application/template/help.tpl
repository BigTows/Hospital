{capture name=content}
    <div class="row card-panel">
        <div class="col s4">
            <h4>Как добраться?</h4>
            <p>
                Наш адрес: <i>Москва, Есенинский бул., 9, корп.1</i>
            <hr>
            <ul> Мы работаем:
                <li>С 7:30 по 20:00</li>
                <li>Телефон: +7 (499) 172-19-57</li>
            </ul>
            </p>
        </div>
        <script src="//api-maps.yandex.ru/2.1/?lang=ru_RU" type="text/javascript"></script>
        <div class="col s7">
            <div id="map" style="width: auto; height: 400px"></div>
        </div>
        <div class="col s1"></div>
    </div>
    <script type="text/javascript">
        ymaps.ready(function () {
            var map = new ymaps.Map("map", {
                center: [55.70113056904488, 37.77944849999999],
                zoom: 14
            });
            var myPlacemark = new ymaps.Placemark([55.70113056904488, 37.77944849999999], {}, {});
            map.geoObjects.add(myPlacemark);
        });
    </script>
{/capture}
{include 'util/body.tpl'}