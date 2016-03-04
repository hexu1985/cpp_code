TEMPLATE      = app
HEADERS       = diagramwindow.h \
                link.h \
                node.h \
                propertiesdialog.h \
                undirected_graph.h
SOURCES       = diagramwindow.cpp \
                link.cpp \
                main.cpp \
                node.cpp \
                propertiesdialog.cpp \
                undirected_graph.cpp
FORMS         = propertiesdialog.ui
RESOURCES     = resources.qrc
QT += widgets gui
CONFIG += c++11
