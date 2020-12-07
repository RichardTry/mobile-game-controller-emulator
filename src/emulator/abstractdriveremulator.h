#ifndef IDRIVEREMULATOR_H
#define IDRIVEREMULATOR_H

#include <QObject>

class AbstractTransceiver;
class AbstractDriver;

class AbstractDriverEmulator: public QObject {
    Q_OBJECT
public:
    AbstractDriverEmulator(AbstractDriver *driver, AbstractTransceiver *transceiver, QObject *parent = nullptr): QObject(parent), m_transceiver(transceiver), m_driver(driver) {
    }

public slots:
    virtual void onError(QString error) = 0;
    virtual void onDataArrived(QByteArray data) = 0;
    virtual void onConnected() = 0;
    virtual void onDisconnected(QString msg) = 0;
    virtual void onQuit() = 0;

protected:
    AbstractTransceiver *m_transceiver;
    AbstractDriver *m_driver;
};

#endif // IDRIVEREMULATOR_H
