#include "gamepadcontrolleremulator.h"
#include <QEvent>
#include <QHBoxLayout>

GamepadControllerEmulator::GamepadControllerEmulator(AbstractTransceiver *transceiver, QWidget *parent): AbstractControllerEmulator(transceiver, parent), m_frameBufferSize(10) {
    m_frames.fill(QByteArray(), m_frameBufferSize);
    m_freeFrames.release(m_frameBufferSize);
    m_frameIndex = 0;

    m_gamepad = new Gamepad(this);
    m_gamepadWidget = new GamepadWidget(this);

    this->setLayout(new QHBoxLayout);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->addWidget(m_gamepadWidget);

    connect(m_gamepadWidget, &GamepadWidget::buttonPressed, this, &GamepadControllerEmulator::onButtonPressed);
    connect(m_gamepadWidget, &GamepadWidget::buttonReleased, this, &GamepadControllerEmulator::onButtonReleased);
    connect(m_gamepadWidget, &GamepadWidget::stickPressed, this, &GamepadControllerEmulator::onStickPressed);
    connect(m_gamepadWidget, &GamepadWidget::stickReleased, this, &GamepadControllerEmulator::onStickReleased);
    connect(m_gamepadWidget, &GamepadWidget::stickMoved, this, &GamepadControllerEmulator::onStickMoved);

    m_transmittionWorker = new TransmittionWorker(this);
    m_transmittionWorker->start();
}

GamepadControllerEmulator::~GamepadControllerEmulator() {
    m_transmittionWorker->stop();
    m_transmittionWorker->deleteLater();
}

void GamepadControllerEmulator::onStickMoved(const Button& btn, const QPointF &point) {
    m_gamepad->onStickMoved(btn, point);
    writeFrame();
    m_gamepad->clearEvents(btn);
}

void GamepadControllerEmulator::onStickReleased(const Button& btn, const QPointF &point) {
    m_gamepad->onStickReleased(btn, point);
    writeFrame();
    m_gamepad->clearEvents(btn);
}

void GamepadControllerEmulator::onStickPressed(const Button& btn, const QPointF &point) {
    m_gamepad->onStickPressed(btn, point);
    writeFrame();
    m_gamepad->clearEvents(btn);
}

void GamepadControllerEmulator::onButtonReleased(const Button& btn) {
    m_gamepad->onButtonReleased(btn);
    writeFrame();
    m_gamepad->clearEvents(btn);
}

void GamepadControllerEmulator::onButtonPressed(const Button& btn) {
    m_gamepad->onButtonPressed(btn);
    writeFrame();
    m_gamepad->clearEvents(btn);
}

void GamepadControllerEmulator::writeFrame() {
    m_freeFrames.acquire();
    m_frameIndex = m_frameIndex % m_frameBufferSize;
    QByteArray &payload = m_frames[m_frameIndex];
    payload = m_gamepad->getData();
    ++m_frameIndex;
    m_usedFrames.release();
}

GamepadControllerEmulator::TransmittionWorker::TransmittionWorker(GamepadControllerEmulator *emulator): m_emulator(emulator), m_stopped(false) {

}

void GamepadControllerEmulator::TransmittionWorker::run() {
    int index = 0;
    while(!m_stopped) {
        m_emulator->m_usedFrames.acquire();
        index %= m_emulator->m_frameBufferSize;
        QByteArray &payload = m_emulator->m_frames[index];
        ++index;
        m_emulator->m_transceiver->sendData(payload);
        m_emulator->m_freeFrames.release();
    }
}

void GamepadControllerEmulator::TransmittionWorker::stop() {
    m_stopped = true;
}
