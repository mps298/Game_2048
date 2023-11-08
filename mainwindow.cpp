#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::scoreChangedSlot(int value)
{
    ui->widget->setScore(ui->widget->getScore() + value);

    if(ui->widget->getScore() > bestScore)
    {
        bestScore = ui->widget->getScore();
        bestScoreName = "YOU";
        newBestScore = true;
    }

    QString scoreStr;
    scoreStr.setNum(ui->widget->getScore());
    QString bestScoreStr;
    bestScoreStr.setNum(bestScore);

    ui->scoreLabel->setText("Score: " + scoreStr);

    if (bestScoreName != QString())
    {
        ui->bestScoreLabel->setText("Best score: " + bestScoreStr + " (" + bestScoreName + ")");
    }
    else
    {
        ui->bestScoreLabel->setText("Best score: " + bestScoreStr);
    }

}

void MainWindow::gameOverSlot(int score)
{
    QString scoreStr;
    scoreStr.setNum(score);
    QMessageBox::information(this, tr("Game Over"), tr("GAME OVER\nYour score is ") + scoreStr);

    if (newBestScore)
    {
        QString newBestScoreStr;
        newBestScoreStr.setNum(bestScore);


        QString newChampionName = QInputDialog::getText(this, QString(),
                                             tr(QString("You set a new best score: " + newBestScoreStr + "\nName: ").toLatin1().data()));

        if (!newChampionName.isEmpty())
        {
            bestScoreName = newChampionName;

            QFile file(bestScoreFileName);
            QTextStream stream1(&file);

            if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                 return;
            }

            QString strToSave = newChampionName + "\n" + newBestScoreStr;
            qDebug()<<strToSave;
            stream1 << strToSave;
            stream1.flush();
            file.close();
        }

        newBestScore = false;
    }
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setFixedSize(size());

    connect(ui->widget, SIGNAL(scoreChangedSignal(int)), this, SLOT(scoreChangedSlot(int)));
    connect(ui->widget, SIGNAL(gameOverSignal(int)), this, SLOT(gameOverSlot(int)));

    if (QFile::exists(bestScoreFileName))
    {
        QFile file(bestScoreFileName);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QString bestScoreStr = file.readAll();
            file.close();

             QString::iterator it = bestScoreStr.begin();


             while (*it != '\n')
             {
                 bestScoreName += *it;
                 ++it;
             }

             ++it;

             QString scoreStr;

             while (it != bestScoreStr.end())
             {
                 scoreStr += *it;
                 ++it;
             }

             bestScore = scoreStr.toInt();

             qDebug()<<"best score "<<bestScoreName<<" "<<bestScore;
        }
    }
     emit ui->widget->scoreChangedSignal(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
