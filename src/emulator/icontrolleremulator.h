#ifndef ICONTROLLEREMULATOR_H
#define ICONTROLLEREMULATOR_H

#include <QByteArray>

class AbstractTransceiver;
class QWidget;

class IControllerEmulator
{
public:
    IControllerEmulator();

    virtual void setTransceiver(AbstractTransceiver *transceiver) = 0;
    virtual QWidget *widget() = 0;
};

#endif // ICONTROLLEREMULATOR_H
