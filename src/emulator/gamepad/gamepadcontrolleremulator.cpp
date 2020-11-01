#include "gamepadcontrolleremulator.h"

GamepadControllerEmulator::GamepadControllerEmulator(QObject *parent): QObject(parent), m_transceiver(nullptr) {
    m_widget = new QWidget;
}

GamepadControllerEmulator::~GamepadControllerEmulator() {

}

void GamepadControllerEmulator::setTransceiver(AbstractTransceiver *transceiver) {
    m_transceiver = transceiver;
}

QWidget *GamepadControllerEmulator::widget() {

}
