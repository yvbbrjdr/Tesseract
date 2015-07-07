#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QThread>
#include <QString>
#include <QVector>
#include <QQueue>
#include <QtNetwork/QTcpSocket>
#include "../../Tesseract/Block.h"
#include "../../Tesseract/Coordinate.h"
#include "../../Tesseract/Player.h"
#include "../../Tesseract/World.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void log(QString);
    void process(QVector<QString>);
    ~MainWindow();


private slots:
    void on_lineEdit_editingFinished();
    void newConnectionSlot();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;

};

#endif // MAINWINDOW_H
