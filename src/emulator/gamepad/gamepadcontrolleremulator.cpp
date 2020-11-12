#include "gamepadcontrolleremulator.h"
#include <QEvent>

GamepadControllerEmulator::GamepadControllerEmulator(QWidget *parent): AbstractControllerEmulator(parent), m_transceiver(nullptr) {
    setDisabled(true);

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
    m_rightStick = new VirtualAnalogStick(this);
    m_rightStick->setOuterRadius(outerRadius);
    m_rightStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_rightStick, Button::RIGHTSTICK);

    // Load left stick
    m_leftStick = new VirtualAnalogStick(this);
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

//    connect(m_x, &VirtualGamepadButton::pressed, m_gamepad, &Gamepad::setButton);

    m_gamepad = new Gamepad;
}

GamepadControllerEmulator::~GamepadControllerEmulator() {
    delete m_gamepad;
}

void GamepadControllerEmulator::setTransceiver(AbstractTransceiver *transceiver) {
    m_transceiver = transceiver;
}

bool GamepadControllerEmulator::event(QEvent *event) {
    QEvent::Type eventType = event->type();
    if(eventType != QEvent::TouchBegin && eventType != QEvent::TouchUpdate && eventType != QEvent::TouchEnd && eventType != QEvent::TouchCancel) {
        return QWidget::event(event);
    } else {
        return true;
    }
}
