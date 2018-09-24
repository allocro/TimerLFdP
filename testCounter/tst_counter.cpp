#include <QtTest>
#include "counter.h"
#include <QLineEdit>
#include <iostream>
#include <cmath>
#include <QDebug>

// add necessary includes here

class tst_Counter : public QObject
{
    Q_OBJECT
public:
    tst_Counter();
    ~tst_Counter();

private slots:
    void initTestCD();
};

tst_Counter::tst_Counter() : QObject ()
{
}
tst_Counter::~tst_Counter()
{

}

void tst_Counter::initTestCD(){
    QLineEdit editSec;
    QLineEdit editMin;
    Counter counter(&editSec, &editMin);

    for(int i=0; i<=10; i++){
        srand((unsigned)time(0));
        int randsec= rand() %60;
        int randmin= rand() %60;
        randmin =0; //Per testare il tester piu velocemente

        QString randsecString= QString::number(randsec);
        QString randminString= QString::number(randmin);


        editSec.setText(randsecString);
        editMin.setText(randminString);

        counter.set();
        std::cout << "Starting the Timer at " << (counter.count)/10 << std::endl;

                auto start= std::chrono::system_clock::now();
                counter.start(); //{timer->start();}
                while(counter.count>0){
                    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);
                }
                auto end= std::chrono::system_clock::now();
                counter.stop();
                auto check= std::chrono::duration_cast<std::chrono::seconds>(end - start);
                int checkInt = check.count();
                int timerCountOrgn = randsec + randmin*60;
                if(checkInt==timerCountOrgn){
                        std::cout << "Timer matches" <<std::endl;
                    }else{
                        std::cout << "Timer doesnt match" <<std::endl;
                        std::cout << "Sec counted: " << timerCountOrgn <<std::endl;
                        std::cout << "Sec passed: " << checkInt <<std::endl;
                    }

    }
}

QTEST_MAIN(tst_Counter)

#include "tst_counter.moc"
