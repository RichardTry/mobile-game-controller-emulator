#ifndef VIRTUALGAMEPADBUTTON_H
#define VIRTUALGAMEPADBUTTON_H

#include <QWidget>
#include "common/common.h"

class VirtualGamepadButton : public QWidget {
    Q_OBJECT
public:
    explicit VirtualGamepadButton(const Button &btn, QWidget *parent = nullptr);
    ~VirtualGamepadButton();

signals:

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    int heightForWidth(int) const override;

private:
    void loadIcons();

    bool m_pressed;
    Button m_button;
    QSharedPointer <QPixmap> m_pressedPixmap;
    QSharedPointer <QPixmap> m_releasedPixmap;
};

#endif // VIRTUALGAMEPADBUTTON_H
