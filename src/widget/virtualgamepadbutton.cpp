#include "virtualgamepadbutton.h"

VirtualGamepadButton::VirtualGamepadButton(const Button &btn, QWidget *parent) : QWidget(parent), m_button(btn) {
}

VirtualGamepadButton::~VirtualGamepadButton() {
}

bool VirtualGamepadButton::event(QEvent *event) {
}

void VirtualGamepadButton::paintEvent(QPaintEvent *event) {
}

int VirtualGamepadButton::heightForWidth(int) const {
}

void VirtualGamepadButton::loadIcons() {
}
