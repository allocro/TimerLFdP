#ifndef DATENTIME_H
#define DATENTIME_H

#include <QObject>
#include <QTimer>
#include <QLineEdit>
#include <QLCDNumber>

class DateNTime: public QObject
{
    Q_OBJECT

public:
    DateNTime(QObject *parent = nullptr);
    int hour;
    int min;
    int day;
    int month;
    QString weekDay;

private:
    QTimer *timer;


signals:
    void showTime(int hour, int min);
    void showDate(int d, int m, int y, int weekday);

public slots:
    void getTime();
    void getDate();

};

#endif // DATENTIME_H
