#include <QComboBox>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <cassert>
#include "load_host_list.h"

void load_host_list(QComboBox *box)
{
    assert(box);

    box->clear();
    typedef QList<QHostAddress> AddressList;
    AddressList addr_list = QNetworkInterface::allAddresses();
    for (const QHostAddress &addr: addr_list) {
        box->addItem(addr.toString());
    }
#if 0
    AddressList::iterator first, last;
    last = address_list.end();
    for (first = address_list.begin(); first != last; ++first) {
        box->addItem(first->toString());
    }
#endif
}

