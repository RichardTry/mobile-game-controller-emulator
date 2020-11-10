#include "common/common.h"
#include <QPixmap>
#include <QFile>

QMap <int, QSharedPointer<QPixmap>> Common::m_iconMap;

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
