#include <QtTest>
#include "counter.h"
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <iostream>

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
    void initTestCD();
    void cleanupTestCD();
    void testCountdown();

};

testCounter::testCounter() : QObject ()
{   int i;
    editSec= new QLineEdit();
    editMin= new QLineEdit();
    counter= new Counter(editSec, editMin);
    for(i=0; i<=10; i++){
        int randsec= rand() %60;
        int randmin= rand() %60;
        randsec=3;
        randmin=0; //Per motivi di tempo

        QString randsecString= QString::number(randsec);
        QString randminString= QString::number(randmin);


        editSec->setText(randsecString);
        editMin->setText(randminString);

        counter->set();
        std::cout << "Starting the Timer at " << (counter->count)/10 << "sec" <<std::endl;
        auto start= std::chrono::system_clock::now();

        counter->start();

        while(counter->count>0){
            std::cout <<counter->count <<std::endl;
        }
        auto end= std::chrono::system_clock::now();
        counter->stop();

        auto check= std::chrono::duration_cast<std::chrono::seconds>(end - start);
        int checkInt= check.count();

        if(checkInt==randsec+(randmin*60)){
            std::cout << "Timer matches" <<std::endl;
        }else{
            std::cout << "Timer doesnt match" <<std::endl;
            std::cout << "Sec counted: " << (counter->count)/10 <<std::endl;
            std::cout << "Sec passed: " << checkInt <<std::endl;
            break;
        }
    }

}

testCounter::~testCounter()
{

}

void testCounter::initTestCD()
{

}

void testCounter::cleanupTestCD()
{

}

void testCounter::testCountdown()
{

}

QTEST_MAIN(testCounter)

#include "tst_testcounter.moc"
