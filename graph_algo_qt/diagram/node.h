#ifndef NODE_H
#define NODE_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

class Link;

class Node : public QGraphicsItem
{
    Q_DECLARE_TR_FUNCTIONS(Node)

public:
    Node(int id);
    ~Node();

    void setText(const QString &text);
    QString text() const;
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void addLink(Link *link);
    void removeLink(Link *link);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    int id() const;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    QSet<Link *> myLinks;
    QString myText;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;
    const int id_;
};

#endif
