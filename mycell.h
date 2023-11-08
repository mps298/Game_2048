#ifndef MYCELL_H
#define MYCELL_H

#include <QColor>
#include <QDebug>

class MyCell
{
private:
    int number = 0;
    QColor cellColor = QColor(220,220,220);
    QColor numberColor = QColor(50,50,50);

public:
    MyCell();


    int getNumber() const;
    void setNumber(int value);

    QColor getCellColor() const;
    QColor getNumberColor() const;
    void setNumberColor(const QColor &value);
    void setCellColor(const QColor &value);
};

#endif // MYCELL_H
