#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum Button {
#define BUTTON_DEF(x) x,
#include "button.def"
#undef BUTTON_DEF
    COUNT,
};

static inline QString buttonLabel(const Button &button) {
    switch (button) {
#define BUTTON_DEF(x) case x: return #x;
#include "button.def"
#undef BUTTON_DEF
    }
}

#endif // COMMON_H
