#ifndef NETWORKTRANSCEIVERWIDGET_H
#define NETWORKTRANSCEIVERWIDGET_H

#include <QWidget>
#include "transceiver/networktransceiver.h"

Q_DECLARE_METATYPE(QHostAddress)

namespace Ui {
class NetworkTransceiverMaster;
class NetworkTransceiverSlave;
}

class NetworkTransceiverWidget : public QWidget {
    Q_OBJECT
public:
    explicit NetworkTransceiverWidget(NetworkTransceiver *transceiver, QWidget *parent = nullptr);

signals:

public slots:
    void onStateChanged(NetworkTransceiver::State state);
    void onHostFound(QString address);

private:
    void loadMasterUI();
    void loadSlaveUI();

    NetworkTransceiver *m_transceiver;
    QList <QHostAddress> m_interfaces;
    // Different ui's loaded for each mode
    Ui::NetworkTransceiverMaster *masterUi;
    Ui::NetworkTransceiverSlave *slaveUi;
};

#endif // NETWORKTRANSCEIVERWIDGET_H
