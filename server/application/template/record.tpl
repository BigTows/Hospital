{capture name=content}
    <script src="media/JavaScript/DatePicker.js"></script>
    <div class="col l2 card-panel">

        <ul class="section table-of-contents">
            {foreach item=record key=key from=$data.record}
            <li><a href="#{$key}">{$key}</a></li>
            {/foreach}
        </ul>
    </div>
    <div class="col s10 card-panel">
        <div class="row">
            {foreach item=record key=key from=$data.record}
            <div id="{$key}" class="section scrollspy">
                <h4>{$key}</h4>
            {foreach item=doctor from=$record}
                <div class="col s12 m12 l12 xl6">
                    <div class="card horizontal">
                        <div class="card-image">
                            <img height="200px" src="{$doctor.photo}">
                        </div>
                        <div class="card-stacked">
                            <div class="card-title">{$doctor.second_name} {$doctor.first_name|truncate:2:"."}{$doctor.middle_name|truncate:2:"."}</div>
                            <div class="card-content">
                                <p>
                                    Специальность: {$doctor.name}.
                                    <br>
                                    Время работы: {$doctor.start_time} - {$doctor.end_time}
                                </p>
                            </div>
                            <div class="card-action">
                                <a href="#" class="btn waves-effect" onclick="modal({$doctor.id_doctor},'{$doctor.start_time}','{$doctor.end_time}')">Записаться</a>
                            </div>
                        </div>
                    </div>
                </div>
            {/foreach}
            </div>
                <div class="col s12"></div>
                <br>
            {/foreach}
        </div>



        <!-- Modal Structure -->
        <div id="dialog" class="modal">
            <div class="modal-content">
                <h4>Успех!</h4>
                <p id="dialog-text"></p>
            </div>
            <div class="modal-footer">
                <a href="#!" class="modal-action modal-close waves-effect waves-green btn-flat">Хорошо</a>
            </div>
        </div>

        <!-- Modal Structure -->
        <div id="modal" class="modal bottom-sheet">
            <div class="modal-content">
                <h4>Выбор времени</h4>
                <br>
                <div class="row">
                <div id="date" class="col s4">

                </div>

                <div id="time-table" class="col s8">

                </div>
                </div>
            </div>
            <div class="modal-footer">

            </div>
        </div>

    </div>
    <script>
        var months = ["Января","Февраля","Марта","Апреля","Мая","Июня","Июля","Августа","Сентебря","Октября","Ноября","Декабря"];
        var dateNow = new Date();


        function modal(id,timeStartWork,timeEndWork) {
            let datePicker=  new DatePicker(document.getElementById("date"),document.getElementById("time-table"), {
                id:id,
                timeBegin:timeStartWork,
                timeEnd:timeEndWork
            });
            datePicker.init();
            $('#modal').modal('open');
        }


        $(document).ready(function(){
            $('.modal').modal();


        });
        /*function modal(id,timeStartWork,timeEndWork){
            var dateNow = new Date();
            for (var i = 1; i<=4;i++) {
                $('#month-picker').append(new Option(i+"", i));
            }
            $('select').material_select();
            //Get Hour and minute
            var timeStartWorkArray = timeStartWork.split(':');
            var timeEndWorkArray = timeEndWork.split(':');
            for(let key in timeEndWorkArray){
                timeStartWorkArray[key] = parseInt(timeStartWorkArray[key]);
                timeEndWorkArray[key] = parseInt(timeEndWorkArray[key]);
            }

            while ((timeStartWorkArray[0]*100+timeStartWorkArray[1]<=timeEndWorkArray[0]*100+timeEndWorkArray[1])){
                $('#time-table').text($('#time-table').text()+timeStartWorkArray[0]+":"+timeStartWorkArray[1]+" |  ");
                timeStartWorkArray[1]+=20;
                if (timeStartWorkArray[1]>=60){
                    timeStartWorkArray[0]++;
                    timeStartWorkArray[1]-=60;
                }
            }
            $('#time-table')
            $('#modal').modal('open');
        }*/
    </script>
{/capture}
{include 'util/body.tpl'}