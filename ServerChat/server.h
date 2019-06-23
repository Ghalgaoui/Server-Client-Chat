#ifndef SERVER_H
#define SERVER_H
#include <QString>

class Server{
public:
    Server();
    void listen();
    void send();
    void receive();

private:
    QString _IP;

};
#endif // SERVER_H
