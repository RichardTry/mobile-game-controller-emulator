#include <QApplication>
#include "emulator/gamepad/gamepadcontrolleremulator.h"
#include "widget/gamepadwidget.h"
#include "transceiver/network/networktransceiver.h"
#include "widget/networktransceiverwidget.h"

int packetCount = 0;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

//    GamepadControllerEmulator *emulator = new GamepadControllerEmulator;
//    emulator->show();
//    GamepadWidget *gWidget = new GamepadWidget;
//    gWidget->show();


//    return app.exec();

//    QWidget *widget = new QWidget;
//    widget->setWindowTitle("Virtual Analog Stick Test Run");

//    VirtualAnalogStick *analogStick = new VirtualAnalogStick(widget);
//    const int outerRadius = 250;
//    const int innerRadius = 100;

//    analogStick->setOuterRadius(outerRadius);
//    analogStick->setInnerRadius(innerRadius);

//    analogStick->setOuterColor(QColor(32, 32, 32, 128));
//    analogStick->setInnerColor(QColor(32, 32, 32, 255));

//    QLabel *label = new QLabel(widget);
//    label->setAlignment(Qt::AlignCenter);
//    QObject::connect(analogStick, &VirtualAnalogStick::touchPointMoved, [label] (QPointF normalisedTouchPoint){
//        label->setText("x :" + QString::number((double)normalisedTouchPoint.x()).rightJustified(5, ' ', true) + ", y : " + QString::number((double)normalisedTouchPoint.y()).rightJustified(5, ' ', true));
//    });

//    auto vBoxLayout  = new QVBoxLayout;
//    auto hBoxLayout  = new QHBoxLayout;
//    widget->setLayout(vBoxLayout);
//    vBoxLayout->addStretch();
//    vBoxLayout->addWidget(label);
//    vBoxLayout->addLayout(hBoxLayout);
//    vBoxLayout->addStretch();

//    hBoxLayout->addStretch();
//    hBoxLayout->addWidget(analogStick);
//    hBoxLayout->addStretch();

//    widget->show();
//    analogStick->show();

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
