#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <string>

#include "httpget.h"

using std::cerr;
using std::string;

struct NetworkReplyDeleter {
    void operator ()(QNetworkReply *reply) {
        if (reply) {
            reply->deleteLater();
        }            
    }            
};

HttpGet::HttpGet(QObject *parent)
    : QObject(parent)
{
    http_.reset(new QNetworkAccessManager);
}

HttpGet::HttpGet(QObject *parent, std::shared_ptr<QNetworkAccessManager> http)
    : QObject(parent)
{
    http_ = http;
}

bool HttpGet::check_url(const QUrl &url)
{
    if (!url.isValid()) {
        log_ << "Error: Invalid URL" << '\n';
        return false;
    }

    if (url.scheme() != "http") {
        log_ << "Error: URL must start with 'http:'" << '\n';
        return false;
    }

    if (url.path().isEmpty()) {
        log_ << "Error: URL has no path" << '\n';
        return false;
    }

    return true;
}

bool HttpGet::open_file(const QUrl &url, const QString &file_name)
{
    QString localFileName;
    if (file_name.isEmpty()) {
        localFileName = QFileInfo(url.path()).fileName();
        if (localFileName.isEmpty())
            localFileName = "index.html";
    } else {
        localFileName = file_name;
    } 

    file_.reset(new QFile(localFileName));
    if (!file_->open(QIODevice::WriteOnly)) {
        log_ << "Error: Cannot write file "
                  << qPrintable(file_->fileName()) << ": "
                  << qPrintable(file_->errorString()) << '\n';
        return false;
    }

    return true;
}

void HttpGet::request_url(const QUrl &url)
{
    reply_.reset(http_->get(QNetworkRequest(url)), NetworkReplyDeleter());
    connect(reply_.get(), SIGNAL(finished()), this, SLOT(httpDone()));
}

void HttpGet::get_file(const QUrl &url, const QString &file_name)
{
    log_.str("");

    has_error_ = !check_url(url);
    if (has_error_)
        return;

    has_error_ = !open_file(url, file_name);
    if (has_error_)
        return;

    request_url(url);
}

void HttpGet::httpDone()
{
    QVariant redirectionTarget = 
        reply_->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply_->error()) {  // reply error
        file_->remove();
        has_error_ = true;
        log_ << "Error: reply error, " 
            << qPrintable(reply_->errorString()) << '\n';
    } else if (!redirectionTarget.isNull()) {  // redirection url
        QUrl newUrl = reply_->url().resolved(redirectionTarget.toUrl());
        std::cout << "url [" << qPrintable(reply_->url().toString())
            << "] redirect to [" << qPrintable(newUrl.toString()) << "]? ";
        string ans;
        std::cin >> ans;
        if (ans[0] == 'y' || ans[0] == 'Y') {
            request_url(newUrl);
            return;
        }
    } 
    
    // ok, write file
    file_->write(reply_->readAll()); 
    file_->close();

    if (has_error()) {
        print_log(cerr);
    }

    emit done();
}
