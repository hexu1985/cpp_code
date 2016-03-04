QT += network widgets

HEADERS += httpwindow.h
SOURCES += httpwindow.cpp \
           main.cpp
FORMS += authenticationdialog.ui
CONFIG += debug

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/http
INSTALLS += target
