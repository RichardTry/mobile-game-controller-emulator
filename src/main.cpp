#include <QApplication>
#include <QWidget>
#include <QTimer>
#include "transceiver/network/networktransceiver.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
#if defined(DRIVER)
    NetworkTransceiver transceiver(NetworkTransceiver::Mode::Slave);
    transceiver.widget()->show();
#elif defined(CONTROLLER)
    NetworkTransceiver transceiver(NetworkTransceiver::Mode::Master);
    transceiver.widget()->show();
#endif
    return app.exec();
}
