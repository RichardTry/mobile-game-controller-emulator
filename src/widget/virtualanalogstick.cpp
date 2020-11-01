#include "virtualanalogstick.h"
#include <QTouchEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

VirtualAnalogStick::VirtualAnalogStick(QWidget *parent) : QWidget(parent), m_touchPoint(this->rect().center()) {
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_innerPixmap.load(":/SmallHandle.png");
    m_outerPixmap.load(":/Joystick.png");
    m_timer.setInterval(50);
    QWidget::connect(&m_timer, &QTimer::timeout, this, QOverload <>::of (&QWidget::repaint));
    m_timer.start();
}

VirtualAnalogStick::~VirtualAnalogStick() {
    m_timer.stop();
}

bool VirtualAnalogStick::event(QEvent *event) {
    QEvent::Type eventType = event->type();

    if(eventType != QEvent::TouchBegin && eventType != QEvent::TouchUpdate && eventType != QEvent::TouchEnd && eventType != QEvent::TouchCancel) {
        return QWidget::event(event);
    }

    const QTouchEvent *touchEvent = static_cast <const QTouchEvent*> (event);

    switch (event->type()) {
        case QEvent::TouchEnd: {
            m_touchPoint = this->rect().center();
            return true;
        }
        case QEvent::TouchCancel: {
            m_touchPoint = this->rect().center();
            return true;
        }
        default: {
            m_touchPoint = touchEvent->touchPoints().first().pos();
            if(!this->rect().contains(m_touchPoint.toPoint())) {
                QLineF line(m_touchPoint.toPoint(), this->rect().center());
                QPointF closestPoint;
                closestPoint.setY(qSin(qDegreesToRadians(line.angle())) * (height() / 2) + this->rect().center().y());
                closestPoint.setX(qCos(qDegreesToRadians(line.angle()) + M_PI) * (width() / 2) + this->rect().center().x());
                m_touchPoint = closestPoint;
                qDebug() << m_touchPoint;
                return true;
            }
            qDebug() << m_touchPoint;
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

    const int innerWidth = m_innerPixmap.width();
    QPoint topLeft = QPoint(m_touchPoint.x() - innerWidth/2, m_touchPoint.y() - innerWidth/2);
    painter.drawPixmap(topLeft, m_innerPixmap);
}

int VirtualAnalogStick::heightForWidth(int w) const {
    return w;
}
