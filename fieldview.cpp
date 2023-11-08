#include "fieldview.h"


void FieldView::addNumber()
{
    bool thereIsEmptyCell = false;
    bool canBeDoubled = false;

    for (int i = 0; i < myCells.size(); i++)
    {
        if (!myCells.at(i).getNumber())
        {
            thereIsEmptyCell = true;
            break;
        }
    }

    if (thereIsEmptyCell)
    {
        int index = 0;
        do
        {
            index = rand()%myCells.size();
        }
        while (myCells.at(index).getNumber());

        if (rand()%3) { myCells[index].setNumber(2);    }
        else {  myCells[index].setNumber(4);    }

        newCell = &myCells[index];
    }

    thereIsEmptyCell = false;

    for (int i = 0; i < myCells.size(); i++)
    {
        if (!myCells.at(i).getNumber())
        {
            thereIsEmptyCell = true;
            break;
        }

        if((i%fieldSideLength != fieldSideLength-1 && myCells.at(i).getNumber() == myCells.at(i+1).getNumber())
                || (i/fieldSideLength != fieldSideLength-1 && myCells.at(i).getNumber() == myCells.at(i+fieldSideLength).getNumber()))
        {
            canBeDoubled = true;
        }
    }

    qDebug()<<"empty = "<<thereIsEmptyCell;
    qDebug()<<"double = "<<canBeDoubled;

    if (!thereIsEmptyCell && !canBeDoubled)
    {
        emit gameOverSignal(score);

        myCells.fill(MyCell());
        score = 0;
        emit scoreChangedSignal(score);

        addNumber();
    }
}

void FieldView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    {


        for (int i = 0; i < myCells.size(); i++)
        {
            if (!myCells.at(i).getNumber()) { continue; }
            if (!i%fieldSideLength) { continue; }


            int index = i;

            while (index%fieldSideLength && !myCells.at(index-1).getNumber())
            {
                int tmpNum = myCells.at(index).getNumber();
                myCells[index].setNumber(myCells.at(index-1).getNumber());
                myCells[index-1].setNumber(tmpNum);
                index--;
            }
        }

        for (int i = 0; i < myCells.size()-1; i++)
        {
            if (i%fieldSideLength == fieldSideLength-1 || !myCells.at(i).getNumber())
            {
                continue;
            }

            if (myCells.at(i).getNumber() == myCells.at(i+1).getNumber())
            {
                myCells[i].setNumber(myCells.at(i).getNumber()*2);
                myCells[i+1].setNumber(0);
                emit scoreChangedSignal(myCells.at(i).getNumber());
            }
        }

        break;
    }

    case Qt::Key_Right:
    {


        for (int i = myCells.size()-1; i >= 0; i--)
        {
            if (!myCells.at(i).getNumber()) { continue; }
            if (i%fieldSideLength == fieldSideLength-1) { continue; }


            int index = i;

            while (index%fieldSideLength != fieldSideLength-1 && !myCells.at(index+1).getNumber())
            {
                int tmpNum = myCells.at(index).getNumber();
                myCells[index].setNumber(myCells.at(index+1).getNumber());
                myCells[index+1].setNumber(tmpNum);
                index++;
            }
        }

        for (int i = 0; i < myCells.size()-1; i++)
        {
            if (i%fieldSideLength == fieldSideLength-1 || !myCells.at(i).getNumber())
            {
                continue;
            }

            if (myCells.at(i).getNumber() == myCells.at(i+1).getNumber())
            {
                myCells[i+1].setNumber(myCells.at(i).getNumber()*2);
                myCells[i].setNumber(0);
                emit scoreChangedSignal(myCells.at(i+1).getNumber());
            }
        }

        break;
    }

    case Qt::Key_Up:
    {


        for (int i = fieldSideLength; i < myCells.size(); i++)
        {
            if (!myCells.at(i).getNumber()) { continue; }

            int index = i;

            while (index/fieldSideLength && !myCells.at(index-fieldSideLength).getNumber())
            {
                int tmpNum = myCells.at(index).getNumber();
                myCells[index].setNumber(myCells.at(index-fieldSideLength).getNumber());
                myCells[index-fieldSideLength].setNumber(tmpNum);
                index-=fieldSideLength;
            }
        }

        for (int i = 0; i < myCells.size()-fieldSideLength; i++)
        {
            if (i/fieldSideLength == fieldSideLength-1 || !myCells.at(i).getNumber())
            {
                continue;

            }

            if (myCells.at(i).getNumber() == myCells.at(i+fieldSideLength).getNumber())
            {
                myCells[i].setNumber(myCells.at(i).getNumber()*2);
                myCells[i+fieldSideLength].setNumber(0);
                emit scoreChangedSignal(myCells.at(i).getNumber());
            }
        }

        break;
    }

    case Qt::Key_Down:
    {


        for (int i = myCells.size()-fieldSideLength; i >= 0; i--)
        {
            if (!myCells.at(i).getNumber()) { continue; }
            if (i/fieldSideLength == fieldSideLength-1) { continue; }


            int index = i;

            while (index/fieldSideLength != fieldSideLength-1 && !myCells.at(index+fieldSideLength).getNumber())
            {
                int tmpNum = myCells.at(index).getNumber();
                myCells[index].setNumber(myCells.at(index+fieldSideLength).getNumber());
                myCells[index+fieldSideLength].setNumber(tmpNum);
                index += fieldSideLength;
            }
        }

        for (int i = 0; i < myCells.size()-fieldSideLength; i++)
        {
            if (i/fieldSideLength == fieldSideLength-1 || !myCells.at(i).getNumber())
            {
                continue;
            }

            if (myCells.at(i).getNumber() == myCells.at(i+fieldSideLength).getNumber())
            {
                myCells[i+fieldSideLength].setNumber(myCells.at(i).getNumber()*2);
                myCells[i].setNumber(0);
                emit scoreChangedSignal(myCells.at(i+fieldSideLength).getNumber());
            }
        }

        break;
    }

    default:
        return;
    }

    addNumber();

    if (newCell)
    {
//        for (int i = 0; i < 4; i++)
//        {
//            QTime time;
//            time.start();
//            while (time.elapsed()<=interval) {}

//            QColor tmpColor = newCell->getNumberColor();
//            newCell->setNumberColor(newCell->getCellColor());
//            newCell->setCellColor(tmpColor);

//            repaint();
//        }

        newCell = nullptr;
    }

    repaint();
}

