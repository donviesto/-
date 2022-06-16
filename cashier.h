#ifndef CASHIER_H
#define CASHIER_H

#include <QObject>

/*
 * описание класса TCashState
 * СОСТОЯНИЕ БИЛЕТНОЙ КАССЫ
*/
struct TCashState
{
    bool active;
    int  counter;
    short int que;
};

/*
 * описание класса TKey
 * СОСТОЯНИЕ ОКОШКА КАССЫ
*/
class TKey : public QObject
{
    Q_OBJECT

    bool state;
public:
    TKey();
    TKey(const TKey&);
    TKey& operator=(const TKey&);

    inline bool getState() { return state; }
    bool control();
};

/*
 * описание класса TCash
 * БИЛЕТНОЕ ОКНО КАССЫ
*/
class TCash : public QObject
{
    Q_OBJECT

    TKey CashKey;
    int  counter;
    short int que=0;

public:
    TCash();
    TCash(const TCash&);
    TCash& operator=(const TCash&);

    TCashState getState();
    bool control();
    void queControl();

public slots:
    void tact();
};

#endif // CASHIER_H
