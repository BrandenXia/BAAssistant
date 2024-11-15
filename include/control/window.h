#ifndef BAASSISTANT_WINDOW_H
#define BAASSISTANT_WINDOW_H

#include <cassert>

#include "log.h"

namespace Baa {

struct Point {
    double x, y;
};

class Window {
protected:
    Window();
    double height{}, width{};

public:
    virtual void mousedown(Point point);
    virtual void mouseup(Point point);
    virtual ~Window() = default;
};
}

#endif  // BAASSISTANT_WINDOW_H
