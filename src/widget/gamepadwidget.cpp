#include "gamepadwidget.h"

GamepadWidget::GamepadWidget(QWidget *parent) : QWidget(parent) {
    // Load layout
    m_svgLayout = new GamepadSvgLayout;
    m_svgLayout->load();
    this->setLayout(m_svgLayout);

    // Load dpad
    m_dpad = new VirtualDirectionalPad(this);
    m_svgLayout->addWidget(m_dpad, Button::DPAD);
    connect(m_dpad, &VirtualDirectionalPad::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_dpad, &VirtualDirectionalPad::released, this, &GamepadWidget::buttonReleased);

    // Load right stick
    const int outerRadius = 100;
    const int innerRadius = 30;
    m_rightStick = new VirtualAnalogStick(Button::RIGHTSTICK, this);
    m_rightStick->setOuterRadius(outerRadius);
    m_rightStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_rightStick, Button::RIGHTSTICK);
    connect(m_rightStick, &VirtualAnalogStick::released, this, &GamepadWidget::stickReleased);
    connect(m_rightStick, &VirtualAnalogStick::pressed, this, &GamepadWidget::stickPressed);
    connect(m_rightStick, &VirtualAnalogStick::moved, this, &GamepadWidget::stickMoved);

    // Load left stick
    m_leftStick = new VirtualAnalogStick(Button::LEFTSTICK, this);
    m_leftStick->setOuterRadius(outerRadius);
    m_leftStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_leftStick, Button::LEFTSTICK);
    connect(m_leftStick, &VirtualAnalogStick::released, this, &GamepadWidget::stickReleased);
    connect(m_leftStick, &VirtualAnalogStick::pressed, this, &GamepadWidget::stickPressed);
    connect(m_leftStick, &VirtualAnalogStick::moved, this, &GamepadWidget::stickMoved);

    // Load x, y, b, a buttons
    m_x = new VirtualGamepadButton(Button::X, this);
    m_svgLayout->addWidget(m_x, Button::X);
    connect(m_x, &VirtualGamepadButton::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_x, &VirtualGamepadButton::released, this, &GamepadWidget::buttonReleased);
    m_y = new VirtualGamepadButton(Button::Y, this);
    m_svgLayout->addWidget(m_y, Button::Y);
    connect(m_y, &VirtualGamepadButton::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_y, &VirtualGamepadButton::released, this, &GamepadWidget::buttonReleased);
    m_a = new VirtualGamepadButton(Button::A, this);
    m_svgLayout->addWidget(m_a, Button::A);
    connect(m_a, &VirtualGamepadButton::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_a, &VirtualGamepadButton::released, this, &GamepadWidget::buttonReleased);
    m_b = new VirtualGamepadButton(Button::B, this);
    m_svgLayout->addWidget(m_b, Button::B);
    connect(m_b, &VirtualGamepadButton::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_b, &VirtualGamepadButton::released, this, &GamepadWidget::buttonReleased);

    // Start and back
    m_start = new VirtualGamepadButton(Button::START, this);
    m_svgLayout->addWidget(m_start, Button::START);
    connect(m_start, &VirtualGamepadButton::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_start, &VirtualGamepadButton::released, this, &GamepadWidget::buttonReleased);
    m_back = new VirtualGamepadButton(Button::BACK, this);
    m_svgLayout->addWidget(m_back, Button::BACK);
    connect(m_back, &VirtualGamepadButton::pressed, this, &GamepadWidget::buttonPressed);
    connect(m_back, &VirtualGamepadButton::released, this, &GamepadWidget::buttonReleased);
}
