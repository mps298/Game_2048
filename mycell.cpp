#include "mycell.h"

int MyCell::getNumber() const
{
    return number;
}

void MyCell::setNumber(int value)
{
    number = value;

    switch (number) {

    case 0: cellColor = QColor(220,220,220); numberColor = QColor(220,220,220); break;
    case 2: cellColor = QColor(169,169,169); numberColor = QColor(50,50,50);break;
    case 4: cellColor = QColor(110,110,110); numberColor = Qt::white; break;
    case 8: cellColor = QColor(189, 183, 107); numberColor = Qt::white; break;
    case 16: cellColor = QColor(210, 180, 140); numberColor = Qt::white; break;
    case 32: cellColor = QColor(218, 165, 32); numberColor = Qt::white; break;
    case 64: cellColor = QColor(205, 133, 63); numberColor = Qt::white; break;
    case 128: cellColor = QColor(255, 215, 0); numberColor = Qt::white; break;
    case 256: cellColor = QColor(210, 105, 30); numberColor = Qt::white; break;
    case 512: cellColor = QColor(160, 82, 45); numberColor = Qt::white; break;
    case 1024: cellColor = QColor(139, 69, 19); numberColor = Qt::white; break;
    case 2048: cellColor = QColor(255, 69, 0); numberColor = Qt::white; break;

    default: cellColor = Qt::black; numberColor = Qt::red; break;
    }




}



QColor MyCell::getCellColor() const
{
    return cellColor;
}

QColor MyCell::getNumberColor() const
{
    return numberColor;
}

void MyCell::setNumberColor(const QColor &value)
{
    numberColor = value;
}

void MyCell::setCellColor(const QColor &value)
{
    cellColor = value;
}

MyCell::MyCell()
{

}

