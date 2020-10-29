#include "networktransceiver.h"
#include <QThreadPool>
#include <QWidget>
#include <QNetworkInterface>
#include <QNetworkDatagram>
#include <QMessageBox>
#include <QDataStream>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ui_networktransceivermaster.h"
#include "ui_networktransceiverslave.h"

unsigned int NetworkTransceiver::m_datagramId = 0;

NetworkTransceiver::NetworkTransceiver(const Mode &mode, QObject *parent):
    AbstractTransceiver(mode, parent),
    m_port(45800),
    m_selectedInterface(QHostAddress::Null),
    m_slaveHost(QHostAddress::Null),
    m_masterHost(QHostAddress::Null)
{

    // Get available interfaces
    for(const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if(address.isLoopback() || address.isNull())
            continue;
        else
            m_interfaces.push_back(address);
    }

    // Load initial state and ui
    m_widget = new QWidget();
    if(m_mode == Mode::Master) {
        loadMasterUI();
        m_state = new StateInitMaster(this);
    } else if(m_mode == Mode::Slave) {
        loadSlaveUI();
        m_state = new StateInitSlave(this);
    }

    // Initilize udp socket and make connections
    m_udpSocket = new QUdpSocket();
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &NetworkTransceiver::onReadyRead);
}

NetworkTransceiver::~NetworkTransceiver() {
    delete m_state;
}

QWidget *NetworkTransceiver::widget() {
    return m_widget;
}

qint64 NetworkTransceiver::sendData(const QByteArray &data, const bool &acknowledge) {
    return m_state->sendData(data, acknowledge);
}

void NetworkTransceiver::onStart() {
    AbstractState *nextState = m_state->start();
    if(nextState) {
        delete m_state;
        m_state = nextState;
    }
}

void NetworkTransceiver::onStop() {
    AbstractState *nextState = m_state->stop();
    if(nextState) {
        delete m_state;
        m_state = nextState;
    }
}

void NetworkTransceiver::onReadyRead() {
    AbstractState *nextState = m_state->onReadyRead();
    if(nextState) {
        delete m_state;
        m_state = nextState;
    }
}

void NetworkTransceiver::loadMasterUI() {
    masterUi = new Ui::NetworkTransceiverMaster();
    masterUi->setupUi(m_widget);

    // Init
    connect(masterUi->startPushButton, &QPushButton::clicked, this, &NetworkTransceiver::onStart);
    connect(masterUi->backPushButton, &QPushButton::clicked, this, &AbstractTransceiver::quit);
    connect(masterUi->pollRateSpinBox, QOverload <int>::of (&QSpinBox::valueChanged), [this] (int value) {
        m_pollPeriodMS = 1000.f / value;
    });
    for(const QHostAddress &address: m_interfaces) {
        masterUi->networkInterfaceComboBox->addItem(address.toString(), QVariant::fromValue <QHostAddress> (address));
    }
    connect(masterUi->networkInterfaceComboBox, QOverload <int>::of (&QComboBox::activated), [this] (int index) {
        m_selectedInterface = masterUi->networkInterfaceComboBox->itemData(index).value <QHostAddress> ();
    });

    // Listen
    connect(masterUi->connectPushButton, &QPushButton::clicked, this, &NetworkTransceiver::onStart);
    connect(masterUi->backPushButton2, &QPushButton::clicked, this, &NetworkTransceiver::onStop);
    connect(masterUi->hostListWidget, &QListWidget::itemClicked, [this] (QListWidgetItem *item) {
        QVariant data = item->data(Qt::UserRole);
        if(!data.canConvert <QHostAddress> ()) {
            QMessageBox messageBox;
            messageBox.setText(tr("Error, can't convert QVariant to QHostAddress"));
            messageBox.setWindowTitle(tr("Error"));
            messageBox.exec();
        } else {
            m_slaveHost = data.value <QHostAddress> ();
        }
    });

    // Send Input
    connect(masterUi->stopSendingPushButton, &QPushButton::clicked, this, &NetworkTransceiver::onStop);
}

void NetworkTransceiver::loadSlaveUI() {
    slaveUi = new Ui::NetworkTransceiverSlave();
    slaveUi->setupUi(m_widget);
    QGraphicsScene *scene = new QGraphicsScene();
    QSvgRenderer *renderer = new QSvgRenderer(QStringLiteral(":/applications-simulation.svg"));
    QGraphicsSvgItem *item = new QGraphicsSvgItem();
    item->setSharedRenderer(renderer);
    scene->addItem(item);
    slaveUi->logoGraphicsView->setScene(scene);
    slaveUi->logoGraphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
//    slaveUi->logoGraphicsView->scale(slaveUi->logoGraphicsView->frameSize().width()/scene->width(), slaveUi->logoGraphicsView->frameSize().height()/scene->height());
    slaveUi->logoGraphicsView->setAlignment(Qt::AlignCenter);
    widget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Init
    connect(slaveUi->startPushButton, &QPushButton::clicked, this, &NetworkTransceiver::onStart);
    connect(slaveUi->quitPushButton, &QPushButton::clicked, this, &NetworkTransceiver::quit);
    for(const QHostAddress &address: m_interfaces) {
        slaveUi->networkInterfaceComboBox->addItem(address.toString(), QVariant::fromValue <QHostAddress> (address));
    }
    connect(slaveUi->networkInterfaceComboBox, QOverload <int>::of (&QComboBox::activated), [this] (int index) {
        m_selectedInterface = slaveUi->networkInterfaceComboBox->itemData(index).value <QHostAddress> ();
    });

    // Broadcast
    connect(slaveUi->stopBroadcastPushButton, &QPushButton::clicked, this, &NetworkTransceiver::onStop);

    // Receive Input
    connect(slaveUi->stopReceivingPushButton, &QPushButton::clicked, this, &NetworkTransceiver::onStop);
}

