#pragma once
#include "Console.h"

class Colors {
    static inline bool enabled = true;

public:
    static void apply(Color c) {
        if (enabled)
            set_color(c);
        else
            reset_color();
    }

    static void toggle() {
        enabled = !enabled;
    }

    static bool isEnabled() {
        return enabled;
    }
};
