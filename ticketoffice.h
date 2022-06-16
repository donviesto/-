#ifndef TICKETOFFICE_H
#define TICKETOFFICE_H

#include <QObject>
#include <QVector>
#include <QTimer>

#include "cashier.h"

/*
 * описание класса TOffTicParam
 * ПАРАМЕТРЫ БИЛЕТНОЙ КАССЫ
*/
struct TOffTicParam
{
    int minCashCount;
    int maxCashCount;
    int curCashCount;
    int minCashNum;
    int maxCashNum;
    int curCashNum;
};

/*
 * описание класса TOffTicState
 * СОСТОЯНИЕ БИЛЕТНОЙ КАССЫ
*/
struct TOffTicState
{
    bool active;
    QVector<TCashState> mstate;
};

/*
 * описание класса TOffTic
 * МОДЕЛЬ КАССЫ
*/
class TOffTic : public QObject
{
    Q_OBJECT

    static TOffTicParam defaultParam;
    TOffTicParam currentParam;

    QTimer *timer;

    TKey simKey;
    QVector<TCash> Cashiers;

    void configure(int);
    void reconfigure(int);
    void sendState();

private slots:
    void tact();

signals:
    void OffTicState(TOffTicState);

public:
    TOffTic();
    ~TOffTic();

    inline TOffTicParam getParam() { return currentParam; };

public slots:
    void control(int);
    void countChanged(int);
    void numChanged(int);
};

#endif // TICKETOFFICE_H
