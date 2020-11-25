#include "gamepadcontrolleremulator.h"
#include <QEvent>

GamepadControllerEmulator::GamepadControllerEmulator(QWidget *parent): AbstractControllerEmulator(parent), m_transceiver(nullptr), m_payloadsBufferSize(10) {
    m_payloads.fill(QByteArray(), m_payloadsBufferSize);
    m_gamepad = new Gamepad;
}

GamepadControllerEmulator::~GamepadControllerEmulator() {
    delete m_gamepad;
}

void GamepadControllerEmulator::setTransceiver(AbstractTransceiver *transceiver) {
    m_transceiver = transceiver;
}
