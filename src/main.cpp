#include <QApplication>
#include "emulator/gamepad/gamepadcontrolleremulator.h"
#include "widget/gamepadwidget.h"
#include "transceiver/network/networktransceiver.h"
#include "widget/networktransceiverwidget.h"

int packetCount = 0;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

#if defined(DRIVER)
    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Slave);
    QObject::connect(transceiver, &AbstractTransceiver::dataArrived, [](QByteArray data) {
        QDataStream in(&data, QIODevice::ReadOnly);
        QString str;
        in >> str;
        qDebug() << str;
    });
    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit);
    NetworkTransceiverWidget widget((NetworkTransceiver*)transceiver);
    QObject::connect(&widget, &QWidget::destroyed, transceiver, &AbstractTransceiver::deleteLater);
    widget.show();
#elif defined(CONTROLLER)
    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Master);
    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit, Qt::ConnectionType::QueuedConnection);
    QTimer timer;
    timer.setInterval(100);
    QObject::connect(&timer, &QTimer::timeout, [transceiver] () {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        QString msg = "Packet number: " + QString::number(++packetCount).rightJustified(10, ' ');
        out << msg;
        if(transceiver->sendData(data) == -1) {
            qDebug() << "Failed to send packet : " + QString::number(packetCount).rightJustified(10, ' ');
        } else {
            qDebug() << "Sending packet number : " + QString::number(packetCount).rightJustified(10, ' ');
        }
    });
    QObject::connect(transceiver, &AbstractTransceiver::connected, [&timer] () {
        timer.start();
    });
    QObject::connect(transceiver, &AbstractTransceiver::disconnected, [&timer] () {
        timer.stop();
    });
    NetworkTransceiverWidget widget((NetworkTransceiver*)transceiver);
    QObject::connect(&widget, &QWidget::destroyed, transceiver, &AbstractTransceiver::deleteLater);
    widget.show();
#endif
    return app.exec();
}
