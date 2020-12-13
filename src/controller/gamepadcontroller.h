#ifndef GAMEPADCONTROLLER_H
#define GAMEPADCONTROLLER_H

#include "controller/abstractcontroller.h"
#include "layout/gamepadsvglayout.h"
#include "widget/virtualdirectionalpad.h"
#include "widget/virtualanalogstick.h"
#include "widget/virtualgamepadbutton.h"
#include <QWidget>
#include <QThread>
#include <QTimer>

class GamepadController : public AbstractController {
    Q_OBJECT
public:
    GamepadController(QWidget *parent = nullptr);
    ~GamepadController();

private slots:
    void onStickMoved(const Button& btn, const QPointF &point);
    void onStickReleased(const Button& btn, const QPointF &point);
    void onStickPressed(const Button& btn, const QPointF &point);
    void onButtonReleased(const Button& btn);
    void onButtonPressed(const Button& btn);

private:
    class ConcurrentTimer;
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool event(QEvent *event) override; // Implement to handle volume buttons
    Button m_volumeUpButton; // Gamepad button mapped to volume up
    Button m_volumeDownButton; // Gamepad button mapped to volume down

    GamepadSvgLayout *m_svgLayout;
    VirtualDirectionalPad *m_dpad;
    VirtualAnalogStick *m_rightStick;
    VirtualAnalogStick *m_leftStick;
    // North, South, East, West in linux gamepad specs
    VirtualGamepadButton *m_a;
    VirtualGamepadButton *m_b;
    VirtualGamepadButton *m_x;
    VirtualGamepadButton *m_y;

    VirtualGamepadButton *m_start;
    VirtualGamepadButton *m_back;

    VirtualGamepadButton *m_rightTrigger;
    VirtualGamepadButton *m_leftTrigger;

    VirtualGamepadButton *m_rightBumper;
    VirtualGamepadButton *m_leftBumper;

    VirtualGamepadButton *m_close;

    ConcurrentTimer *m_concurrentTimer;
    int m_timeoutms;
};

class GamepadController::ConcurrentTimer: public QThread {
    Q_OBJECT
public:
    ConcurrentTimer(int periodms, bool singleShot = false);

signals:
    void timeout();

public slots:
    void startTimer();
    void stopTimer();

private:
    int m_periodms;
    QTimer m_timer;
};


#endif // GAMEPADCONTROLLER_H
