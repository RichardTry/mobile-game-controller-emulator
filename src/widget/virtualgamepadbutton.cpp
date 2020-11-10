#include "virtualgamepadbutton.h"
#include <QPixmap>
#include <QPainter>
#include <QTouchEvent>
#include <QEvent>

VirtualGamepadButton::VirtualGamepadButton(const Button &btn, QWidget *parent) : QWidget(parent), m_button(btn) {
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_pixmap = Common::buttonIcon(btn);
    m_pressedScale = 0.9;
}

VirtualGamepadButton::~VirtualGamepadButton() {
}

bool VirtualGamepadButton::event(QEvent *event) {
    const QEvent::Type eventType = event->type();

    if(eventType == QEvent::Resize) {
        const QResizeEvent *resizeEvent = static_cast <const QResizeEvent*> (event);
        setMask(QRegion(QRect(QPoint(0, 0), resizeEvent->size()), QRegion::Ellipse));
        return QWidget::event(event);
    }

    if(eventType != QEvent::TouchBegin && eventType != QEvent::TouchUpdate && eventType != QEvent::TouchEnd && eventType != QEvent::TouchCancel) {
        return QWidget::event(event);
    }

//    const QTouchEvent *touchEvent = static_cast <const QTouchEvent*> (event);

    switch (event->type()) {
        case QEvent::TouchEnd: {
            emit released(m_button);
            m_pressed = false;
            repaint();
            return true;
        }
        case QEvent::TouchCancel: {
            m_pressed = false;
            repaint();
            return true;
        }
        case QEvent::TouchBegin: {
            emit pressed(m_button);
            m_pressed = true;
            repaint();
            return true;
        }
        default: {
            return true;
        }
    }

}

void VirtualGamepadButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if(!m_pressed)
        painter.drawPixmap(rect(), *m_pixmap);
    else {
        const int sX = rect().x() + rect().width() * (1 - m_pressedScale) * 0.5;
        const int sY = rect().y() + rect().height() * (1 - m_pressedScale) * 0.5;
        const int sW = rect().width() * m_pressedScale;
        const int sH = rect().height() * m_pressedScale;
        painter.drawPixmap(QRect(sX, sY, sW, sH), *m_pixmap);
    }
}

int VirtualGamepadButton::heightForWidth(int w) const {
    return w;
}