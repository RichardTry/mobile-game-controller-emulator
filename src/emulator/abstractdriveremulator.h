#ifndef IDRIVEREMULATOR_H
#define IDRIVEREMULATOR_H

#include <QObject>

class AbstractTransceiver;

class AbstractDriverEmulator: public QObject {
    Q_OBJECT
public:
    AbstractDriverEmulator(AbstractTransceiver *transceiver, QObject *parent = nullptr): QObject(parent), m_transceiver(transceiver) {
    }

public slots:
    virtual void onError(QString error) = 0;
    virtual void onDataArrived(QByteArray data) = 0;
    virtual void onConnected() = 0;
    virtual void onDisconnected(QString msg) = 0;
    virtual void onQuit() = 0;

protected:
    AbstractTransceiver *m_transceiver;
};

#endif // IDRIVEREMULATOR_H
