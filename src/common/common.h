#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QMap>
#include <QSharedPointer>

#define BUTTONS_DEFINITIONS \
BUTTON_DEF(X, 0) \
BUTTON_DEF(Y, 1) \
BUTTON_DEF(B, 2) \
BUTTON_DEF(A, 3) \
BUTTON_DEF(START, 4) \
BUTTON_DEF(BACK, 5) \
BUTTON_DEF(GUIDE, 6) \
BUTTON_DEF(LEFTTRIGGER, 7) \
BUTTON_DEF(RIGHTTRIGGER, 8) \
BUTTON_DEF(LEFTBUMPER, 9) \
BUTTON_DEF(RIGHTBUMPER, 10) \
BUTTON_DEF(UP, 11) \
BUTTON_DEF(DOWN, 12) \
BUTTON_DEF(LEFT, 13) \
BUTTON_DEF(RIGHT, 14) \
BUTTON_DEF(LEFTSTICK, 15) \
BUTTON_DEF(RIGHTSTICK, 16) \
BUTTON_DEF(DPAD, 17) \
BUTTON_DEF(COUNT, 18) \

enum Button {
#define BUTTON_DEF(x, y) x = 1 << y,
BUTTONS_DEFINITIONS
#undef BUTTON_DEF
};

static inline QString labelForButton(const Button &button) {
    switch (button) {
#define BUTTON_DEF(x, y) case x: return #x;
BUTTONS_DEFINITIONS
#undef BUTTON_DEF
        default: return "";
    }
}

static inline Button buttonForLabel(const QString &label) {
#define BUTTON_DEF(x, y) if(#x == label) return Button(x);
BUTTONS_DEFINITIONS
#undef BUTTON_DEF
    return Button::COUNT;
}

class Common {
public:
    static QSharedPointer <QPixmap> buttonIcon(const int& btns);
    static QSharedPointer <QPixmap> buttonIcon(const int& btn, const QSize &size);
    static QSharedPointer <QPixmap> buttonPressedIcon(const int& btn, const QSize &size);
    static void loadIcons();

private:
    static QMap <int, QSharedPointer<QPixmap>> m_iconMap;
    static QMap <int, QSharedPointer<QPixmap>> m_iconPressedMap;
};

#endif // COMMON_H