void FieldView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    for (int i = 0; i < myCells.size(); i++)
    {
        const MyCell* currentCell = &myCells.at(i);

        painter.setPen(QPen(QBrush(Qt::gray), borderWidth));
        QPoint point ((i%4)*cellSize + borderWidth/2, (i/4)*cellSize + borderWidth/2);
        QRect rect = QRect(point, QSize(cellSize,cellSize));
        painter.setRenderHint(QPainter::Antialiasing,true);

        QPainterPath rounded_rect;
        rounded_rect.addRoundRect(rect, radius, radius);
        painter.setClipPath(rounded_rect);

        painter.drawRoundRect(rect, radius, radius);
        painter.fillPath(rounded_rect,QBrush(currentCell->getCellColor()));


        painter.drawRoundRect(rect, radius, radius);


        painter.setPen(QPen(QBrush(currentCell->getNumberColor()), 5));

        if (currentCell->getNumber())
        {
            int fontSize = 0;
            if (currentCell->getNumber()<100) {    fontSize = 4; }
            else if (currentCell->getNumber()<1000) {    fontSize = 6; }
            else {    fontSize = 8; }

            painter.setFont(QFont("Times", cellSize/fontSize, QFont::Bold));
            QString str;
            str.setNum(currentCell->getNumber());
            painter.drawText(rect, Qt::AlignCenter, str);
        }
    }
}


int FieldView::getScore() const
{
    return score;
}

void FieldView::setScore(int value)
{
    score = value;
}

FieldView::FieldView(QWidget *parent) : QWidget(parent)
{
    myCells = QVector<MyCell>(fieldSideLength*fieldSideLength);
    addNumber();
//    repaint();
}

