TEMPLATE      = app
QT            = core network
CONFIG       += console debug c++11
CONFIG       -= app_bundle
HEADERS       = httpget.h
SOURCES       = httpget.cpp \
                main.cpp
QT += network
