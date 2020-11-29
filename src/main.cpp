#include <QApplication>
#include "emulator/gamepad/gamepadcontrolleremulator.h"
#include "widget/gamepadwidget.h"
#include "transceiver/network/networktransceiver.h"
#include "widget/networktransceiverwidget.h"

int packetCount = 0;

class NetworkWorker: public QThread {
public:
    NetworkWorker(QObject *parent = nullptr) {
    }

    ~NetworkWorker() {
        m_networkTransceiver->deleteLater();
    }

    void init(const AbstractTransceiver::Mode &mode) {
        m_networkTransceiver = new NetworkTransceiver(mode);
    }

    NetworkTransceiver *networkTransceiver() const {
        return m_networkTransceiver;
    }

private:
    NetworkTransceiver *m_networkTransceiver;
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

#if defined(DRIVER)
    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Slave);
    Gamepad gamepad;
    QObject::connect(transceiver, &AbstractTransceiver::dataArrived, &gamepad, &Gamepad::setData);
    QObject::connect(transceiver, &AbstractTransceiver::dataArrived, [&gamepad] () {
        qDebug() << "";
        qDebug() << "Left  : " << QString::number(gamepad.getLeftStick().x()).rightJustified(7, ' ') << ", " << QString::number(gamepad.getLeftStick().y()).rightJustified(7, ' ');
        qDebug() << "Right : " << QString::number(gamepad.getRightStick().x()).rightJustified(7, ' ') << ", " << QString::number(gamepad.getRightStick().y()).rightJustified(7, ' ');
    });
    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit);
    NetworkTransceiverWidget widget((NetworkTransceiver*)transceiver);
    QObject::connect(&widget, &QWidget::destroyed, transceiver, &AbstractTransceiver::deleteLater);
    widget.show();
#elif defined(CONTROLLER)
    NetworkWorker worker;
    worker.init(AbstractTransceiver::Mode::Master);
    AbstractTransceiver *transceiver = worker.networkTransceiver();
    NetworkTransceiverWidget comWidget((NetworkTransceiver*)transceiver);
    comWidget.show();
    GamepadControllerEmulator *conemu = new GamepadControllerEmulator(transceiver);
    conemu->init();
    QObject::connect(transceiver, &AbstractTransceiver::connected, &comWidget, &QWidget::hide);
    QObject::connect(transceiver, &AbstractTransceiver::connected, conemu, &QWidget::show);
#endif

    return app.exec();
}
