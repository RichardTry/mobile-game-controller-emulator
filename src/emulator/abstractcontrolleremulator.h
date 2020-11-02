#ifndef ABSTRACTCONTROLLEREMULATOR_H
#define ABSTRACTCONTROLLEREMULATOR_H

#include <QByteArray>
#include <QWidget>

class AbstractTransceiver;

class AbstractControllerEmulator: public QWidget {
public:
    AbstractControllerEmulator(QWidget *parent = nullptr): QWidget(parent) {}
    virtual ~AbstractControllerEmulator() {}

    virtual void setTransceiver(AbstractTransceiver *transceiver) = 0;
};

#endif // ABSTRACTCONTROLLEREMULATOR_H
