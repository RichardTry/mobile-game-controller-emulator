#include "gamepadcontrolleremulator.h"

GamepadControllerEmulator::GamepadControllerEmulator(QWidget *parent): AbstractControllerEmulator(parent), m_transceiver(nullptr) {
    m_gamepad = new Gamepad(this);

    // Setup ui
}

GamepadControllerEmulator::~GamepadControllerEmulator() {

}

void GamepadControllerEmulator::setTransceiver(AbstractTransceiver *transceiver) {
    m_transceiver = transceiver;
}
