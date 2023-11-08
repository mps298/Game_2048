#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fieldview.h"
#include <QFile>
#include <QInputDialog>
#include <QByteArray>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void scoreChangedSlot(int value);
    void gameOverSlot(int score);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FieldView *fieldView;

    int bestScore = 0;
    QString bestScoreName = QString();
    bool newBestScore = false;
    const QString bestScoreFileName = QString("best_score.txt");

};

#endif // MAINWINDOW_H
