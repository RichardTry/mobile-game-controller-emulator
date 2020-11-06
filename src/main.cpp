#include <QApplication>
#include <QWidget>
#include <QTimer>
#include "widget/virtualanalogstick.h"
#include "layout/gamepadsvglayout.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

int packetCount = 0;

int main(int argc, char **argv) {
    QApplication app(argc, argv);


    QWidget *widget = new QWidget;
    widget->setWindowTitle("Virtual Analog Stick Test Run");

    VirtualAnalogStick *analogStick = new VirtualAnalogStick(widget);
    const int outerRadius = 250;
    const int innerRadius = 100;
    analogStick->setOuterRadius(outerRadius);
    analogStick->setInnerRadius(innerRadius);
    analogStick->setOuterColor(QColor(32, 32, 32, 128));
    analogStick->setInnerColor(QColor(32, 32, 32, 255));

    GamepadSvgLayout *svgLayout = new GamepadSvgLayout;
    svgLayout->load();
    svgLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
    widget->setLayout(svgLayout);
    svgLayout->addWidget(analogStick, Button::LEFTSTICK);
    auto label = new QLabel("RIGHT STICK", widget);
    label->setFrameStyle(QFrame::Box);
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setMinimumSize(50, 50);
    label->setStyleSheet("background-color:red");
    svgLayout->addWidget(label, Button::RIGHTSTICK);
    widget->show();
    analogStick->show();


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

//#if defined(DRIVER)
//    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Slave);
//    transceiver->widget()->show();
//    QObject::connect(transceiver, &AbstractTransceiver::dataArrived, [](QByteArray data) {
//        QDataStream in(&data, QIODevice::ReadOnly);
//        QString str;
//        in >> str;
//        qDebug() << str;
//    });
//    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit);
//#elif defined(CONTROLLER)
//    AbstractTransceiver *transceiver = new NetworkTransceiver(NetworkTransceiver::Mode::Master);
//    transceiver->widget()->show();
//    QObject::connect(transceiver, &AbstractTransceiver::quit, &app, &QApplication::quit, Qt::ConnectionType::QueuedConnection);
//    QTimer timer;
//    timer.setInterval(100);
//    QObject::connect(&timer, &QTimer::timeout, [transceiver] () {
//        QByteArray data;
//        QDataStream out(&data, QIODevice::WriteOnly);
//        QString msg = "Packet number: " + QString::number(++packetCount).rightJustified(10, ' ');
//        out << msg;
//        if(transceiver->sendData(data) == -1) {
//            qDebug() << "Failed to send packet : " + QString::number(packetCount).rightJustified(10, ' ');
//        } else {
//            qDebug() << "Sending packet number : " + QString::number(packetCount).rightJustified(10, ' ');
//        }
//    });
//    QObject::connect(transceiver, &AbstractTransceiver::connected, [&timer] () {
//        timer.start();
//    });
//    QObject::connect(transceiver, &AbstractTransceiver::disconnected, [&timer] () {
//        timer.stop();
//    });
//#endif
    return app.exec();
}
