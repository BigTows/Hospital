class DatePicker {
    constructor(daysElement, timeElement, doctorInfo, countDays) {
        this.root = daysElement;
        this.timeTable = timeElement;
        this.doctor = doctorInfo.id;
        this.time = {
            begin: doctorInfo.timeBegin,
            end: doctorInfo.timeEnd
        };
        this.months = ["Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентебря", "Октября", "Ноября", "Декабря"];
        if (countDays === undefined) {
            this.countDays = 5;
        } else {
            this.countDays = countDays;
        }
    }

    init() {
        this.root.innerHTML="";
        this.timeTable.innerHTML="";
        let dateNow = new Date();
        let self = this;
        for (let i = 0; i < this.countDays; i++) {
            let button = document.createElement("a");
            button.className = "btn waves-effect";
            button.style.margin="0 2px 2px 0";
            button.innerHTML = dateNow.getDate() + " " + this.months[dateNow.getMonth()];
            button.addEventListener("click", (function (dateString) {
                return function (){self.showTimeTable(dateString);}
            }(this.dateToString(dateNow))), true);
            this.root.appendChild(button);
            dateNow.setDate(dateNow.getDate() + 1);
        }
    }

    dateToString(date) {
        return date.getFullYear() + "-" + (date.getMonth() + 1) + "-" + date.getDate();
    }

    showTimeTable(dateString) {
        let self = this;
        this.time.dateString =dateString;
        $.ajax({
            url:'request/getFreeTime/index.php',
            type:"POST",
            data:{
                date:dateString,
                id_doctor:self.doctor
            },
            success:(function (msg){
                console.log(msg);
                self.printTimeTable(JSON.parse(msg).data);
            })

        })
    }
    printTimeTable(json){
        console.log(json);
        var beginTime = this.time.begin.split(':');
        var endTime = this.time.end.split(':');
        var self = this;
        for(let key in this.time.end){
            beginTime[key] = parseInt(beginTime[key]);
            endTime[key] = parseInt(endTime[key]);
        }

        while ((beginTime[0]*100+beginTime[1]<=endTime[0]*100+endTime[1])){
            if (!this.existsTime(beginTime[0],beginTime[1],json)) {
                let button = document.createElement("a");
                button.className = "btn waves-effect";
                button.style.margin="0 2px 2px 0";
                button.innerHTML = dateNow.getDate() + " " + this.months[dateNow.getMonth()];
                var goodBeginTime = beginTime[1]+"";
                if (goodBeginTime.length===1) goodBeginTime+="0";
                button.innerHTML = beginTime[0] + ":" + goodBeginTime;
                button.addEventListener("click", (function (dateString,time) {
                    return function (){self.acceptRecord(dateString,time);}
                }(self.time.dateString,beginTime[0] + ":" + goodBeginTime)), true);
                this.timeTable.appendChild(button);
            }
            beginTime[1]+=20;
            if (beginTime[1]>=60){
                beginTime[0]++;
                beginTime[1]-=60;
            }
        }
    }

    existsTime(hour,min,json){
        for (let key in json){
           if (json[key].h==hour && json[key].m==min) return true;
        }
        return false;
    }

    acceptRecord(date,time){
        let self = this;
        date+=" "+time;
        console.log(date);
        $.ajax({
            url:'request/addRecord/index.php',
            type:"POST",
            data:{
                date:date,
                id_doctor:self.doctor
            },
            success:(function (msg){
                console.log(msg);
                $('#modal').modal('close');
                $('#dialog').modal('open');
                $('#dialog-text').text("Вы успешно записались на прием к "+date);

            })

        })
    }

}
