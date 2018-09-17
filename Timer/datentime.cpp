#include "datentime.h"
#include <ctime>
#include <chrono>

DateNTime::DateNTime(QObject *parent): QObject (parent)
{

    timer= new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DateNTime::getTime);
    connect(timer, &QTimer::timeout, this, &DateNTime::getDate);
    timer->start(100);

}

/* i metodi getTime e getDate possono essere modificati
per estrapolare qualsiasi tipo di data e ora si voglia e hanno il compito
di inviare i relativi risultati tramite signal per il Display

E' stato scelto di lasciare al Displayer il compito di interpretare i dati per rendere
il codice piu' flessibile nel caso di modifica dei componenti grafici
*/

void DateNTime::getTime(){
    auto now = std::chrono::system_clock::now();
    time_t tmpt= std::chrono::system_clock::to_time_t(now);
    struct tm *timeInts;
    timeInts = std::localtime(&tmpt); //laboriosi passaggi, ma unici che ho trovato per passare da chrono::time_point a tm

    hour= timeInts->tm_hour;
    min=timeInts->tm_min;

    emit showTime(hour, min);
}

void DateNTime::getDate(){
    auto now = std::chrono::system_clock::now();
    time_t tmpt= std::chrono::system_clock::to_time_t(now);
    struct tm *timeInts;
    timeInts = std::localtime(&tmpt);

    day=timeInts->tm_mday;
    month=(timeInts->tm_mon +1);
    year=(timeInts->tm_year + 1900);
    weekDay=timeInts->tm_wday;

    emit showDate(day, month, year, weekDay);
}
