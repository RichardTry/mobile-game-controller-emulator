#ifndef SVGLAYOUT_H
#define SVGLAYOUT_H

#include <QLayout>
#include <QObject>
#include <QtSvg/QGraphicsSvgItem>
#include "common/common.h"

class GamepadSvgLayout : public QLayout {
    Q_OBJECT
public:
    GamepadSvgLayout();
    ~GamepadSvgLayout();

    void addWidget(QWidget *widget, const Button &button);

    // Mandatory to implement
    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    void setGeometry(const QRect &r) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;

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
    QSize calculateSize(SizeType sizeType) const;
    QString getSvgLabel(const Button &button) const;
    Button getButton(const QString &svgLabel) const;

    QList<ItemWrapper *> m_itemList;
    QMap <Button, QString> m_buttonPropertyMap;
};

#endif // SVGLAYOUT_H
