#ifndef ABSTRACTDRIVER_H
#define ABSTRACTDRIVER_H

#include <QObject>

class AbstractDriver : public QObject {
    Q_OBJECT
public:
    explicit AbstractDriver(QObject *parent = nullptr);

public slots:
    virtual void onDataArrived(const QByteArray &data) = 0;
    virtual void onConnected() = 0;
    virtual void onDisconnect() = 0;
};

#endif // ABSTRACTDRIVER_H
