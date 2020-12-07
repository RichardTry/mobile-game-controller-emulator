#include <QApplication>
#include <QThread>
#include "transceiver/network/networktransceiver.h"
#include "widget/networktransceiverwidget.h"
#include "emulator/androidcontrolleremulator.h"
#include "controller/gamepadcontroller.h"
#include "emulator/genericdriveremulator.h"
#include "driver/linuxgamepaddriver.h"

class NetworkWorker: public QThread {
public:
    NetworkWorker(const AbstractTransceiver::Mode &mode, QObject *parent = nullptr) {
        m_networkTransceiver = new NetworkTransceiver(mode);
    }

    ~NetworkWorker() {
        m_networkTransceiver->deleteLater();
    }

    NetworkTransceiver *networkTransceiver() const {
        return m_networkTransceiver;
    }

private:
    NetworkTransceiver *m_networkTransceiver;
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

#if defined(DRIVER)
    NetworkWorker worker(AbstractTransceiver::Mode::Slave);
    AbstractTransceiver *transceiver = worker.networkTransceiver();
    AbstractDriver *driver = new LinuxGamepadDriver;
    GenericDriverEmulator *drivemu = new GenericDriverEmulator(driver, transceiver);
    NetworkTransceiverWidget widget((NetworkTransceiver*)transceiver);
    widget.show();
#elif defined(CONTROLLER)
    NetworkWorker worker(AbstractTransceiver::Mode::Master);
    AbstractTransceiver *transceiver = worker.networkTransceiver();
    NetworkTransceiverWidget comWidget((NetworkTransceiver*)transceiver);
    comWidget.show();
    AbstractController *controller = new GamepadController;
    AndroidControllerEmulator *conemu = new AndroidControllerEmulator(transceiver, controller);
    QObject::connect(transceiver, &AbstractTransceiver::connected, &comWidget, &QWidget::hide);
    QObject::connect(transceiver, &AbstractTransceiver::connected, conemu, &QWidget::show);
#endif

    return app.exec();
}
