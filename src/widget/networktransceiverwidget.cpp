#include <QNetworkInterface>
#include <QMessageBox>
#include "networktransceiverwidget.h"
#include "ui_networktransceivermaster.h"
#include "ui_networktransceiverslave.h"

NetworkTransceiverWidget::NetworkTransceiverWidget(NetworkTransceiver *transceiver, QWidget *parent) : QWidget(parent), m_transceiver(transceiver) {
    // Get available interfaces
    for(const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if(address.isLoopback() || address.isNull())
            continue;
        else
            m_interfaces.push_back(address);
    }

    // Load initial state and ui
    if(transceiver->mode() == AbstractTransceiver::Mode::Master) {
        loadMasterUI();
    } else if(transceiver->mode() == AbstractTransceiver::Mode::Slave) {
        loadSlaveUI();
    }

    connect(m_transceiver, &NetworkTransceiver::hostFound, this, &NetworkTransceiverWidget::onHostFound);
    connect(m_transceiver, &NetworkTransceiver::stateChanged, this, &NetworkTransceiverWidget::onStateChanged);
}

void NetworkTransceiverWidget::loadMasterUI() {
    masterUi = new Ui::NetworkTransceiverMaster();
    masterUi->setupUi(this);
    masterUi->logoLabel->setPixmap(QIcon(":/applications-simulation.svg").pixmap(256, 256));
    masterUi->sendingIconLabel->setPixmap(QIcon(":/network-transmit-receive.svg").pixmap(256, 256));

    // INIT
    connect(masterUi->startPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStart);
    connect(masterUi->backPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::quit);
    for(const QHostAddress &address: m_interfaces) {
        masterUi->networkInterfaceComboBox->addItem(address.toString(), QVariant::fromValue <QHostAddress> (address));
    }
    connect(masterUi->networkInterfaceComboBox, QOverload <int>::of (&QComboBox::activated), [this] (int index) {
        const QHostAddress selectedInterface = masterUi->networkInterfaceComboBox->itemData(index).value <QHostAddress> ();
        m_transceiver->setSelectedInterface(selectedInterface);
    });

    // LISTEN
    connect(masterUi->connectPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStart);
    connect(masterUi->backPushButton2, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStop);
    connect(masterUi->hostListWidget, &QListWidget::itemClicked, [this] (QListWidgetItem *item) {
        QVariant data = item->data(Qt::UserRole);
        if(!data.canConvert <QHostAddress> ()) {
            QMessageBox messageBox;
            messageBox.setText(tr("Error, can't convert QVariant to QHostAddress"));
            messageBox.setWindowTitle(tr("Error"));
            messageBox.exec();
        } else {
            const QHostAddress slaveHost = data.value <QHostAddress> ();
            m_transceiver->setSlaveHost(slaveHost);
        }
    });

    // SEND INPUT
    connect(masterUi->stopSendingPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStop);
}

void NetworkTransceiverWidget::loadSlaveUI() {
    slaveUi = new Ui::NetworkTransceiverSlave();
    slaveUi->setupUi(this);
    slaveUi->logoLabel->setPixmap(QIcon(":/applications-simulation.svg").pixmap(256, 256));
    slaveUi->receiveAnimationLabel->setPixmap(QIcon(":/network-transmit-receive.svg").pixmap(256, 256));

    // INIT
    connect(slaveUi->startPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStart);
    connect(slaveUi->quitPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::quit);
    slaveUi->networkInterfaceComboBox->clear();
    for(const QHostAddress &address: m_interfaces) {
        slaveUi->networkInterfaceComboBox->addItem(address.toString(), QVariant::fromValue <QHostAddress> (address));
    }
    connect(slaveUi->networkInterfaceComboBox, QOverload <int>::of (&QComboBox::activated), [this] (int index) {
        const QHostAddress selectedInterface = slaveUi->networkInterfaceComboBox->itemData(index).value <QHostAddress> ();
        m_transceiver->setSelectedInterface(selectedInterface);
    });

    // BROADCAST
    connect(slaveUi->stopBroadcastPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStop);

    // RECEIVE INPUT
    connect(slaveUi->stopReceivingPushButton, &QPushButton::clicked, m_transceiver, &NetworkTransceiver::onStop);
}

void NetworkTransceiverWidget::onStateChanged(NetworkTransceiver::State state) {
    // Clear host list on every state change
    if(m_transceiver->mode() == NetworkTransceiver::Master)
        masterUi->hostListWidget->clear();

    switch (state) {
    // MASTER STATES
    case NetworkTransceiver::State::InitMaster: {
        masterUi->stackedWidget->setCurrentWidget(masterUi->stateMasterInit);
        break;
    }
    case NetworkTransceiver::State::Listen: {
        masterUi->stackedWidget->setCurrentWidget(masterUi->stateListen);
        break;
    }
    case NetworkTransceiver::State::SendInput: {
        masterUi->stackedWidget->setCurrentWidget(masterUi->stateSendnput);
        break;
    }
    // SLAVE STATES
    case NetworkTransceiver::State::InitSlave: {
        slaveUi->stackedWidget->setCurrentWidget(slaveUi->StateInitSlave);
        break;
    }
    case NetworkTransceiver::State::Broadcast: {
        slaveUi->stackedWidget->setCurrentWidget(slaveUi->StateBroadcast);
        break;
    }
    case NetworkTransceiver::State::ReceiveInput: {
        slaveUi->stackedWidget->setCurrentWidget(slaveUi->StateReceiveInput);
        break;
    }
    }
}

void NetworkTransceiverWidget::onHostFound(QString address) {
    const QHostAddress hostAddress(address);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole, QVariant::fromValue <QHostAddress> (hostAddress));
    item->setText(address);
    masterUi->hostListWidget->addItem(item);
}
