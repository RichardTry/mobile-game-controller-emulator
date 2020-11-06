#include "virtualanalogstick.h"
#include <QTouchEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

VirtualAnalogStick::VirtualAnalogStick(QWidget *parent) : QWidget(parent), m_touchPoint(this->rect().center()) {
    setAttribute(Qt::WA_AcceptTouchEvents);

    m_innerRadius = 50;
    m_innerRadius = 150;

    m_innerColor = QColor(32, 32, 32, 128);
    m_outerColor = QColor(255, 32, 32, 255);
    m_lineWidth = 10;

    m_timer.setInterval(25);
    m_timer.setSingleShot(true);
    QWidget::connect(&m_timer, &QTimer::timeout, this, QOverload <>::of (&QWidget::repaint));
    m_timer.start();
}

VirtualAnalogStick::~VirtualAnalogStick() {
    m_timer.stop();
}

bool VirtualAnalogStick::event(QEvent *event) {
    QEvent::Type eventType = event->type();

    if(eventType == QEvent::Resize) {
        const QResizeEvent *resizeEvent = static_cast <const QResizeEvent *> (event);
        const qreal w = resizeEvent->size().width();
        const qreal h = resizeEvent->size().height();
        qreal ri = (w < h ? w : h) / 2;
        ri *= (qreal)innerRadius() / (qreal) outerRadius();
        setInnerRadius(ri);
        qreal ro = (w < h ? w : h) / 2;
        setOuterRadius(ro);
        return QWidget::event(event);
    }

    if(eventType != QEvent::TouchBegin && eventType != QEvent::TouchUpdate && eventType != QEvent::TouchEnd && eventType != QEvent::TouchCancel) {
        return QWidget::event(event);
    }

    if(!m_timer.isActive()) {
        m_timer.start();
    }

    const QTouchEvent *touchEvent = static_cast <const QTouchEvent*> (event);

    switch (event->type()) {
        case QEvent::TouchEnd: {
            m_touchPoint = this->rect().center();
            emit touchPointMoved(normalisedTouchPoint());
            return true;
        }
        case QEvent::TouchCancel: {
            m_touchPoint = this->rect().center();
            emit touchPointMoved(normalisedTouchPoint());
            return true;
        }
        default: {
            const QPointF rawTouchPoint = touchEvent->touchPoints().first().pos();
            const QPoint origin = this->rect().center();
            if((rawTouchPoint - origin).manhattanLength() > m_outerRadius - m_innerRadius) {
                QLineF line(origin, rawTouchPoint.toPoint());
                m_touchPoint.setY(qSin(qDegreesToRadians(360-line.angle())) * (m_outerRadius - m_innerRadius) + origin.y());
                m_touchPoint.setX(qCos(qDegreesToRadians(360-line.angle())) * (m_outerRadius - m_innerRadius) + origin.x());
            } else {
                m_touchPoint = rawTouchPoint;
            }
            emit touchPointMoved(normalisedTouchPoint());
            return true;
        }
    }

}

QPointF VirtualAnalogStick::touchPoint() const {
    return m_touchPoint;
}

QPointF VirtualAnalogStick::normalisedTouchPoint() const {
    return (m_touchPoint - rect().center())/(m_outerRadius - m_innerRadius);
}

void VirtualAnalogStick::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPen pen = painter.pen();
    pen.setWidth(m_lineWidth);
    const QPoint origin = this->rect().center();

    // Outer circle
    pen.setColor(m_outerColor);
    painter.setPen(pen);
    painter.drawEllipse(origin, m_outerRadius - m_lineWidth, m_outerRadius - m_lineWidth);

    // Inner circle
    pen.setColor(m_innerColor);
    painter.setPen(pen);
    painter.drawEllipse(m_touchPoint, m_innerRadius - m_lineWidth, m_innerRadius - m_lineWidth);

//#if defined (QT_DEBUG)
//    // Draw x axis positive side
//    pen.setColor(QColor(0, 255, 0));
//    painter.setPen(pen);
//    painter.drawLine(QLine(origin + QPoint(m_lineWidth, 0), origin + QPoint(m_outerRadius, 0)));
//    // Label axis
//    QFontMetrics fm(painter.font());
//    int textWidth = fm.horizontalAdvance("+x");
//    painter.drawText(origin + QPoint(m_outerRadius - textWidth, -20), "+x");

//    // Draw y axis positive side
//    pen.setColor(QColor(255, 0, 0));
//    painter.setPen(pen);
//    painter.drawLine(QLine(origin + QPoint(0, m_lineWidth), origin + QPoint(0, m_outerRadius)));
//    // Label axis
//    int textHeight = fm.boundingRect("+y").height();
//    painter.drawText(origin + QPoint(-textHeight, m_outerRadius), "+y");

//    // Draw line from origin to touch point's center
//    pen.setColor(QColor(0, 0, 0));
//    pen.setWidth(m_lineWidth/2 > 0 ? m_lineWidth/2 : 1);
//    painter.setPen(pen);
//    painter.drawLine(QLine(origin, m_touchPoint.toPoint()));
//#endif
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
    return QSize(m_outerRadius * 2, m_outerRadius * 2);
}

//void VirtualAnalogStick::setGeometry(const QRect &r) {
//    setInnerRadius(r.width()/2 * (m_innerRadius/m_outerRadius));
//    setOuterRadius(r.width()/2);
//    QWidget::setGeometry(r);
//}

//void VirtualAnalogStick::setGeometry(int x, int y, int w, int h) {
//    setInnerRadius(w/2 * (m_innerRadius/m_outerRadius));
//    setOuterRadius(w/2);
//    QWidget::setGeometry(x, y, w, h);
//}
