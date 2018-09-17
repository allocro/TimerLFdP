#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "counter.h"
#include <QDateTime>
#include <QString>
#include "datentime.h"
#include <QAbstractButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Spostati i parametri di valutazione di accettabilita' del timeSetter dalla
     * main window e inseriti nell'instanziazione del timer(classe Counter) stesso
     * per una maggiore compattezza della classe ed evitare possibili malfunzionamenti
     * dovuti a modifiche della parte grafica dell'interfaccia
     */
    DateNTime *dateNTime= new DateNTime(this);

    QObject::connect(dateNTime, &DateNTime::showTime, [=](int hour, int min){
        QString outString= QString::number(hour) + ":" + QString::number(min);
        ui->currentClock->display(outString);
    });

    QObject::connect(dateNTime, &DateNTime::showDate, [=](int d, int m, int y, int wd){
        QString outString;
        switch (wd) {
        case 0:
            outString="Sunday";
            break;
        case 1:
            outString="Monday";
            break;
        case 2:
            outString="Tuesday";
            break;
        case 3:
            outString="Wednesday";
            break;
        case 4:
            outString="Thursday";
            break;
        case 5:
            outString="Friday";
            break;
        case 6:
            outString="Saturday";
            break;

        }
        ui->dayOfWeek->setText(outString);
    });

    QObject::connect(dateNTime, &DateNTime::showDate, [=](int d, int m){
        if(!ui->usFormat->isChecked()){
            QString outString= QString::number(d) + "." + QString::number(m);
            ui->dateClock->display(outString);
        } else{
            QString outString= QString::number(m) + "." + QString::number(d);
            ui->dateClock->display(outString);
        }
    });

    QObject::connect(dateNTime, &DateNTime::showDate, [=](int d, int m, int y){
        ui->yearClock->display(y);
    });

    QObject::connect(ui->usFormat, &QCheckBox::stateChanged, dateNTime, &DateNTime::getDate);

    Counter *counter= new Counter(ui->secEdit, ui->minEdit, this);
        QObject::connect(counter, SIGNAL(showCountSec(QString)), ui->timerDisplay, SLOT(display(QString)));
        QObject::connect(counter, SIGNAL(showCountMin(int)), ui->timerMin, SLOT(display(int)));
        QObject::connect(ui->startButton, SIGNAL(clicked()), counter, SLOT(start()));
        QObject::connect(ui->stopButton, SIGNAL(clicked()), counter, SLOT(stop()));
        QObject::connect(ui->setButton, SIGNAL(clicked()), counter, SLOT(set()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
