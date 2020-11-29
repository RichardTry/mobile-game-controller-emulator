#ifndef ABSTRACTCONTROLLEREMULATOR_H
#define ABSTRACTCONTROLLEREMULATOR_H

#include <QByteArray>
#include <QWidget>

class AbstractTransceiver;

class AbstractControllerEmulator: public QWidget {
public:
    AbstractControllerEmulator(AbstractTransceiver *transceiver, QWidget *parent = nullptr): QWidget(parent), m_transceiver(transceiver) {}
    virtual ~AbstractControllerEmulator() {}
    virtual void init() = 0;

protected:
    AbstractTransceiver *m_transceiver;
};

#endif // ABSTRACTCONTROLLEREMULATOR_H
