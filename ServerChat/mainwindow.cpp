#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server.listen(QHostAddress("127.0.0.1"), 4444);
     connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
     connect(ui->send, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
   QTcpSocket *clientSocket = _server.nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
           this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}

void MainWindow::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    ui->history->append(tr("Client: %1").arg(QString(datas)));
}

void MainWindow::sendMessage(){
    QString message = ui->message->toPlainText();

    ui->message->clear();
    QByteArray ba = message.toLocal8Bit();
    const char *c_message = ba.data();

    for(auto &client : _sockets) {
        client->write(c_message);
        ui->history->setTextColor("green");
        ui->history->append(tr("You: %1").arg(message));
    }
}
