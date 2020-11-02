#ifndef ABSTRACTTRANSCEIVER_H
#define ABSTRACTTRANSCEIVER_H

#include <QByteArray>
#include <QWidget>

class AbstractTransceiver: public QWidget {
    Q_OBJECT

public:
    enum Mode{
        Master,
        Slave
    };

    AbstractTransceiver(const Mode &mode, QWidget *parent = nullptr): QWidget(parent), m_mode(mode) {

    }

    virtual ~AbstractTransceiver() {}

signals:
    void dataArrived(QByteArray data);
    void connected();
    void disconnected(QString msg);
    void quit();

public slots:
    virtual qint64 sendData(const QByteArray &data, const bool &acknowledge = false) = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;

protected:
    Mode m_mode;
};

#endif // ABSTRACTTRANSCEIVER_H
