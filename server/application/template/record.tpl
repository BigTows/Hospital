{capture name=content}
    <script src="media/JavaScript/DatePicker.js"></script>
    <div class="col s10 card-panel">

        <div class="row">
            {foreach item=record from=$data.record}
                <div class="col s12 m12 l12 xl6">
                    <div class="card horizontal">
                        <div class="card-image">
                            <img src="{$record.photo}">
                        </div>
                        <div class="card-stacked">
                            <div class="card-title">{$record.second_name} {$record.first_name|truncate:2:"."}{$record.middle_name|truncate:2:"."}</div>
                            <div class="card-content">
                                <p>
                                    Специальность: {$record.name}.
                                    <br>
                                    Время работы: {$record.start_time} - {$record.end_time}
                                </p>
                            </div>
                            <div class="card-action">
                                <a href="#" class="btn waves-effect" onclick="modal({$record.id_doctor},'{$record.start_time}','{$record.end_time}')">Записаться</a>
                            </div>
                        </div>
                    </div>
                </div>
            {/foreach}
        </div>
        <!-- Modal Structure -->
        <div id="modal" class="modal bottom-sheet">
            <div class="modal-content">
                <h4>Выбор времени</h4>
                <br>
                <div class="row">
                <div id="date" class="input-field col s6">

                </div>

                <div id="time-table">

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
        var datePicker=  new DatePicker(document.getElementById("date"));
        datePicker.init();


        $(document).ready(function(){
            $('.modal').modal();


        });
        function modal(id,timeStartWork,timeEndWork){
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
        }
    </script>
{/capture}
{include 'util/body.tpl'}