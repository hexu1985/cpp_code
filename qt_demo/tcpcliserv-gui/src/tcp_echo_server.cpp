#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout> 
#include <QVBoxLayout> 
#include <QHBoxLayout> 
#include <QMessageBox>
#include <thread>
#include "tcp_echo_server.h"
#include "load_host_list.h"

void server(boost::asio::io_service &io_service, std::string host, 
    unsigned short port);

void session(std::shared_ptr<boost::asio::ip::tcp::iostream> tcp_stream);

TcpEchoServer::TcpEchoServer(QWidget *parent): QDialog(parent)
{
    host_prompt_ = new QLabel(tr("&Host:"));
    host_select_ = new QComboBox;
    load_host_list(host_select_);
    host_select_->addItem(tr("any"));
    host_prompt_->setBuddy(host_select_);

    port_prompt_ = new QLabel(tr("&Port:"));
    port_input_ = new QLineEdit;
    port_input_->setText(tr("50001"));
    port_prompt_->setBuddy(port_input_);

    start_button_ = new QPushButton(tr("&Start"));

    QGridLayout *left_layout = new QGridLayout;
    left_layout->addWidget(host_prompt_, 0, 0);
    left_layout->addWidget(host_select_, 0, 1);
    left_layout->addWidget(port_prompt_, 1, 0);
    left_layout->addWidget(port_input_, 1, 1);

    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->addWidget(start_button_); 
//    right_layout->addStretch();

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addLayout(left_layout);
    main_layout->addLayout(right_layout);

    setLayout(main_layout);

    setWindowTitle(tr("tcp echo server"));
    connect(start_button_, SIGNAL(clicked()), this, SLOT(do_start()));
}

TcpEchoServer::~TcpEchoServer() {}

void TcpEchoServer::do_start() {
    std::string host;
    host = host_select_->currentText().toStdString();
    bool ok;
    int port = port_input_->text().toInt(&ok);
    if (!ok) {
        QMessageBox::information(this, tr("Check port"), tr("port must be number!"));
        return;
    }
    if (port < 0 || port > 65535) {
        QMessageBox::information(this, tr("Check port"), tr("port must be positive and less than 65536!"));
        return;
    }

    std::thread(&server, std::ref(io_service_), host, static_cast<unsigned short>(port)).detach();

    host_select_->setEnabled(false);
    port_input_->setEnabled(false);
    start_button_->setEnabled(false);
}

void server(boost::asio::io_service &io_service, std::string host, 
    unsigned short port) 
try
{
    boost::asio::ip::address bind_addr;
    if (host == "any") {
        bind_addr = boost::asio::ip::address_v4::any();
    } else {
        bind_addr = boost::asio::ip::address::from_string(host);
    }
    boost::asio::ip::tcp::acceptor a(io_service, 
        boost::asio::ip::tcp::endpoint(bind_addr, static_cast<unsigned short>(port)));
    std::shared_ptr<boost::asio::ip::tcp::iostream> tcp_stream;
    while (true) {
        tcp_stream.reset(new boost::asio::ip::tcp::iostream);
        a.accept(*tcp_stream->rdbuf());
        std::thread(&session, tcp_stream).detach();
    }
}
catch (std::exception &e)
{
    std::cerr << "Exception in server thread: " << e.what() << "\n";
}

void session(std::shared_ptr<boost::asio::ip::tcp::iostream> tcp_stream)
try
{
    std::string line;
    while (getline(*tcp_stream, line)) {
        *tcp_stream << line << std::endl;
    }
}
catch (std::exception &e)
{
    std::cerr << "Exception in session thread: " << e.what() << "\n";
}


