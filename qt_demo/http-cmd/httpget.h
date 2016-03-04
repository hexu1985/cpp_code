#ifndef HTTPGET_H
#define HTTPGET_H

#include <memory>
#include <sstream>
#include <iostream>
#include <QFile>
#include <QtNetwork>

class QUrl;

class HttpGet : public QObject
{
    Q_OBJECT

public:
    HttpGet(QObject *parent = 0);
    HttpGet(QObject *parent, std::shared_ptr<QNetworkAccessManager> http);

    void get_file(const QUrl &url, const QString &file_name = "");

    void print_log(std::ostream &out) {
        out << log_.str();
    }

    bool has_error() const {
        return has_error_;
    }

private:
    bool check_url(const QUrl &url);

    bool open_file(const QUrl &url, const QString &file_name);

    void request_url(const QUrl &url);

signals:
    void done();

private slots:
    void httpDone();

private:
    std::shared_ptr<QNetworkAccessManager> http_;
    std::shared_ptr<QNetworkReply> reply_;
    std::shared_ptr<QFile> file_;
    bool has_error_;
    std::ostringstream log_;
};

#endif
