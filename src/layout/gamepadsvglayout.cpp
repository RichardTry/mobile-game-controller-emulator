#include "gamepadsvglayout.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>

GamepadSvgLayout::GamepadSvgLayout() {
    m_svgRect = QRect(0, 0, 200, 200);
    m_rect = QRect(0, 0, 200, 200);
}

GamepadSvgLayout::~GamepadSvgLayout() {
}

void GamepadSvgLayout::load() {
    QSvgRenderer *renderer = new QSvgRenderer(QString(":/controller-layout.svg"));
    m_svgRect.setSize(renderer->defaultSize());

    for(int btn = Button::X; btn < Button::COUNT; btn = btn << 1) {
        const QString label = labelForButton(Button(btn)).toLower();
        if(!renderer->elementExists(label))
            continue;
        QRectF boundingRect = renderer->boundsOnElement(label);
        QTransform transform = renderer->transformForElement(label);
        boundingRect = transform.mapRect(boundingRect);
        m_buttonRects[Button(btn)] = boundingRect;
    }

    delete renderer;
}

void GamepadSvgLayout::add(QLayoutItem *item, const Button &button) {
    m_itemList.append(new ItemWrapper(item, button));
}

void GamepadSvgLayout::addWidget(QWidget *widget, const Button &button) {
    add(new QWidgetItem(widget), button);
}

// Mandatory to implement
void GamepadSvgLayout::addItem(QLayoutItem *item) {
    add(item, Button::COUNT);
}

QSize GamepadSvgLayout::sizeHint() const {
    return m_svgRect.size().toSize();
}

void GamepadSvgLayout::setGeometry(const QRect &r) {
    m_rect = r;
    m_scale = QPointF(m_rect.width() / m_svgRect.width(), m_rect.height() / m_svgRect.height());

    for(auto item: m_itemList) {
        QRectF bRect = m_buttonRects[item->button];

        const qreal w = bRect.width() * m_scale.x();
        const qreal h = bRect.height() * m_scale.y();

        const qreal x = bRect.topLeft().x() * m_scale.x();
        const qreal y = bRect.topLeft().y() * m_scale.y();

        item->item->widget()->setGeometry(x, y, w, h);
    }
    QLayout::setGeometry(r);
}

QLayoutItem *GamepadSvgLayout::itemAt(int index) const {
    if(index >= 0 && index < m_itemList.size())
        return m_itemList.at(index)->item;
    else
        return nullptr;
}

QLayoutItem *GamepadSvgLayout::takeAt(int index) {
    if(index >= 0 && index < m_itemList.size())
        return m_itemList.takeAt(index)->item;
    else
        return nullptr;
}

int GamepadSvgLayout::count() const {
    return m_itemList.size();
}

// Recommended
QSize GamepadSvgLayout::maximumSize() const {
    return m_svgRect.size().toSize() * 10;
}

QSize GamepadSvgLayout::minimumSize() const {
    return (m_svgRect.size()/4).toSize();
}

int GamepadSvgLayout::heightForWidth(int w) const {
    return w * (m_svgRect.height() / m_svgRect.width());
}

bool GamepadSvgLayout::hasHeightForWidth() const {
    return true;
}
