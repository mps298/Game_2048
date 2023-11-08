#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QRect>
#include <QMessageBox>
#include <QTime>
#include <QPainterPath>

#include "mycell.h"

class FieldView : public QWidget
{
    Q_OBJECT

    const int cellSize = 100;
    const int fieldSideLength = 4;
    int score = 0;
    const int borderWidth = 10;
    const int radius = 50;

    QVector<MyCell> myCells;
    MyCell* newCell = nullptr;



public:
    explicit FieldView(QWidget *parent = nullptr);

    void addNumber();

    int getScore() const;
    void setScore(int value);

signals:

    void scoreChangedSignal(int);
    void gameOverSignal(int);

public slots:

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // FIELDVIEW_H
