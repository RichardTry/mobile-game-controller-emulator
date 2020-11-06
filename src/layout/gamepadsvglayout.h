#ifndef SVGLAYOUT_H
#define SVGLAYOUT_H

#include <QLayout>
#include <QObject>
#include <QXmlStreamReader>
#include <QMap>
#include "common/common.h"

class GamepadSvgLayout : public QLayout {
    Q_OBJECT
public:
    GamepadSvgLayout();
    ~GamepadSvgLayout();

    void load();

    void add(QLayoutItem *item, const Button &button);

    void addWidget(QWidget *widget, const Button &button);

    // Mandatory to implement
    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    void setGeometry(const QRect &r) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    int count() const override;

    // Recommended
    QSize maximumSize() const override;
    QSize minimumSize() const override;
    int heightForWidth(int) const override;
    bool hasHeightForWidth() const override;

private:
    struct ItemWrapper {
        ItemWrapper(QLayoutItem *i, Button b) {
            item = i;
            button = b;
        }

        QLayoutItem *item;
        Button button;
    };

    enum SizeType { MinimumSize, SizeHint };

    QList<ItemWrapper *> m_itemList;
    QMap <Button, QRectF> m_buttonRects;
    QRectF m_rect;
    QRectF m_svgRect;
    QPointF m_scale; // scale = layout (this) dimensions / SVG dimensions or m_rect/m_svgRect
};

#endif // SVGLAYOUT_H
