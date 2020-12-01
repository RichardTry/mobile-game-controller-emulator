#include <QApplication>
#include "emulator/gamepad/gamepadcontrolleremulator.h"
#include "widget/gamepadwidget.h"
#include "transceiver/network/networktransceiver.h"
#include "widget/networktransceiverwidget.h"

class NetworkWorker: public QThread {
public:
    NetworkWorker(const AbstractTransceiver::Mode &mode, QObject *parent = nullptr) {
        m_networkTransceiver = new NetworkTransceiver(mode);
    }

    ~NetworkWorker() {
        m_networkTransceiver->deleteLater();
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
    QObject::connect(&gamepad, &Gamepad::buttonPressed, [] (const Button& btn) {
        qDebug() << "Button pressed:  " << labelForButton(btn).rightJustified(10, ' ');
    });
    QObject::connect(&gamepad, &Gamepad::buttonReleased, [] (const Button& btn) {
        qDebug() << "Button released: " << labelForButton(btn).rightJustified(10, ' ');
    });
    QObject::connect(&gamepad, &Gamepad::stickMoved, [] (const Button& btn, const QPointF &point) {
        qDebug() << labelForButton(btn).rightJustified(10) << " Moved:    " << QString::number(point.x()).rightJustified(10, ' ') << ", " << QString::number(point.y()).rightJustified(10, ' ');
    });
    QObject::connect(&gamepad, &Gamepad::stickPressed, [] (const Button& btn, const QPointF &point) {
        qDebug() << labelForButton(btn).rightJustified(10) << " Pressed:  " << QString::number(point.x()).rightJustified(10, ' ') << ", " << QString::number(point.y()).rightJustified(10, ' ');
    });
    QObject::connect(&gamepad, &Gamepad::stickReleased, [] (const Button& btn, const QPointF &point) {
        qDebug() << labelForButton(btn).rightJustified(10) << " Released: " << QString::number(point.x()).rightJustified(10, ' ') << ", " << QString::number(point.y()).rightJustified(10, ' ');
    });
    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit);
    NetworkTransceiverWidget widget((NetworkTransceiver*)transceiver);
    QObject::connect(&widget, &QWidget::destroyed, transceiver, &AbstractTransceiver::deleteLater);
    widget.show();
#elif defined(CONTROLLER)
    NetworkWorker worker(AbstractTransceiver::Mode::Master);
    AbstractTransceiver *transceiver = worker.networkTransceiver();
    NetworkTransceiverWidget comWidget((NetworkTransceiver*)transceiver);
    comWidget.show();
    GamepadControllerEmulator *conemu = new GamepadControllerEmulator(transceiver);
    QObject::connect(transceiver, &AbstractTransceiver::connected, &comWidget, &QWidget::hide);
    QObject::connect(transceiver, &AbstractTransceiver::connected, conemu, &QWidget::show);
#endif

    return app.exec();
}
