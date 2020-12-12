#include "gamepadcontroller.h"
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include "event/gamepadevent.h"

GamepadController::GamepadController(QWidget *parent): AbstractController(parent) {
    // Load layout
    m_svgLayout = new GamepadSvgLayout;
    m_svgLayout->load();
    this->setLayout(m_svgLayout);

    // Load dpad
    m_dpad = new VirtualDirectionalPad(this);
    m_svgLayout->addWidget(m_dpad, Button::DPAD);
    connect(m_dpad, &VirtualDirectionalPad::pressed, this, &GamepadController::onButtonPressed);
    connect(m_dpad, &VirtualDirectionalPad::released, this, &GamepadController::onButtonReleased);

    // Load right stick
    const int outerRadius = 100;
    const int innerRadius = 30;
    m_rightStick = new VirtualAnalogStick(Button::RIGHTSTICK, this);
    m_rightStick->setOuterRadius(outerRadius);
    m_rightStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_rightStick, Button::RIGHTSTICK);
    connect(m_rightStick, &VirtualAnalogStick::released, this, &GamepadController::onStickReleased);
    connect(m_rightStick, &VirtualAnalogStick::pressed, this, &GamepadController::onStickPressed);
    connect(m_rightStick, &VirtualAnalogStick::moved, this, &GamepadController::onStickMoved);

    // Load left stick
    m_leftStick = new VirtualAnalogStick(Button::LEFTSTICK, this);
    m_leftStick->setOuterRadius(outerRadius);
    m_leftStick->setInnerRadius(innerRadius);
    m_svgLayout->addWidget(m_leftStick, Button::LEFTSTICK);
    connect(m_leftStick, &VirtualAnalogStick::released, this, &GamepadController::onStickReleased);
    connect(m_leftStick, &VirtualAnalogStick::pressed, this, &GamepadController::onStickPressed);
    connect(m_leftStick, &VirtualAnalogStick::moved, this, &GamepadController::onStickMoved);

    // Load x, y, b, a buttons
    m_x = new VirtualGamepadButton(Button::X, this);
    m_svgLayout->addWidget(m_x, Button::X);
    connect(m_x, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_x, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
    m_y = new VirtualGamepadButton(Button::Y, this);
    m_svgLayout->addWidget(m_y, Button::Y);
    connect(m_y, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_y, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
    m_a = new VirtualGamepadButton(Button::A, this);
    m_svgLayout->addWidget(m_a, Button::A);
    connect(m_a, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_a, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
    m_b = new VirtualGamepadButton(Button::B, this);
    m_svgLayout->addWidget(m_b, Button::B);
    connect(m_b, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_b, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);

    // Start and back
    m_start = new VirtualGamepadButton(Button::START, this);
    m_svgLayout->addWidget(m_start, Button::START);
    connect(m_start, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_start, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
    m_back = new VirtualGamepadButton(Button::BACK, this);
    m_svgLayout->addWidget(m_back, Button::BACK);
    connect(m_back, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_back, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);

    // Add left and right trigger
    m_rightTrigger = new VirtualGamepadButton(Button::RIGHTTRIGGER, this);
    m_svgLayout->addWidget(m_rightTrigger, Button::RIGHTTRIGGER);
    connect(m_rightTrigger, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_rightTrigger, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
    m_leftTrigger = new VirtualGamepadButton(Button::LEFTTRIGGER, this);
    m_svgLayout->addWidget(m_leftTrigger, Button::LEFTTRIGGER);
    connect(m_leftTrigger, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_leftTrigger, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);

    // Add left and right bumper
    m_rightBumper = new VirtualGamepadButton(Button::RIGHTBUMPER, this);
    m_svgLayout->addWidget(m_rightBumper, Button::RIGHTBUMPER);
    connect(m_rightBumper, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_rightBumper, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
    m_leftBumper = new VirtualGamepadButton(Button::LEFTBUMPER, this);
    m_svgLayout->addWidget(m_leftBumper, Button::LEFTBUMPER);
    connect(m_leftBumper, &VirtualGamepadButton::pressed, this, &GamepadController::onButtonPressed);
    connect(m_leftBumper, &VirtualGamepadButton::released, this, &GamepadController::onButtonReleased);
}

void GamepadController::onStickMoved(const Button& btn, const QPointF &point) {
    GamepadEvent gEvent(GamepadEvent::StickMoveEvent, btn, point);
    emit eventTriggered(gEvent.data());
}

void GamepadController::onStickReleased(const Button& btn, const QPointF &point) {
    GamepadEvent gEvent(GamepadEvent::StickReleaseEvent, btn, point);
    emit eventTriggered(gEvent.data());
}

void GamepadController::onStickPressed(const Button& btn, const QPointF &point) {
    GamepadEvent gEvent(GamepadEvent::StickPressEvent, btn, point);
    emit eventTriggered(gEvent.data());
}

void GamepadController::onButtonReleased(const Button& btn) {
    GamepadEvent gEvent(GamepadEvent::ButtonReleaseEvent, btn);
    emit eventTriggered(gEvent.data());
}

void GamepadController::onButtonPressed(const Button& btn) {
    GamepadEvent gEvent(GamepadEvent::ButtonPressEvent, btn);
    emit eventTriggered(gEvent.data());
}

bool GamepadController::eventFilter(QObject *obj, QEvent *event) {
    if(event->type() != QEvent::KeyPress || event->type() != QEvent::KeyRelease)
        return false;

//    const QInputEvent *inputEvent = static_cast<const QInputEvent*> (event);
    const QKeyEvent *keyEvent = static_cast<const QKeyEvent*> (event);

    if(keyEvent->key() == Qt::Key_VolumeUp) {
        qDebug() << "Volume up";
        return true;
    }
    if(keyEvent->key() == Qt::Key_VolumeDown) {
        qDebug() << "Volume down";
        return true;
    }
    return false;
}

bool GamepadController::event(QEvent *event) {
    if(event->type() != QEvent::KeyPress || event->type() != QEvent::KeyRelease)
        return QWidget::event(event);

    const QInputEvent *inputEvent = static_cast<const QInputEvent*> (event);
    const QKeyEvent *keyEvent = static_cast<const QKeyEvent*> (inputEvent);

    if(keyEvent->key() == Qt::Key_VolumeUp) {
        qDebug() << "Volume up";
        return true;
    }
    if(keyEvent->key() == Qt::Key_VolumeDown) {
        qDebug() << "Volume down";
        return true;
    }
    return QWidget::event(event);
}
