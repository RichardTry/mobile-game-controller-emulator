#ifndef ABSTRACTCONTROLLEREMULATOR_H
#define ABSTRACTCONTROLLEREMULATOR_H

#include <QByteArray>
#include <QWidget>

class AbstractController;
class AbstractTransceiver;

class AbstractControllerEmulator: public QWidget {
    Q_OBJECT
public:
    AbstractControllerEmulator(AbstractTransceiver *transceiver, AbstractController *controller, QWidget *parent = nullptr): QWidget(parent), m_transceiver(transceiver), m_controller(controller) {}
    virtual ~AbstractControllerEmulator() {}

signals:
    void closeCalled();
    void sendData(const QByteArray &data);

public slots:
    virtual void onEventTriggered(const QByteArray &data) = 0;

protected:
    AbstractController *m_controller;
    AbstractTransceiver *m_transceiver;
};

#endif // ABSTRACTCONTROLLEREMULATOR_H
