#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onReadyRead();
    //void writeMessage();
    void getMessage();

private:
    Ui::MainWindow *ui;
    QTcpSocket  _socket;
};

#endif // MAINWINDOW_H

