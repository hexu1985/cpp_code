#include <QApplication>
#include "tcp_echo_server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TcpEchoServer server;
    server.show();

    return app.exec();
}
