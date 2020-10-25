#ifndef ABSTRACTTRANSCEIVER_H
#define ABSTRACTTRANSCEIVER_H

#include <QByteArray>
#include <QObject>

class AbstractTransceiver: public QObject {
    Q_OBJECT

public:
    enum Mode{
        Master,
        Slave
    };

    AbstractTransceiver(const Mode &mode, QObject *parent = nullptr): QObject(parent), m_mode(mode) {

    }

    virtual QWidget *connectionMenu() = 0;

signals:
    void dataArrived(const QByteArray &data);

public slots:
    virtual qint64 sendData(const QByteArray &data, const bool &acknowledge = false) = 0;

protected:
    Mode m_mode;
};

#endif // ABSTRACTTRANSCEIVER_H
