#include "gamepaddriveremulator.h"
#include <QPointF>

GamepadDriverEmulator::GamepadDriverEmulator(AbstractTransceiver *transceiver, QObject *parent): AbstractDriverEmulator(transceiver, parent) {
    m_toggle = 0;
}

GamepadDriverEmulator::~GamepadDriverEmulator() {
    if(ioctl(m_fd, UI_DEV_DESTROY) < 0)
    {
        printf("error: ioctl");
        return;
    }
    close(m_fd);
}

void GamepadDriverEmulator::onError(QString error) {

}

void GamepadDriverEmulator::onDataArrived(QByteArray data) {

}

void GamepadDriverEmulator::onConnected() {

}

void GamepadDriverEmulator::onDisconnected(QString msg) {

}

void GamepadDriverEmulator::onQuit() {

}

int GamepadDriverEmulator::init() {
    m_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK); //opening of uinput
    if (m_fd < 0) {
        printf("Opening of uinput failed!\n");
        return 1;
    }
    ioctl(m_fd, UI_SET_EVBIT, EV_KEY); //setting Gamepad keys
    ioctl(m_fd, UI_SET_KEYBIT, BTN_A);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_B);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_X);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_Y);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_TL);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_TR);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_TL2);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_TR2);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_START);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_SELECT);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_THUMBL);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_THUMBR);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_DPAD_UP);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_DPAD_DOWN);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_DPAD_LEFT);
    ioctl(m_fd, UI_SET_KEYBIT, BTN_DPAD_RIGHT);
    ioctl(m_fd, UI_SET_EVBIT, EV_ABS); //setting Gamepad thumbsticks
    ioctl(m_fd, UI_SET_ABSBIT, ABS_X);
    ioctl(m_fd, UI_SET_ABSBIT, ABS_Y);
    ioctl(m_fd, UI_SET_ABSBIT, ABS_RX);
    ioctl(m_fd, UI_SET_ABSBIT, ABS_RY);
    memset(&m_uidev, 0, sizeof(m_uidev)); //setting the default settings of Gamepad
    snprintf(m_uidev.name, UINPUT_MAX_NAME_SIZE, "Simple Gamepad"); //Name of Gamepad
    m_uidev.id.bustype = BUS_USB;
    m_uidev.id.vendor  = 0x3;
    m_uidev.id.product = 0x3;
    m_uidev.id.version = 2;
    m_uidev.absmax[ABS_X] = 512; //Parameters of thumbsticks
    m_uidev.absmin[ABS_X] = -512;
    m_uidev.absfuzz[ABS_X] = 0;
    m_uidev.absflat[ABS_X] = 15;
    m_uidev.absmax[ABS_Y] = 512;
    m_uidev.absmin[ABS_Y] = -512;
    m_uidev.absfuzz[ABS_Y] = 0;
    m_uidev.absflat[ABS_Y] = 15;
    m_uidev.absmax[ABS_RX] = 512;
    m_uidev.absmin[ABS_RX] = -512;
    m_uidev.absfuzz[ABS_RX] = 0;
    m_uidev.absflat[ABS_RX] = 16;
    m_uidev.absmax[ABS_RY] = 512;
    m_uidev.absmin[ABS_RY] = -512;
    m_uidev.absfuzz[ABS_RY] = 0;
    m_uidev.absflat[ABS_RY] = 16;
    if(write(m_fd, &m_uidev, sizeof(m_uidev)) < 0) //writing settings
    {
        printf("error: write");
        return 1;
    }
    if(ioctl(m_fd, UI_DEV_CREATE) < 0) //writing ui dev create
    {
        printf("error: ui_dev_create");
        return 1;
    }

//    while(1)
//    {
//        memset(&m_ev, 0, sizeof(struct input_event)); //setting the memory for event
//        m_ev.type = EV_KEY;
//        m_ev.code = BTN_X;
//        m_ev.value = !m_toggle;
//        m_toggle = !m_toggle;
//        if(write(m_fd, &m_ev, sizeof(struct input_event)) < 0) //writing the key change
//        {
//            printf("error: key-write");
//            return 1;
//        }
//        memset(&m_ev, 0, sizeof(struct input_event)); //setting the memory for event
//        m_ev.type = EV_ABS;
//        m_ev.code = ABS_X;
//        m_ev.value = m_toggle == 1 ? 256 : 0;
//        if(write(m_fd, &m_ev, sizeof(struct input_event)) < 0) //writing the thumbstick change
//        {
//            printf("error: thumbstick-write");
//            return 1;
//        }
//        memset(&m_ev, 0, sizeof(struct input_event));
//        m_ev.type = EV_SYN;
//        m_ev.code = SYN_REPORT;
//        m_ev.value = 0;
//        if(write(m_fd, &m_ev, sizeof(struct input_event)) < 0) //writing the sync report
//        {
//            printf("error: sync-report");
//            return 1;
//        }
//    }
}

void GamepadDriverEmulator::onStickMoved(const Button& btn, const QPointF &point) {
    memset(&m_ev, 0, sizeof(struct input_event)); //setting the memory for event
    m_ev.type = EV_ABS;
    m_ev.code = ABS_X;
    m_ev.value = point.x() * 512;
    if(write(m_fd, &m_ev, sizeof(struct input_event)) < 0) //writing the thumbstick change
    {
        printf("error: thumbstick-write");
    }
    memset(&m_ev, 0, sizeof(struct input_event)); //setting the memory for event
    m_ev.type = EV_ABS;
    m_ev.code = ABS_X;
    m_ev.value = point.y() * 512;
    if(write(m_fd, &m_ev, sizeof(struct input_event)) < 0) //writing the thumbstick change
    {
        printf("error: thumbstick-write");
    }
    memset(&m_ev, 0, sizeof(struct input_event));
    m_ev.type = EV_SYN;
    m_ev.code = SYN_REPORT;
    m_ev.value = 0;
    if(write(m_fd, &m_ev, sizeof(struct input_event)) < 0) //writing the sync report
    {
        printf("error: sync-report");
    }
}

void GamepadDriverEmulator::onStickReleased(const Button& btn, const QPointF &point) {

}

void GamepadDriverEmulator::onStickPressed(const Button& btn, const QPointF &point) {

}

void GamepadDriverEmulator::onButtonReleased(const Button &button) {

}

void GamepadDriverEmulator::onButtonPressed(const Button &button) {

}
