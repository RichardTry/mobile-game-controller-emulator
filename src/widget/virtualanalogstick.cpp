#include "virtualanalogstick.h"
#include <QTouchEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

VirtualAnalogStick::VirtualAnalogStick(QWidget *parent) : QWidget(parent), m_touchPoint(this->rect().center()) {
    setAttribute(Qt::WA_AcceptTouchEvents);

    m_innerColor = QColor(32, 32, 32, 128);
    m_outerColor = QColor(255, 32, 32, 255);
    m_lineWidth = 10;

    m_timer.setInterval(25);
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
            if((m_touchPoint - this->rect().center()).manhattanLength() > m_outerRadius - m_innerRadius) {
                QLineF line(m_touchPoint.toPoint(), this->rect().center());
                QPointF closestPoint;
                closestPoint.setY(qSin(qDegreesToRadians(line.angle())) * (m_outerRadius - m_innerRadius) + this->rect().center().y());
                closestPoint.setX(qCos(qDegreesToRadians(line.angle()) + M_PI) * (m_outerRadius - m_innerRadius) + this->rect().center().x());
                m_touchPoint = closestPoint;
                return true;
            }
            return true;
        }
    }

}

QPointF VirtualAnalogStick::touchPoint() const {
    return m_touchPoint;
}

void VirtualAnalogStick::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPen pen = painter.pen();
    pen.setWidth(m_lineWidth);

    // Outer circle
    pen.setColor(m_outerColor);
    painter.setPen(pen);
    painter.drawEllipse(this->rect().center(), m_outerRadius - m_lineWidth, m_outerRadius - m_lineWidth);

    // Inner circle
    pen.setColor(m_innerColor);
    painter.setPen(pen);
    painter.drawEllipse(m_touchPoint, m_innerRadius - m_lineWidth, m_innerRadius - m_lineWidth);
}

int VirtualAnalogStick::heightForWidth(int w) const {
    return w;
}

QColor VirtualAnalogStick::outerColor() const
{
    return m_outerColor;
}

void VirtualAnalogStick::setOuterColor(const QColor &outerColor)
{
    m_outerColor = outerColor;
}

QColor VirtualAnalogStick::innerColor() const
{
    return m_innerColor;
}

void VirtualAnalogStick::setInnerColor(const QColor &innerColor)
{
    m_innerColor = innerColor;
}

int VirtualAnalogStick::innerRadius() const {
    return m_innerRadius;
}

void VirtualAnalogStick::setInnerRadius(int innerRadius) {
    m_innerRadius = innerRadius;
}

int VirtualAnalogStick::outerRadius() const {
    return m_outerRadius;
}

void VirtualAnalogStick::setOuterRadius(int outerRadius) {
    m_outerRadius = outerRadius;
}

QSize VirtualAnalogStick::minimumSizeHint() const {
    return QSize(m_outerRadius * 2.1, m_outerRadius * 2.1);
}
