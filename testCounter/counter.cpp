#include "counter.h"
#include <QTimer>
#include <QIntValidator>
#include <QEventLoop>


Counter::Counter(QLineEdit *editSec, QLineEdit *editMin, QObject *parent) : QObject(parent)
{   int count = 0;




    setterSec=editSec;
    setterMin=editMin;
    setterSec->setValidator(new QIntValidator(0, 59, this));
    setterMin->setValidator(new QIntValidator(0, 59, this));

}

void Counter::start(){
    timer= new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Counter::decCount);
    timer->start(100);


}

void Counter::stop(){
    if(timer!=nullptr)
    timer->stop();
}

void Counter::set(){

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
