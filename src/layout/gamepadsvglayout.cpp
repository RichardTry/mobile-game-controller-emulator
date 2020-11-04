#include "gamepadsvglayout.h"

GamepadSvgLayout::GamepadSvgLayout() {

}

GamepadSvgLayout::~GamepadSvgLayout() {

}
QString GamepadSvgLayout::getSvgLabel(const Gamepad::Button &button) const {
    switch (button) {
        case Gamepad::Button::X: return "X";
        case Gamepad::Button::Y: return "Y";
        case Gamepad::Button::B: return "B";
        case Gamepad::Button::A: return "A";
        case Gamepad::Button::START: return "START";
        case Gamepad::Button::BACK: return "BACK";
        case Gamepad::Button::GUIDE: return "GUIDE";
        case Gamepad::Button::LEFTTRIGGER: return "LEFTTRIGGER";
        case Gamepad::Button::RIGHTTRIGGER: return "RIGHTTRIGGER";
        case Gamepad::Button::LEFTBUMPER: return "LEFTBUMPER";
        case Gamepad::Button::RIGHTBUMPER: return "RIGHTBUMPER";
        case Gamepad::Button::UP: return "UP";
        case Gamepad::Button::DOWN: return "DOWN";
        case Gamepad::Button::LEFT: return "LEFT";
        case Gamepad::Button::RIGHT: return "RIGHT";
    };

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
