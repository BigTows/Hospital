class DatePicker {
    constructor(daysElement,timeElement, countDays) {
        this.root = daysElement;
        this.timeTable = timeElement;
        this.months = ["Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентебря", "Октября", "Ноября", "Декабря"];
        if (countDays === undefined) {
            this.countDays = 5;
        } else {
            this.countDays = countDays;
        }
    }

    init() {
        let dateNow = new Date();
        let self = this;
        for (let i = 0; i < this.countDays; i++) {
            let button = document.createElement("a");
            button.className = "btn waves-effect";
            button.innerHTML = dateNow.getDate() + " " + this.months[dateNow.getMonth()];
            button.addEventListener("click", function (dateString) {
                return self.showTimeTable(dateString);
            }(this.dateToString(dateNow)),true);
            this.root.appendChild(button);
            dateNow.setDate(dateNow.getDate() + 1);
        }
    }

    dateToString(date) {
        return date.getFullYear() + "-" + (date.getMonth() + 1) + "-" + date.getDate();
    }

    showTimeTable(dateString){

    }

}
