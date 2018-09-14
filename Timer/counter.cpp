#include "counter.h"
#include <QTimer>

Counter::Counter(QLineEdit *editSec, QLineEdit *editMin, QObject *parent) : QObject(parent)
{   int count = 0;

    timer= new QTimer(this);
    setterSec=editSec;
    setterMin=editMin;
    connect(timer, &QTimer::timeout, this, &Counter::decCount);

}

void Counter::start(){
    timer->start(100);
}

void Counter::stop(){
    timer->stop();
}

void Counter::set(){
    timer->stop();
    count=(setterSec->text().toInt())*10 + (setterMin->text().toInt())*600;

    int countsec = count % 600;
    int countmin = (count - countsec)/600;

    QString secOut = QString::number(countsec/10) + "." +QString::number(countsec%10);

    emit showCountMin(countmin);
    emit showCountSec(secOut);
}

void Counter::decCount(){
    if (count>0)
            count--;

    int countsec = count % 600;
    int countmin = (count - countsec)/600;

    QString secOut = QString::number(countsec/10) + "." +QString::number(countsec%10);

    emit showCountMin(countmin);
    emit showCountSec(secOut);
}
