#include "common/common.h"
#include <QPixmap>
#include <QFile>
#include <QSvgRenderer>
#include <QPainter>

QMap <int, QSharedPointer<QPixmap>> Common::m_iconMap;
QMap <int, QSharedPointer<QPixmap>> Common::m_iconPressedMap;

void Common::loadIcons() {
    if(!m_iconMap.isEmpty())
        return;

    m_iconMap[Button::UP | Button::LEFT] = QSharedPointer <QPixmap> (new QPixmap(":/up-left.svg"));
    m_iconMap[Button::UP | Button::RIGHT] = QSharedPointer <QPixmap> (new QPixmap(":/up-right.svg"));
    m_iconMap[Button::DOWN | Button::LEFT] = QSharedPointer <QPixmap> (new QPixmap(":/down-left.svg"));
    m_iconMap[Button::DOWN | Button::RIGHT] = QSharedPointer <QPixmap> (new QPixmap(":/down-right.svg"));

    for(int i = Button::X; i < Button::COUNT; i*=2) {
        QString filename = ":/" + labelForButton(Button(i)).toLower() + ".svg";
        if(!QFile::exists(filename))
            continue;
        m_iconMap[i] = QSharedPointer <QPixmap> (new QPixmap(filename));
    }
}

QSharedPointer <QPixmap> Common::buttonIcon(const int& btns) {
    if(m_iconMap.isEmpty())
        loadIcons();

    if(m_iconMap.contains(btns))
        return m_iconMap[btns];
    else
        return nullptr;
}

QSharedPointer <QPixmap> Common::buttonIcon(const int& btn, const QSize &size) {
    if(m_iconMap.contains(btn) && m_iconMap[btn]->size() == size)
        return m_iconMap[btn];

    QString filename = ":/" + labelForButton(Button(btn)).toLower() + ".svg";
    if(!QFile::exists(filename))
        return nullptr;

    QSharedPointer <QPixmap> pixmap(new QPixmap(size));
    pixmap->fill(QColor(0, 0, 0, 0));
    QSvgRenderer renderer(filename);
    QPainter painter(pixmap.data());
    painter.setBackgroundMode(Qt::BGMode::TransparentMode);
    renderer.render(&painter, QRectF(QPointF(0, 0), size));

    m_iconMap[btn] = pixmap;

    return m_iconMap[btn];
}

QSharedPointer <QPixmap> Common::buttonPressedIcon(const int &btn, const QSize &size) {
    if(m_iconPressedMap.contains(btn) && m_iconPressedMap[btn]->size() == size)
        return m_iconPressedMap[btn];

    QString filename = ":/" + labelForButton(Button(btn)).toLower() + ".svg";
    if(!QFile::exists(filename))
        return nullptr;

    QSharedPointer <QPixmap> pixmap(new QPixmap(size));
    pixmap->fill(QColor(0, 0, 0, 0));
    QSvgRenderer renderer(filename);
    QPainter painter(pixmap.data());
    painter.setBackgroundMode(Qt::BGMode::TransparentMode);
    renderer.render(&painter, QRectF(QPointF(0, 0), size));

    m_iconPressedMap[btn] = pixmap;

    return m_iconPressedMap[btn];
}
