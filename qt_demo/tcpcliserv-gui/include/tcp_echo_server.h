#ifndef TCP_ECHO_SERVER_H
#define TCP_ECHO_SERVER_H

#include <QDialog>
#include <cstdint>
#include <boost/asio.hpp>

class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;

class TcpEchoServer: public QDialog {
    Q_OBJECT

public:
    TcpEchoServer(QWidget *parent = 0);
    ~TcpEchoServer();

private slots:
    void do_start();

private:
    QLabel *host_prompt_;
    QComboBox *host_select_;

    QLabel *port_prompt_;
    QLineEdit *port_input_;

    QPushButton *start_button_;

    boost::asio::io_service io_service_;
};

#endif

