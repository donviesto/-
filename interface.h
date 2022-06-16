#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ticketoffice.h"
#include "tickofficeview.h"

/*
 * описание класса TParamWindow
 * ОКНО ПАРАМЕТРОВ БИЛЕТНОЙ КАССЫ
*/
class TParamWindow : public QWidget
{
    Q_OBJECT

    QLabel      *h;
    QLabel      *l;
    QLabel      *k;
    QSpinBox    *n;
    QSpinBox    *m;
    QPushButton *b1;
    QPushButton *b2;

    int nvalue;
    int qvalue;

private slots:
    void countChanged(int);
    void numChanged(int);
    void changeCashCount();
    void restoreCashCount();

signals:
    void changeCount(int);
    void changeNum(int);

public:
    TParamWindow(TOffTicParam,QWidget *parent = 0);
    ~TParamWindow();
};

/*
 * описание класса TEventWindow
 * ОКНО УПРАВЛЕНИЕ КЛИЕНТАМИ КАССЫ
*/
class TEventWindow : public QWidget
{
    Q_OBJECT

    QLabel      *h;
    QPushButton *b1;
    QPushButton *b2;

private slots:
    void stationControl();

signals:
    void control(int);
    void control2(int);

public:
    TEventWindow(QWidget *parent = 0);
    ~TEventWindow();

};

/*
 * описание класса TOffTicWindow
 * ОКНО ОТОБРАЖЕНИЯ КАССЫ
*/
class TOffTicWindow : public QWidget
{
    Q_OBJECT

    QHBoxLayout   *hl;
    QVBoxLayout   *vl;

    TKeyView *kv;
    QList<TCashView*> mvl;

public:
    TOffTicWindow(TOffTicParam,QWidget *parent = 0);
    ~TOffTicWindow();

    void view(TOffTicState);

public slots:
    void countChanged(int);
};

class TMainWindow : public QWidget
{
    Q_OBJECT

    QHBoxLayout   *hl;
    TParamWindow  *pw;
    TEventWindow  *ew;
    TOffTicWindow *dw;

    TOffTic *gStation;

public:
    TMainWindow(TOffTic*,QWidget *parent = 0);
    ~TMainWindow();

public slots:
    void OffTicState(TOffTicState);
};

#endif // INTERFACE_H
