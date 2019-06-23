#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _socket.connectToHost(QHostAddress("127.0.0.1"), 4444);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(getMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    QByteArray datas = _socket.readAll();
    qDebug() << datas;
    ui->history->append(tr("Server: %1").arg(QString(datas)));
}

void MainWindow::getMessage(){
    QString message = ui->message->toPlainText();
    ui->message->clear();

    QByteArray ba = message.toLocal8Bit();
    const char *c_message = ba.data();

    _socket.write(c_message, strlen(c_message));

    ui->history->setTextColor("green");

    ui->history->append(tr("You: %1").arg(message));

}

