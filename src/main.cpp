#include <QApplication>
#include <QWidget>
#include <QTimer>
#include "transceiver/network/networktransceiver.h"

int packetCount = 0;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
#if defined(DRIVER)
    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Slave);
    transceiver->widget()->show();
    QObject::connect(transceiver, &AbstractTransceiver::dataArrived, [](QByteArray data) {
        QDataStream in(&data, QIODevice::ReadOnly);
        QString str;
        in >> str;
        qDebug() << '\r' << str;
    });
    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit);
#elif defined(CONTROLLER)
    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Master);
    transceiver->widget()->show();
    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit, Qt::ConnectionType::QueuedConnection);
    QTimer timer;
    timer.setInterval(100);
    QObject::connect(&timer, &QTimer::timeout, [transceiver] () {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        QString msg = "Pecket number: " + QString::number(++packetCount).rightJustified(10, ' ');
        out << msg;
        if(transceiver->sendData(data) == -1) {
            qDebug() << "\r" << "Failed to send packet : " + QString::number(packetCount).rightJustified(10, ' ');
        } else {
            qDebug() << '\r' << "Sending packet number : " + QString::number(packetCount).rightJustified(10, ' ');
        }
    });
    QObject::connect(transceiver, &AbstractTransceiver::connected, [&timer] () {
        timer.start();
    });
    QObject::connect(transceiver, &AbstractTransceiver::disconnected, [&timer] () {
        timer.stop();
    });
#endif
    return app.exec();
}
