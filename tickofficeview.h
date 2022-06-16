#ifndef TICKOFFICEVIEW_H
#define TICKOFFICEVIEW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "cashier.h"

/*
 * описание класса TKeyView
 * ВИЗУАЛИЗАЦИЯ СОСТОЯНИЯ СИМУЛЯЦИИ
*/
class TKeyView : public QLabel
{
    Q_OBJECT

public:
    TKeyView(QWidget *parent = 0);

    void view(bool);
};

/*
 * описание класса TCounterView
 * ВИЗУАЛИЗАЦИЯ СЧЕТЧИКА ОЧЕРЕДИ И ТАЙМЕРА
*/
class TCounterView : public QLabel
{
    Q_OBJECT

public:
    TCounterView(QWidget *parent = 0);

    void view(int);
};

/*
 * описание класса TCashView
 * ВИЗУАЛИЗАЦИЯ ОКОШКА БИЛЕТНОЙ КАССЫ
*/
class TCashView : public QWidget
{
    Q_OBJECT

    QHBoxLayout   *hl;

    TKeyView      *kv;
    TCounterView  *cv;
    TCounterView  *qu;

public:
    TCashView(QWidget *parent = 0);

    void view(TCashState);
};

#endif // TICKOFFICEVIEW_H
