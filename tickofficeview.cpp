#include "tickofficeview.h"

/*
 * реализация класса TKeyView
 * ВИЗУАЛИЗАЦИЯ СОСТОЯНИЯ СИМУЛЯЦИИ
*/
TKeyView::TKeyView(QWidget *parent)
    : QLabel(parent)
{
    QFont f = font();
    f.setBold(true);
    f.setPointSize(16);
    setFont(f);
    setAutoFillBackground(true);
    setAlignment(Qt::AlignCenter);
    setMinimumSize(QSize(50,50));
    setMaximumSize(QSize(50,50));
    view(false);
}

void TKeyView::view(bool s)
{
    setText(s ? "ЗАН" : "ПУСТ");
    QPalette p;
    p.setColor(QPalette::Window,(s ? Qt::green : Qt::red));
    setPalette(p);
}

/*
 * реализация класса TCounterView
 * ВИЗУАЛИЗАЦИЯ СЧЕТЧИКА ОЧЕРЕДИ И ТАЙМЕРА ОКОШКА КАССЫ
*/
TCounterView::TCounterView(QWidget *parent)
    : QLabel(parent)
{
    QFont f = font();
    f.setBold(true);
    f.setPointSize(16);
    setFont(f);
    setAutoFillBackground(true);
    setAlignment(Qt::AlignCenter);
    setMinimumSize(QSize(80,50));
    setMaximumSize(QSize(80,50));
    view(0);
}

void TCounterView::view(int n)
{
    setText(QString().setNum(n));
    QPalette p;
    p.setColor(QPalette::Window,Qt::lightGray);
    setPalette(p);
}

/*
 * реализация класса TCashView
 * ВИЗУАЛИЗАЦИЯ КОНКРЕТНОГО ОКОШКА КАССЫ
*/
TCashView::TCashView(QWidget *parent)
    : QWidget(parent)
{
    kv = new TKeyView();
    cv = new TCounterView();
    qu = new TCounterView();
    hl = new QHBoxLayout(this);
    hl->addWidget(qu,1,Qt::AlignLeft);
    hl->addWidget(kv);
    hl->addWidget(cv);
}

void TCashView::view(TCashState ms)
{
    kv->view(ms.active);
    cv->view(ms.counter);
    qu->view(ms.que);
}
