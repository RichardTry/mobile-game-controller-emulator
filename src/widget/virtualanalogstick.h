#ifndef VIRTUALANALOGSTICK_H
#define VIRTUALANALOGSTICK_H

#include <QWidget>
#include <QTimer>

class VirtualAnalogStick : public QWidget {
    Q_OBJECT

public:
    explicit VirtualAnalogStick(QWidget *parent = nullptr);
    ~VirtualAnalogStick();


    QPointF touchPoint() const;
    QPointF normalisedTouchPoint() const;

    int outerRadius() const;
    void setOuterRadius(int outerRadius);

    int innerRadius() const;
    void setInnerRadius(int innerRadius);

    QColor innerColor() const;
    void setInnerColor(const QColor &innerColor);

    QColor outerColor() const;
    void setOuterColor(const QColor &outerColor);

    QSize minimumSizeHint() const override;

signals:
    void touchPointMoved(QPointF normalisedTouchPoint);

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    int heightForWidth(int) const override;

private:
    int m_outerRadius;
    int m_innerRadius;

    int m_lineWidth;
    QColor m_innerColor;
    QColor m_outerColor;

    QPointF m_touchPoint;
    QRect m_innerRect;

    QTimer m_timer;
};

#endif // VIRTUALANALOGSTICK_H
