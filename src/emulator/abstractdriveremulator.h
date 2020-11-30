#ifndef IDRIVEREMULATOR_H
#define IDRIVEREMULATOR_H

#include <QObject>

class AbstractTransceiver;

class AbstractDriverEmulator: public QObject {
    Q_OBJECT
public:
    AbstractDriverEmulator(AbstractTransceiver *transceiver, QObject *parent = nullptr): QObject(parent), m_transceiver(transceiver) {
    }

protected:
    AbstractTransceiver *m_transceiver;
};

#endif // IDRIVEREMULATOR_H
