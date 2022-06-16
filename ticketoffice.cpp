#include "ticketoffice.h"
#include <QRandomGenerator>

/*
 * реализация класса TOffTicParam
 * ПАРАМЕТРЫ БИЛЕТНОЙ КАССЫ
*/
TOffTicParam TOffTic::defaultParam = {1,5,3,1,10,5};

/*
 * реализация класса TOffTic
 * МОДЕЛЬ БИЛЕТНОЙ КАССЫ
*/
TOffTic::TOffTic() : QObject()
{
    currentParam = defaultParam;
    configure(currentParam.curCashCount);
    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(tact()));
}

TOffTic::~TOffTic()
{
    timer->stop();
    delete timer;
}

void TOffTic::configure(int n)
{
    for (int i=0; i<n; i++)
    {
        TCash m;
        Cashiers.append(m);
    }
}

void TOffTic::reconfigure(int n)
{
    if (n > 0) configure(n);
    while (n < 0)
    {
        Cashiers.removeLast();
        n++;
    }
}

void TOffTic::sendState()
{
    TOffTicState gs;
    gs.active = simKey.getState();
    for (int i=0; i<Cashiers.count(); i++)
    {
        gs.mstate.append(Cashiers[i].getState());
    }
    emit OffTicState(gs);
}

void TOffTic::tact()
{
    for (int i=0; i<Cashiers.count(); i++)
    {
        Cashiers[i].tact();
    }
    sendState();
}

void TOffTic::control(int cmd)
{
    if (cmd == 0)
    {
        bool on = simKey.control();
        if (on) timer->start();
        else    timer->stop();
    }
    else
    {       
        int helper=1;
            for (int i=0; i<Cashiers.count(); i++)
            {
                if (!Cashiers[i].getState().active) {Cashiers[i].control(); helper--; break;}
            }
            if (helper==1)
            {
                helper=currentParam.curCashNum;
                int minTicketOffice=-1;
                for (int i=0; i<Cashiers.count(); i++)
                {
                    if (Cashiers[i].getState().que<helper ||(Cashiers[i].getState().que==helper && QRandomGenerator::global()->bounded(1, 3)==1))
                                {
                        helper=Cashiers[i].getState().que;
                        minTicketOffice=i;
                    }
                }
                 if (helper!=currentParam.curCashNum) Cashiers[minTicketOffice].queControl();
            }
    }
    sendState();
}

void TOffTic::countChanged(int n)
{
    reconfigure(n);
    currentParam.curCashCount += n;
}

void TOffTic::numChanged(int n)
{
    currentParam.curCashNum += n;
}
