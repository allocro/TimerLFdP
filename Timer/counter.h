#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>
#include <QLineEdit>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QLineEdit *setterSec, QLineEdit *setterMin, QObject *parent = nullptr);
    int count;

private:
    QTimer *timer;
    QLineEdit *setterSec;
    QLineEdit *setterMin;

signals:
    void showCountSec(QString count);
    void showCountMin(int count);

public slots:
    void decCount();
    void start();
    void stop();
    void set();
};

#endif // COUNTER_H
