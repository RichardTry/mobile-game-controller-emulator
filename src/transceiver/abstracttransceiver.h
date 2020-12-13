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

    virtual ~AbstractTransceiver() {}

    Mode mode() const {
        return m_mode;
    }

signals:
    void error(QString error);
    void dataArrived(QByteArray data);
    void connected();
    void disconnected(QString msg);
    void closeCalled();

public slots:
    virtual qint64 sendData(const QByteArray &data, const bool &acknowledge = false) = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;

protected:
    Mode m_mode;
};

#endif // ABSTRACTTRANSCEIVER_H
