#include "virtualdirectionalpad.h"
#include <QEvent>
#include <QTouchEvent>
#include <QtMath>
#include <QPainter>
#include <QDebug>

VirtualDirectionalPad::VirtualDirectionalPad(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_AcceptTouchEvents);

    m_increment = 45;
    m_startAngle = 0;
    m_endAngle = 360;
    m_offset = -m_increment/2;

    m_outerRadius = 100;
    m_innerRadius = m_outerRadius/3;
    m_pressedButtons = 0;

    m_resizePixmap = true;

    // Transitional region [337.5, 22.5] broken up into two pieces because no positive angle could between these two values
    m_regions.push_back(DpadRegion(337.5, 360, Button::RIGHT));
    m_regions.push_back(DpadRegion(0, 22.5, Button::RIGHT));
    // Rest are all positive values
    m_regions.push_back(DpadRegion(1 * m_increment + m_offset, 2 * m_increment + m_offset, Button::RIGHT | Button::DOWN));
    m_regions.push_back(DpadRegion(2 * m_increment + m_offset, 3 * m_increment + m_offset, Button::DOWN));
    m_regions.push_back(DpadRegion(3 * m_increment + m_offset, 4 * m_increment + m_offset, Button::DOWN | Button::LEFT));
    m_regions.push_back(DpadRegion(4 * m_increment + m_offset, 5 * m_increment + m_offset, Button::LEFT));
    m_regions.push_back(DpadRegion(5 * m_increment + m_offset, 6 * m_increment + m_offset, Button::LEFT | Button::UP));
    m_regions.push_back(DpadRegion(6 * m_increment + m_offset, 7 * m_increment + m_offset, Button::UP));
    m_regions.push_back(DpadRegion(7 * m_increment + m_offset, 8 * m_increment + m_offset, Button::UP | Button::RIGHT));

    loadIcons();
}

VirtualDirectionalPad::~VirtualDirectionalPad() {
}

QSize VirtualDirectionalPad::minimumSizeHint() const {
    return QSize(100, 100);
}

bool VirtualDirectionalPad::event(QEvent *event) {
    QEvent::Type eventType = event->type();

    if(eventType == QEvent::Resize) {
        const QResizeEvent *resizeEvent = static_cast <const QResizeEvent*> (event);
        m_resizePixmap = true;
        m_outerRadius = resizeEvent->size().width()/2;
        m_innerRadius = m_outerRadius/3;
        return QWidget::event(event);
    }

    if(eventType != QEvent::TouchBegin && eventType != QEvent::TouchUpdate && eventType != QEvent::TouchEnd && eventType != QEvent::TouchCancel) {
        return QWidget::event(event);
    }

    if(!m_timer.isActive()) {
        m_timer.start();
    }

    const QTouchEvent *touchEvent = static_cast <const QTouchEvent*> (event);

    // DETERMINE WHICH REGION WAS TOUCHED
    const QPointF rawTouchPoint = touchEvent->touchPoints().first().pos();
    const QPoint origin = this->rect().center();
    const qreal distanceFromOrigin = (rawTouchPoint - origin).manhattanLength();
    const QLineF line(origin, rawTouchPoint.toPoint());
    const qreal lineAngle = 360-line.angle();
    // 1-) Central region touched
    if(0 <= distanceFromOrigin && distanceFromOrigin <= m_innerRadius) {
        m_pressedButtons = 0;
    }
    // 2-) Button region touched, one of 4 directions or a diagonal combination of two
    else if (m_innerRadius < distanceFromOrigin && distanceFromOrigin <= m_outerRadius) {
        // Iterate through all regions to see which region the click has happened in
        for(DpadRegion region: m_regions) {
            if(region.startAngle < lineAngle && lineAngle <= region.endAngle) {
                m_pressedButtons = region.pressedButtons;
                break;
            }
        }
    }
    // 3-) No valid region touched return before emitting a signal
    else {
        m_pressedButtons = 1453;
    }

    if(m_pressedButtons != m_pressedButtonsPrevious)
        repaint();
    m_pressedButtonsPrevious = m_pressedButtons;

    switch (event->type()) {
        case QEvent::TouchEnd: {
            emit released(m_pressedButtons);
            m_pressedButtons = 0;
            repaint();
            return true;
        }
        case QEvent::TouchCancel: {
            emit released(m_pressedButtons);
            m_pressedButtons = 0;
            repaint();
            return true;
        }
        case QEvent::TouchBegin: {
            emit pressed(m_pressedButtons);
            repaint();
            return true;
        }
        default: {
            return true;
        }
    }
}

void VirtualDirectionalPad::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    const quint32 key = m_pixmap.contains(m_pressedButtons) ? m_pressedButtons : 0;
    QPixmap &pixmap = m_pixmap[key];
    if(m_resizePixmap) {
        m_currentPixmap = pixmap.scaled(rect().size());
    }
    else {
        m_currentPixmap = pixmap;
    }
    painter.drawPixmap(rect(), m_currentPixmap);
    m_resizePixmap = false;
}

int VirtualDirectionalPad::heightForWidth(int w) const {
    return w;
}

void VirtualDirectionalPad::loadIcons() {
    Button btnArray[4] = {Button::UP, Button::DOWN, Button::LEFT, Button::RIGHT};
    for(Button btn: btnArray) {
        m_pixmap[static_cast<quint32>(btn)] = QPixmap(":/dpad-" + labelForButton(btn).toLower() + ".svg");
    }

    m_pixmap[0] = QPixmap(":/dpad.svg");
    m_pixmap[Button::UP | Button::LEFT] = QPixmap(":/dpad-up-left.svg");
    m_pixmap[Button::UP | Button::RIGHT] = QPixmap(":/dpad-up-right.svg");
    m_pixmap[Button::DOWN | Button::LEFT] = QPixmap(":/dpad-down-left.svg");
    m_pixmap[Button::DOWN | Button::RIGHT] = QPixmap(":/dpad-down-right.svg");
}
