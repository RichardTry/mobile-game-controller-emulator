#ifndef VIRTUALANALOGSTICK_H
#define VIRTUALANALOGSTICK_H

#include <QWidget>

class VirtualAnalogStick : public QWidget {
    Q_OBJECT

public:
    explicit VirtualAnalogStick(QWidget *parent = nullptr);
    ~VirtualAnalogStick();


    QPointF touchPoint() const;

signals:

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    int heightForWidth(int) const override;

private:
    int m_outerRadius;
    int m_innerRadius;
    QPixmap m_innerPixmap;
    QPixmap m_outerPixmap;
    QPointF m_touchPoint;
    QRect m_innerRect;
};

#endif // VIRTUALANALOGSTICK_H
