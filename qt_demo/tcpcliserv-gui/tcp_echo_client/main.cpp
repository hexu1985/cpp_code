#include <QApplication>
#include "tcp_echo_client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TcpEchoClient client;
    client.show();

    return app.exec();
}
