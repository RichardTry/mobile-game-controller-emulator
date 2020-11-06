#ifndef COMMON_H
#define COMMON_H

#include <QString>

#define BUTTONS_DEFINITIONS \
BUTTON_DEF(X) \
BUTTON_DEF(Y) \
BUTTON_DEF(B) \
BUTTON_DEF(A) \
BUTTON_DEF(START) \
BUTTON_DEF(BACK) \
BUTTON_DEF(GUIDE) \
BUTTON_DEF(LEFTTRIGGER) \
BUTTON_DEF(RIGHTTRIGGER) \
BUTTON_DEF(LEFTBUMPER) \
BUTTON_DEF(RIGHTBUMPER) \
BUTTON_DEF(UP) \
BUTTON_DEF(DOWN) \
BUTTON_DEF(LEFT) \
BUTTON_DEF(RIGHT) \
BUTTON_DEF(LEFTSTICK) \
BUTTON_DEF(RIGHTSTICK) \
BUTTON_DEF(COUNT) \

enum Button {
#define BUTTON_DEF(x) x,
BUTTONS_DEFINITIONS
#undef BUTTON_DEF
};

static inline QString labelForButton(const Button &button) {
    switch (button) {
#define BUTTON_DEF(x) case x: return #x;
BUTTONS_DEFINITIONS
#undef BUTTON_DEF
    }
}

static inline Button buttonForLabel(const QString &label) {
#define BUTTON_DEF(x) if(#x == label) return Button(x);
BUTTONS_DEFINITIONS
#undef BUTTON_DEF
    return Button::COUNT;
}

#endif // COMMON_H
