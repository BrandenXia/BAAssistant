#ifndef BAASSISTANT_WINDOW_H
#define BAASSISTANT_WINDOW_H

#include <cassert>

#include "spdlog/spdlog.h"

namespace Baa {

class Window {
protected:
    Window() { spdlog::info("Initializing IPhoneMirrorWindow"); };
    double height{}, width{};

public:
    virtual void click(double x, double y) {
        assert(x <= width && y <= height);
        spdlog::info("Clicking at ({}, {})", x, y);
    };

    virtual ~Window() = default;
};
}

#endif  // BAASSISTANT_WINDOW_H
