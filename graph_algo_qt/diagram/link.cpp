#include <QtGui>

#include "link.h"
#include "node.h"

Link::Link(Node *fromNode, Node *toNode)
{
    myFromNode = fromNode;
    myToNode = toNode;

    myFromNode->addLink(this);
    myToNode->addLink(this);

    setFlags(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);

    setColor(Qt::darkRed);
    trackNodes();
}

Link::~Link()
{
    myFromNode->removeLink(this);
    myToNode->removeLink(this);
}

Node *Link::fromNode() const
{
    return myFromNode;
}

Node *Link::toNode() const
{
    return myToNode;
}

void Link::setColor(const QColor &color, qreal width)
{
    setPen(QPen(color, width));
}

QColor Link::color() const
{
    return pen().color();
}

void Link::trackNodes()
{
    setLine(QLineF(myFromNode->pos(), myToNode->pos()));
}

void Link::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
#if 0
    painter->setPen(pen());
    painter->drawRect(QRectF(myFromNode->pos(), myToNode->pos()));
#endif
    QGraphicsLineItem::paint(painter, option, widget);
}

