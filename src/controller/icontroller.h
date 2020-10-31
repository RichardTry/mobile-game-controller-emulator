#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QByteArray>

class IController {
public:
    IController();
    virtual ~IController() {}

    virtual QByteArray getData() = 0;
    virtual void setData(const QByteArray &data) = 0;
};

#endif // ICONTROLLER_H
