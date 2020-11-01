#include "virtualanalogstick.h"
#include <QTouchEvent>
#include <QPainter>
#include <QDebug>

VirtualAnalogStick::VirtualAnalogStick(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_innerPixmap.load(":/SmallHandle.png");
    m_outerPixmap.load(":/Joystick.png");
}

VirtualAnalogStick::~VirtualAnalogStick() {

}

bool VirtualAnalogStick::event(QEvent *event) {

    QEvent::Type eventType = event->type();

    if(eventType != QEvent::TouchBegin && eventType != QEvent::TouchUpdate && eventType != QEvent::TouchEnd && eventType != QEvent::TouchCancel) {
        return QWidget::event(event);
    }

    const QTouchEvent *touchEvent = static_cast <const QTouchEvent*> (event);

    m_touchPoint = touchEvent->touchPoints().first().pos();
    qDebug() << m_touchPoint;
//    for (QTouchEvent::TouchPoint point: touchEvent->touchPoints() ) {
//        m_touchPoint = point.pos();
//    }

    switch (event->type()) {
        case QEvent::TouchBegin: {
            return true;
        }
        case QEvent::TouchUpdate: {
            return true;
        }
        case QEvent::TouchEnd: {
            return true;
        }
        case QEvent::TouchCancel: {
            m_touchPoint = this->rect().center();
            return true;
        }
    }
}

QPointF VirtualAnalogStick::touchPoint() const {
    return m_touchPoint;
}

void VirtualAnalogStick::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(this->rect(), m_outerPixmap);

    QRect innerRect = QRect(0, 0, m_innerPixmap.width(), m_innerPixmap.height());
    innerRect.setTopLeft(QPoint(m_touchPoint.x() - innerRect.width()/2, m_touchPoint.y() - innerRect.height()/2));
    painter.drawPixmap(innerRect, m_innerPixmap);

    painter.drawLine(QLine(0, 0, 128, 128));
}

int VirtualAnalogStick::heightForWidth(int w) const {
    return w;
}
