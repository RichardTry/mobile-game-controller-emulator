#ifndef NETWORKTRANSCEIVER_H
#define NETWORKTRANSCEIVER_H

#include "transceiver/abstracttransceiver.h"
#include <QUdpSocket>
#include <QTimer>

namespace Ui {
class NetworkTransceiverMaster;
class NetworkTransceiverSlave;
}

Q_DECLARE_METATYPE(QHostAddress)

class NetworkTransceiver : public AbstractTransceiver {
    class AbstractState {
    public:
        AbstractState(NetworkTransceiver *transceiver): m_transceiver(transceiver) {

        }

        virtual ~AbstractState() {}

        virtual AbstractState *start() = 0;
        virtual AbstractState *stop() = 0;
        virtual AbstractState *onReadyRead() { return nullptr; }
        virtual qint64 sendData(const QByteArray &data, const bool &acknowledge = false) {}

    protected:
        NetworkTransceiver *m_transceiver;
    };

    // MASTER STATES
    class StateInitMaster : public AbstractState {
    public:
        StateInitMaster(NetworkTransceiver *transceiver);
        ~StateInitMaster();

        AbstractState *start() override;
        AbstractState *stop() override;
        qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;
    };

    class StateListen: public AbstractState {
    public:
        StateListen(NetworkTransceiver *transceiver);
        ~StateListen();

        AbstractState *start() override;
        AbstractState *stop() override;
        AbstractState *onReadyRead() override; // When a host is found add it to host list
        qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;

    private:
        QMap <int, QHostAddress> m_hosts;
    };

    class StateSendInput: public AbstractState {
    public:
        StateSendInput(NetworkTransceiver *transceiver);
        ~StateSendInput();

        AbstractState *start() override;
        AbstractState *stop() override;
        AbstractState *onReadyRead() override; // When the slave informs it has quit receiving input go back to previous state and display an info message
        qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;
    };

    // SLAVE STATES
    class StateInitSlave : public AbstractState {
    public:
        StateInitSlave(NetworkTransceiver *transceiver);
        ~StateInitSlave();

        AbstractState *start() override;
        AbstractState *stop() override;
        qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;
    };

    class StateBroadcast: public AbstractState {
    public:
        StateBroadcast(NetworkTransceiver *transceiver);
        ~StateBroadcast();

        AbstractState *start() override;
        AbstractState *stop() override;
        AbstractState *onReadyRead() override; // When a master sends a datagram go into receive input state and store master address
        qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;

    private:
        int m_pollPeriodMS;
        QTimer m_timer;
    };

    class StateReceiveInput: public AbstractState {
    public:
        StateReceiveInput(NetworkTransceiver *transceiver);
        ~StateReceiveInput();

        AbstractState *start() override;
        AbstractState *stop() override;
        AbstractState *onReadyRead() override; // Receive data and emit data arrived signal
        qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;
    };

public:
    NetworkTransceiver(const Mode &mode, QObject *parent = nullptr);
    ~NetworkTransceiver();

    QWidget *widget() override;
    qint64 sendData(const QByteArray &data, const bool &acknowledge = false) override;

public slots:
    // Not start & stop in the strict sense, start could mean connect to target, stop could be quit etc.
    // They represent transitions between states in opposing directions
    void onStart() override;
    void onStop() override;

private slots:
    void onReadyRead();

private:
    void loadMasterUI();
    void loadSlaveUI();

    AbstractState *m_state;
    QUdpSocket *m_udpSocket;
    quint16 m_port;
    QWidget *m_widget;
    // Configured by master only, slave receives at the rate the master dictates
    int m_pollPeriodMS;
    // Common to both modes
    QList <QHostAddress> m_interfaces;
    QHostAddress m_selectedInterface;
    // Paired devices, slave stores master and master vice versa
    QHostAddress m_slaveHost;
    QHostAddress m_masterHost;
    // Different ui's loaded for each mode
    Ui::NetworkTransceiverMaster *masterUi;
    Ui::NetworkTransceiverSlave *slaveUi;
    static unsigned int m_datagramId;
};

#endif // NETWORKTRANSCEIVER_H
