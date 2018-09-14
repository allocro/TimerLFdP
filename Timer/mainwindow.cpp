#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QTimer>
#include "counter.h"
#include <QDateTime>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->minEdit->setValidator(new QIntValidator(0, 59, this));
    ui->secEdit->setValidator(new QIntValidator(0, 59, this));
    QDateTime dateTime = QDateTime::currentDateTime();

    QTimer *timer = new QTimer(this);
        //connect(timer, SIGNAL(timeout()), ui->currentClock, SLOT(display()));
        timer->start(1000);

    ui->dayOfWeek->setText(dateTime.toString("dddd"));
    //ui->dayOfWeek->setAlignment(Qt::AlignCenter);
    ui->currentClock->display(dateTime.toString("hh:mm"));
    ui->dateClock->display(dateTime.toString("dd.MM"));
    ui->yearClock->display(dateTime.toString("yyyy"));
    QObject::connect(ui->usFormat, &QCheckBox::stateChanged,[=](int stateChanged){
        if(!stateChanged)
            ui->dateClock->display(dateTime.toString("dd.MM"));
        else
            ui->dateClock->display(dateTime.toString("MM.dd"));

    });

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
