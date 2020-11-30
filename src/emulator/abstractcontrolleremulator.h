#ifndef ABSTRACTCONTROLLEREMULATOR_H
#define ABSTRACTCONTROLLEREMULATOR_H

#include <QByteArray>
#include <QWidget>

class AbstractTransceiver;

class AbstractControllerEmulator: public QWidget {
    Q_OBJECT
public:
    AbstractControllerEmulator(AbstractTransceiver *transceiver, QWidget *parent = nullptr): QWidget(parent), m_transceiver(transceiver) {}
    virtual ~AbstractControllerEmulator() {}

signals:
    void quit();

protected:
    AbstractTransceiver *m_transceiver;
};

#endif // ABSTRACTCONTROLLEREMULATOR_H
