#include <QtTest>
#include "counter.h"
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <iostream>
#include <QEventLoop>

// add necessary includes here

class testCounter : public QObject
{
    Q_OBJECT


public:
    Counter *counter;
    QLineEdit *editSec;
    QLineEdit *editMin;


    testCounter();
    ~testCounter();

private slots:
    void testCountdown(int sec, int min, QThread *thread);

};

testCounter::testCounter() : QObject ()
{   int i;
    int testTimes = 1;
    QThread*thread = new QThread();
    editSec= new QLineEdit();
    editMin= new QLineEdit();
    counter= new Counter(editSec, editMin);
    counter->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), counter, SLOT(start()));
    for(i=0; i<=testTimes; i++){
        int randsec= rand() %60;
        int randmin= rand() %60;

        randmin = 0;//Per velocizzare il test

        testCountdown(randsec, randmin, thread);
    }

}

testCounter::~testCounter()
{

}

void testCounter::testCountdown(int sec, int min, QThread *thread)
{

    QString randsecString= QString::number(sec);
    QString randminString= QString::number(min);


    editSec->setText(randsecString);
    editMin->setText(randminString);


    counter->set();
    std::cout << "Starting the Timer at " << (counter->count)/10 << "sec" <<std::endl;


    thread->start();
    auto start= std::chrono::system_clock::now();

    while(counter->count>0){
    }
    auto end= std::chrono::system_clock::now();

    auto check= std::chrono::duration_cast<std::chrono::seconds>(end - start);
    int checkInt= check.count();

    if(checkInt==sec+(min*60)){
        std::cout << "Timer matches" <<std::endl;
    }else{
        std::cout << "Timer doesnt match" <<std::endl;
        std::cout << "Sec counted: " << sec+(min*60) <<std::endl;
        std::cout << "Sec passed: " << checkInt <<std::endl;
    }
}

QTEST_MAIN(testCounter)

#include "tst_testcounter.moc"
