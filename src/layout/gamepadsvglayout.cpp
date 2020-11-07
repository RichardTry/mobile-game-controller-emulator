#include "gamepadsvglayout.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>

GamepadSvgLayout::GamepadSvgLayout() {
    m_svgRect = QRect(0, 0, 200, 200);
    m_rect = QRect(0, 0, 200, 200);
}

GamepadSvgLayout::~GamepadSvgLayout() {
}

void GamepadSvgLayout::load() {
    QFile file(":/controller-layout.svg");

    QMessageBox messageBox;
    messageBox.setWindowTitle("Error");

    if(!file.exists()) {
        messageBox.setText("No such file " + file.fileName());
        messageBox.exec();
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        messageBox.setText("Failed to open file " + file.fileName());
        messageBox.exec();
    }

    QByteArray data = file.readAll();
    file.close();

    QXmlStreamReader *xmlReader = new QXmlStreamReader(data);

    // Calculate the rects for each button type
    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {

            // Get svg dimensions
            if(xmlReader->name() == "svg") {
                auto attributes = xmlReader->attributes();
                const int width = attributes.value("width").toString().toInt();
                const int height = attributes.value("height").toString().toInt();
                m_svgRect.setWidth(width);
                m_svgRect.setHeight(height);
                m_svgRect.setTopLeft(QPoint(0, 0));
                continue;
            }

            auto attributes = xmlReader->attributes();
            const QString id = attributes.value("id").toString();
            const Button button = buttonForLabel(id.toUpper());
            // Check if button was added before
            if(m_buttonRects.contains(button)) {
                messageBox.setText("Button defined twice in svg : " + id);
                messageBox.exec();
            }
            // Only rectangular and circular shapes supported
            if(button != Button::COUNT) { // Circular svg items
                if(attributes.hasAttribute("r")) {
                    const qreal radius = attributes.value("r").toString().toDouble();
                    const qreal cx = attributes.value("cx").toString().toDouble();
                    const qreal cy = attributes.value("cy").toString().toDouble();
                    QRectF buttonRect(cx - radius, cy - radius, radius * 2, radius * 2);
                    m_buttonRects[button] = buttonRect;
                }
                else if(attributes.hasAttribute("width")) { // Rectangular svg items
                    const qreal width = attributes.value("width").toString().toDouble();
                    const qreal height = attributes.value("height").toString().toDouble();
                    const qreal x = attributes.value("x").toString().toDouble();
                    const qreal y = attributes.value("y").toString().toDouble();
                    QRectF buttonRect(x, y, width, height);
                    m_buttonRects[button] = buttonRect;
                }
            }
        }
    }
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
