#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout> 
#include <QVBoxLayout> 
#include <QHBoxLayout> 
#include <QMessageBox>
#include <string>
#include <iostream>
#include <iomanip>

#include "tcp_echo_client.h"

TcpEchoClient::TcpEchoClient(QWidget *parent): QDialog(parent)
{
    host_prompt_ = new QLabel(tr("&Host:"));
    host_input_ = new QLineEdit;
    host_prompt_->setBuddy(host_input_);
    host_input_->setText("localhost");

    port_prompt_ = new QLabel(tr("&Port:"));
    port_input_ = new QLineEdit;
    port_prompt_->setBuddy(port_input_);
    port_input_->setText("50001");

    connect_button_ = new QPushButton(tr("&Connect"));
    disconnect_button_ = new QPushButton(tr("&Disconnect"));
    disconnect_button_->setEnabled(false);

    send_button_ = new QPushButton(tr("&Send"));
    send_button_->setEnabled(false);
    send_input_ = new QLineEdit;
    send_input_->setText("hello world!");
    send_input_ = new QLineEdit;

    QGridLayout *left_layout = new QGridLayout;
    left_layout->addWidget(host_prompt_, 0, 0);
    left_layout->addWidget(host_input_, 0, 1);
    left_layout->addWidget(port_prompt_, 1, 0);
    left_layout->addWidget(port_input_, 1, 1);

    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->addWidget(connect_button_); 
    right_layout->addWidget(disconnect_button_); 
//    right_layout->addStretch();

    QHBoxLayout *top_layout = new QHBoxLayout;
    top_layout->addLayout(left_layout);
    top_layout->addLayout(right_layout);

    QHBoxLayout *bottom_layout = new QHBoxLayout;
    bottom_layout->addWidget(send_input_);
    bottom_layout->addWidget(send_button_);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);

    setLayout(main_layout);

    setWindowTitle(tr("tcp echo client"));

    connect(connect_button_, SIGNAL(clicked()), this, SLOT(do_connect()));
    connect(disconnect_button_, SIGNAL(clicked()), this, SLOT(do_disconnect()));
    connect(send_button_, SIGNAL(clicked()), this, SLOT(do_send()));
}

TcpEchoClient::~TcpEchoClient() {}

void TcpEchoClient::do_connect()
{
    std::string host, port;
    host = host_input_->text().toStdString();
    port = port_input_->text().toStdString();
    tcp_stream_.reset(new boost::asio::ip::tcp::iostream(host, port));
    if (tcp_stream_->good()) {
        host_input_->setEnabled(false);
        port_input_->setEnabled(false);
        connect_button_->setEnabled(false);
        disconnect_button_->setEnabled(true);
        send_button_->setEnabled(true);
        QMessageBox::information(this, tr("Connect"), tr("Connect success!"));
    } else {
        QMessageBox::critical(this, tr("Connect"), tr("Connect Fault!"));
    }
}

void TcpEchoClient::do_disconnect()
{
    tcp_stream_.reset(nullptr);
    host_input_->setEnabled(true);
    port_input_->setEnabled(true);
    connect_button_->setEnabled(true);
    disconnect_button_->setEnabled(false);
    send_button_->setEnabled(false);
    QMessageBox::information(this, tr("Disconnect"), tr("Disconnect success!"));
}

void TcpEchoClient::do_send()
{
    std::string line = send_input_->text().toStdString();
    if (line.empty()) {
        QMessageBox::information(this, tr("Send"), tr("Send message is empty!"));
        return;
    }
    assert(tcp_stream_ && tcp_stream_->good());
    *tcp_stream_ << line << std::endl; 
    std::string reply;
    if(std::getline(*tcp_stream_, reply)) {
        assert(line == reply);
        QMessageBox::information(this, tr("Reply"), QString::fromStdString(reply));
    } else {
        QMessageBox::critical(this, tr("Reply"), "Error when read reply");
        tcp_stream_.reset(nullptr);
        host_input_->setEnabled(true);
        port_input_->setEnabled(true);
        connect_button_->setEnabled(true);
        disconnect_button_->setEnabled(false);
        send_button_->setEnabled(false);
    }
}

