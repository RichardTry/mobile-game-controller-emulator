#include "gamepadwidget.h"

GamepadWidget::GamepadWidget(QWidget *parent) : QWidget(parent) {
    // Load layout
    m_svgLayout = new GamepadSvgLayout;
    m_svgLayout->load();
    this->setLayout(m_svgLayout);

    // Load dpad
    m_dpad = new VirtualDirectionalPad(this);
    m_svgLayout->addWidget(m_dpad, Button::DPAD);

    // Load right stick
    const int outerRadius = 100;
    const int innerRadius = 30;
    m_rightStick = new VirtualAnalogStick(Button::RIGHTSTICK, this);
    m_rightStick->setOuterRadius(outerRadius);
    m_rightStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_rightStick, Button::RIGHTSTICK);

    // Load left stick
    m_leftStick = new VirtualAnalogStick(Button::LEFTSTICK, this);
    m_leftStick->setOuterRadius(outerRadius);
    m_leftStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_leftStick, Button::LEFTSTICK);

    // Load x, y, b, a buttons
    m_x = new VirtualGamepadButton(Button::X, this);
    m_svgLayout->addWidget(m_x, Button::X);
    m_y = new VirtualGamepadButton(Button::Y, this);
    m_svgLayout->addWidget(m_y, Button::Y);
    m_a = new VirtualGamepadButton(Button::A, this);
    m_svgLayout->addWidget(m_a, Button::A);
    m_b = new VirtualGamepadButton(Button::B, this);
    m_svgLayout->addWidget(m_b, Button::B);

    // Start and back
    m_start = new VirtualGamepadButton(Button::START, this);
    m_svgLayout->addWidget(m_start, Button::START);
    m_back = new VirtualGamepadButton(Button::BACK, this);
    m_svgLayout->addWidget(m_back, Button::BACK);
}
