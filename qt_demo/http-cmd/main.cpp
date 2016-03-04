#include <QtCore>
#include <iostream>

#include "httpget.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: httpget url [outfile]" << std::endl
                  << "Example:" << std::endl
                  << "    httpget http://doc.trolltech.com/index.html"
                  << std::endl;
        return 1;
    }

    QString url_str = argv[1];

    QString file_name;
    if (argc == 3) {
        file_name = argv[2];
    }

    HttpGet getter;
    QObject::connect(&getter, SIGNAL(done()), &app, SLOT(quit()));

    // down url
    getter.get_file(QUrl(url_str), file_name);
    if (getter.has_error()) {
        getter.print_log(std::cerr);
        return 2;
    }

    return app.exec();
}
