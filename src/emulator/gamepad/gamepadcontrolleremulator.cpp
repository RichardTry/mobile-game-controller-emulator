#include "gamepadcontrolleremulator.h"
#include <QEvent>

GamepadControllerEmulator::GamepadControllerEmulator(QWidget *parent): AbstractControllerEmulator(parent), m_transceiver(nullptr) {
//    setAttribute(Qt::WA_AcceptTouchEvents);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
//    setWindowFlag(Qt::WindowTransparentForInput);
    setDisabled(true);

    // Load layout
    m_svgLayout = new GamepadSvgLayout;
    m_svgLayout->load();
    this->setLayout(m_svgLayout);

    // Load dpad
    m_dpad = new VirtualDirectionalPad(this);
    m_svgLayout->addWidget(m_dpad, Button::LEFTSTICK);

    // Load right stick
    const int outerRadius = 100;
    const int innerRadius = 30;
    m_rightStick = new VirtualAnalogStick(this);
    m_rightStick->setOuterRadius(outerRadius);
    m_rightStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_rightStick, Button::RIGHTSTICK);

//    // Load left stick
//    m_leftStick = new VirtualAnalogStick(this);
//    m_leftStick->setOuterRadius(outerRadius);
//    m_leftStick->setInnerRadius(innerRadius);
//    m_svgLayout->addWidget(m_leftStick, Button::LEFTSTICK);
}

GamepadControllerEmulator::~GamepadControllerEmulator() {

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
