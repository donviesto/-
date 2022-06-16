#include "interface.h"

/*
 * реализация класса TParamWindow
 * ОКНО ПАРАМЕТРОВ БИЛЕТНОЙ КАССЫ
*/
TParamWindow::TParamWindow(TOffTicParam par, QWidget *parent)
    : QWidget(parent)
{
    h = new QLabel("Параметры кассы",this);
    h->setGeometry(20,10,200,50);
    h->setWordWrap(true);
    QFont f = h->font();
    f.setBold(true);
    f.setPointSize(16);
    h->setFont(f);
    l = new QLabel("Число кассиров",this);
    k = new QLabel("Число людей в очереди",this);
    l->setGeometry(20,70,120,25);
    k->setGeometry(20, 150,200, 25);
    n = new QSpinBox(this);
    m=new QSpinBox(this);
    n->setGeometry(20,100,40,25);
    m->setGeometry(20,180,40,25);
    n->setMinimum(par.minCashCount);
    m->setMinimum(par.minCashNum);
    n->setMaximum(par.maxCashCount);
    m->setMaximum(par.maxCashNum);
    n->setValue(par.curCashCount);
    m->setValue(par.curCashNum);
    nvalue = par.curCashCount;
    qvalue = par.curCashNum;
    b1 = new QPushButton("Применить",this);
    b1->setGeometry(20,230,100,25);
    b1->setEnabled(false);
    b2 = new QPushButton("Отменить",this);
    b2->setGeometry(20,250,100,25);
    b2->setEnabled(false);
    setMinimumSize(QSize(160,210));

    connect(n,SIGNAL(valueChanged(int)),this,SLOT(countChanged(int)));
    connect(m,SIGNAL(valueChanged(int)),this,SLOT(numChanged(int)));
    connect(b1,SIGNAL(pressed()),this,SLOT(changeCashCount()));
    connect(b2,SIGNAL(pressed()),this,SLOT(restoreCashCount()));
}

TParamWindow::~TParamWindow()
{
    delete b2;
    delete b1;
    delete n;
    delete l;
    delete h;
}

void TParamWindow::countChanged(int n)
{
    bool m = (nvalue != n);
    b1->setEnabled(m);
    b2->setEnabled(m);
}

void TParamWindow::numChanged(int n)
{
    bool m = (qvalue != n);
    b1->setEnabled(m);
    b2->setEnabled(m);
}

void TParamWindow::changeCashCount()
{
    b1->setEnabled(false);
    b2->setEnabled(false);
    emit changeCount(n->value()-nvalue);
    emit changeNum(m->value()-qvalue);
    qvalue = m->value();
    nvalue = n->value();
}

void TParamWindow::restoreCashCount()
{
    b1->setEnabled(false);
    b2->setEnabled(false);
    n->setValue(nvalue);
    m->setValue(qvalue);
}

/*
 * реализация класса TEventWindow
 * ОКНО УПРАВЛЕНИЕ КЛИЕНТАМИ КАССЫ
*/
TEventWindow::TEventWindow(QWidget *parent)
    : QWidget(parent)
{
    h = new QLabel("Управление симуляцией",this);
     h->setGeometry(20,10,300,50);
    h->setWordWrap(true);
    QFont f = h->font();
    f.setBold(true);
    f.setPointSize(16);
    h->setFont(f);
    b1 = new QPushButton("Добавить клиента",this);
    b1->setGeometry(5,120,220,25);
    b2 = new QPushButton("Пуск или пауза",this);
    b2->setGeometry(5,150,220,25);
    QPalette p;
    p.setColor(QPalette::Window,Qt::lightGray);
    setPalette(p);
    setAutoFillBackground(true);
    setMinimumSize(QSize(180,150));
    connect(b1,SIGNAL(pressed()),this,SLOT(stationControl()));
    connect(b2,SIGNAL(pressed()),this,SLOT(stationControl()));
}

TEventWindow::~TEventWindow()
{
    delete b2;
    delete b1;
    delete h;
}


void TEventWindow::stationControl()
{
    QPushButton *b = (QPushButton*)sender();
    int command = (b == b2 ? 0 : 1);
    emit control(command);

}


/*
 * реализация класса TOffTicWindow
 * ОКНО ОТОБРАЖЕНИЯ БИЛЕТНОЙ КАССЫ
*/
TOffTicWindow::TOffTicWindow(TOffTicParam par, QWidget *parent)
    : QWidget(parent)
{
    kv = new TKeyView();
    kv->setText("ПУСТ");
    hl = new QHBoxLayout(this);
    vl = new QVBoxLayout();
    TCashView *mv;
    for (int i=0; i<par.curCashCount;i++)
    {
        mv = new TCashView();
        mvl.append(mv);
        vl->addWidget(mv);
    }
    hl->addLayout(vl);
    setMinimumSize(QSize(180,150));
    setMaximumWidth(400);
}

TOffTicWindow::~TOffTicWindow()
{
    TCashView *mv;
    while (mvl.count() > 0)
    {
        mv = mvl.takeLast();
        delete mv;
    }
    delete kv;
    delete vl;
    delete hl;
}

void TOffTicWindow::view(TOffTicState gs)
{
    kv->view(gs.active);
    for (int i=0; i<gs.mstate.count();i++)
    {
        mvl.at(i)->view(gs.mstate[i]);
    }
}

void TOffTicWindow::countChanged(int n)
{
    TCashView *mv;
    while (n > 0)
    {
        mv = new TCashView();
        mvl.append(mv);
        vl->addWidget(mv);
        n--;
    }
    while (n < 0)
    {
        mv = mvl.takeLast();
        vl->removeWidget(mv);
        delete mv;
        n++;
    }
}

/*
 * реализация класса TMainWindow
 * ГЛАВНОЕ ОКНО ПРИЛОЖЕНИЯ
*/
TMainWindow::TMainWindow(TOffTic *gst, QWidget *parent)
    : QWidget(parent)
{
    gStation = gst;
    TOffTicParam par = gst->getParam();
    pw = new TParamWindow(par);
    ew = new TEventWindow();
    dw = new TOffTicWindow(par);
    hl = new QHBoxLayout(this);
    hl->addWidget(pw);
    hl->addWidget(ew);
    hl->addWidget(dw);
    setWindowTitle("Билетная касса");
    setMinimumSize(1200,600);
    connect(ew,SIGNAL(control(int)),gst,SLOT(control(int)));
    connect(gst,SIGNAL(OffTicState(TOffTicState)),
            this,SLOT(OffTicState(TOffTicState)));
    connect(pw,SIGNAL(changeCount(int)),ew,SLOT(countChanged(int)));
    connect(pw,SIGNAL(changeCount(int)),dw,SLOT(countChanged(int)));
    connect(pw,SIGNAL(changeCount(int)),gStation,SLOT(countChanged(int)));
    connect(pw,SIGNAL(changeNum(int)),gStation,SLOT(numChanged(int)));
}

TMainWindow::~TMainWindow()
{
    delete dw;
    delete ew;
    delete pw;
    delete hl;
}

void TMainWindow::OffTicState(TOffTicState gs)
{
    dw->view(gs);
}