// MASTER INITIAL
NetworkTransceiver::StateInitMaster::StateInitMaster(NetworkTransceiver *transceiver): AbstractState(transceiver) {
    m_transceiver->masterUi->stackedWidget->setCurrentWidget(m_transceiver->masterUi->stateMasterInit);
}

NetworkTransceiver::StateInitMaster::~StateInitMaster() {

}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateInitMaster::start() {
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Error"));

    if(m_transceiver->m_selectedInterface.isNull()) {
        messageBox.setText(tr("Error, no interface selected!"));
        messageBox.exec();
        return nullptr;
    }

    m_transceiver->m_udpSocket->close();
    if(!m_transceiver->m_udpSocket->bind(QHostAddress::Any, m_transceiver->m_port)) {
//    if(!m_transceiver->m_udpSocket->bind(m_transceiver->m_selectedInterface, m_transceiver->m_port)) {
        messageBox.setText(tr("Error binding socket to host: ") + m_transceiver->m_selectedInterface.toString() + tr(", port: ") + QString::number(m_transceiver->m_port));
        messageBox.exec();
        return nullptr;
    }

    return new StateListen(m_transceiver);
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateInitMaster::stop() {
    m_transceiver->quit();
    return nullptr;
}

qint64 NetworkTransceiver::StateInitMaster::sendData(const QByteArray &data, const bool &acknowledge) {
    return -1;
}

// MASTER LISTEN
NetworkTransceiver::StateListen::StateListen(NetworkTransceiver *transceiver): AbstractState(transceiver) {
    transceiver->masterUi->stackedWidget->setCurrentWidget(transceiver->masterUi->stateListen);
    transceiver->masterUi->hostListWidget->clear();
}

NetworkTransceiver::StateListen::~StateListen() {
    m_transceiver->m_slaveHost = QHostAddress::Null;
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateListen::start() {
    if(m_transceiver->m_slaveHost.isNull()) {
        QMessageBox messageBox;
        messageBox.setWindowTitle(tr("Error"));
        messageBox.setText(tr("Error, no target device selected!"));
        messageBox.exec();
        return nullptr;
    }
    else {
        return new StateSendInput(m_transceiver);
    }
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateListen::stop() {
    return new StateInitMaster(m_transceiver);
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateListen::onReadyRead() {
    QNetworkDatagram datagram = m_transceiver->m_udpSocket->receiveDatagram();
    if(!m_hosts.contains(datagram.senderAddress().toIPv4Address())) {
        m_hosts[datagram.senderAddress().toIPv4Address()] = datagram.senderAddress();

        QListWidgetItem *item = new QListWidgetItem(m_transceiver->masterUi->hostListWidget);
        item->setData(Qt::UserRole, QVariant::fromValue(datagram.senderAddress()));
        item->setText(QString(datagram.data()) + "@ ip = " + datagram.senderAddress().toString() + ", port = " + QString::number(datagram.senderPort()));
        m_transceiver->masterUi->hostListWidget->addItem(item);
    }
    return nullptr;
}

qint64 NetworkTransceiver::StateListen::sendData(const QByteArray &data, const bool &acknowledge) {
    return -1;
}

// MASTER SEND INPUT
NetworkTransceiver::StateSendInput::StateSendInput(NetworkTransceiver *transceiver): AbstractState(transceiver) {
    transceiver->masterUi->stackedWidget->setCurrentWidget(transceiver->masterUi->stateSendnput);
    m_transceiver->connected();
    m_transceiver->m_udpSocket->connectToHost(m_transceiver->m_slaveHost, m_transceiver->m_port);
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Info"));
    messageBox.setText(tr("Connected to host: ") + m_transceiver->m_slaveHost.toString());
    messageBox.exec();
}

NetworkTransceiver::StateSendInput::~StateSendInput() {
    m_transceiver->m_udpSocket->disconnectFromHost();
    m_transceiver->disconnected("");
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateSendInput::start() {
    return nullptr;
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateSendInput::stop() {
    return new StateListen(m_transceiver);
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateSendInput::onReadyRead() {
    QNetworkDatagram datagram = m_transceiver->m_udpSocket->receiveDatagram();
    QByteArray data = datagram.data();
    QDataStream in(&data, QIODevice::ReadOnly);
    QString str;
    in << str;
    if(str == "quit") {
        return new StateListen(m_transceiver);
    } else
        return nullptr;
}

qint64 NetworkTransceiver::StateSendInput::sendData(const QByteArray &data, const bool &acknowledge) {
    QNetworkDatagram datagram;
    datagram.setData(data);
    datagram.setSender(m_transceiver->m_selectedInterface, m_transceiver->m_port);
    datagram.setDestination(m_transceiver->m_slaveHost, m_transceiver->m_port);
//    m_transceiver->m_udpSocket->connectToHost(m_transceiver->m_slaveHost, m_transceiver->m_port);
    return m_transceiver->m_udpSocket->write(data);
//    return m_transceiver->m_udpSocket->writeDatagram(datagram);
}

// SLAVE INIT
NetworkTransceiver::StateInitSlave::StateInitSlave(NetworkTransceiver *transceiver): AbstractState(transceiver) {
    m_transceiver->slaveUi->stackedWidget->setCurrentWidget(m_transceiver->slaveUi->StateInitSlave);
}

NetworkTransceiver::StateInitSlave::~StateInitSlave() {

}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateInitSlave::start() {
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Error"));

    if(m_transceiver->m_selectedInterface.isNull()) {
        messageBox.setText(tr("Error, no interface selected!"));
        messageBox.exec();
        return nullptr;
    }

    m_transceiver->m_udpSocket->close();
    if(!m_transceiver->m_udpSocket->bind(m_transceiver->m_selectedInterface, m_transceiver->m_port)) {
        messageBox.setText(tr("Error binding socket to host: ") + m_transceiver->m_selectedInterface.toString() + tr(", port: ") + QString::number(m_transceiver->m_port));
        messageBox.exec();
        return nullptr;
    }

    return new StateBroadcast(m_transceiver);
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateInitSlave::stop() {
    m_transceiver->quit();
    return nullptr;
}

qint64 NetworkTransceiver::StateInitSlave::sendData(const QByteArray &data, const bool &acknowledge) {
    return -1;
}

// SLAVE BROADCAST
NetworkTransceiver::StateBroadcast::StateBroadcast(NetworkTransceiver *transceiver): AbstractState(transceiver), m_pollPeriodMS(200) {
    m_transceiver->slaveUi->stackedWidget->setCurrentWidget(m_transceiver->slaveUi->StateBroadcast);

    QNetworkDatagram datagram;
    datagram.setDestination(QHostAddress::Broadcast, m_transceiver->m_port);
    connect(&m_timer, &QTimer::timeout, [this, datagram] () {
        m_transceiver->m_udpSocket->writeDatagram(datagram);
    });

    m_timer.setInterval(m_pollPeriodMS);
    m_timer.start();
}

NetworkTransceiver::StateBroadcast::~StateBroadcast() {

}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateBroadcast::start() {
    return nullptr;
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateBroadcast::stop() {
    return new StateInitSlave(m_transceiver);
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateBroadcast::onReadyRead() {
    QNetworkDatagram datagram = m_transceiver->m_udpSocket->receiveDatagram();
    m_transceiver->m_masterHost = datagram.senderAddress();
    return new StateReceiveInput(m_transceiver);
}

qint64 NetworkTransceiver::StateBroadcast::sendData(const QByteArray &data, const bool &acknowledge) {
    return -1;
}

// SLAVE RECEIVE INPUT
NetworkTransceiver::StateReceiveInput::StateReceiveInput(NetworkTransceiver *transceiver): AbstractState(transceiver) {
    m_transceiver->slaveUi->stackedWidget->setCurrentWidget(m_transceiver->slaveUi->StateReceiveInput);
    m_transceiver->connected();
}

NetworkTransceiver::StateReceiveInput::~StateReceiveInput() {
    m_transceiver->disconnected("");
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateReceiveInput::start() {
    return nullptr;
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateReceiveInput::stop() {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << QString("quit");

    QNetworkDatagram datagram;
    datagram.setDestination(m_transceiver->m_masterHost, m_transceiver->m_port);
    datagram.setData(data);
    m_transceiver->m_udpSocket->writeDatagram(datagram);

    return new StateBroadcast(m_transceiver);
}

NetworkTransceiver::AbstractState *NetworkTransceiver::StateReceiveInput::onReadyRead() {
    QNetworkDatagram datagram = m_transceiver->m_udpSocket->receiveDatagram();
    m_transceiver->dataArrived(datagram.data());
}

qint64 NetworkTransceiver::StateReceiveInput::sendData(const QByteArray &data, const bool &acknowledge) {
    QNetworkDatagram datagram;
    datagram.setDestination(m_transceiver->m_masterHost, m_transceiver->m_port);
    datagram.setData(data);
    return m_transceiver->m_udpSocket->writeDatagram(datagram);
}
