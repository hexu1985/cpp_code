#ifndef TCP_ECHO_CLIENT_H
#define TCP_ECHO_CLIENT_H

#include <QDialog>
#include <cstdint>
#include <memory>
#include <boost/asio.hpp>

class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;

class TcpEchoClient: public QDialog {
    Q_OBJECT

public:
    TcpEchoClient(QWidget *parent = 0);
    ~TcpEchoClient();

private slots:
    void do_connect();
    void do_disconnect();
    void do_send();

private:
    QLabel *host_prompt_;
    QLineEdit *host_input_;

    QLabel *port_prompt_;
    QLineEdit *port_input_;

    QPushButton *connect_button_;
    QPushButton *disconnect_button_;

    QLineEdit *send_input_;
    QPushButton *send_button_;

    std::unique_ptr<boost::asio::ip::tcp::iostream> tcp_stream_;
};

#endif

