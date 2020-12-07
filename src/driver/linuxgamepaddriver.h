#ifndef LINUXGAMEPADDRIVER_H
#define LINUXGAMEPADDRIVER_H

#include "driver/abstractdriver.h"

class LinuxGamepadDriver : public AbstractDriver {
    Q_OBJECT
public:
    LinuxGamepadDriver(QObject *parent = nullptr);

public slots:
    void onDataArrived(const QByteArray &data);
};

#endif // LINUXGAMEPADDRIVER_H
