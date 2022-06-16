#include "cashier.h"

/*
 * реализация класса TKey
 * КЛЮЧ МЕСТА У ОКОШКА
*/
TKey::TKey() : QObject()
{
    state = false;
}

TKey::TKey(const TKey& k) : QObject()
{
    *this = k;
}

TKey& TKey::operator=(const TKey& k)
{
    state=k.state;
    return *this;
};

bool TKey::control()
{
    state = !state;
    return state;
}

/*
 * реализация класса TCash
 * ОКОШКО КАССЫ
*/
TCash::TCash() : QObject()
{
    counter = 0;
}

TCash::TCash(const TCash& m) : QObject()
{
    *this = m;
}

TCash& TCash::operator=(const TCash& m)
{
    CashKey = m.CashKey;
    counter = m.counter;
    return *this;
}

void TCash::tact()
{
    if(counter<2) counter++;
    else
    {
        counter=0;
        if (CashKey.getState()) CashKey.control();
        if (que>0){
                CashKey.control();
                que--;
        }
    }
}

TCashState TCash::getState()
{
    TCashState ms;
    ms.active  = CashKey.getState();
    ms.que=que;
    ms.counter = counter;
    return ms;
}

bool TCash::control()
{
    return CashKey.control();
}


void TCash::queControl() //TODO убрать параметры
{
   que++;
}
