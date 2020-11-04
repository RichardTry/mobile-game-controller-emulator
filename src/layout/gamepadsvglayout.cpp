#include "gamepadsvglayout.h"

GamepadSvgLayout::GamepadSvgLayout() {

}

GamepadSvgLayout::~GamepadSvgLayout() {
}

void GamepadSvgLayout::addItem(QLayoutItem *item) {

}

QSize GamepadSvgLayout::sizeHint() const {

}

void GamepadSvgLayout::setGeometry(const QRect &r) {

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

QSize GamepadSvgLayout::maximumSize() const {

}

QSize GamepadSvgLayout::minimumSize() const {

}

int GamepadSvgLayout::heightForWidth(int) const {

}

bool GamepadSvgLayout::hasHeightForWidth() const {

}
