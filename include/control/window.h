#ifndef BAASSISTANT_WINDOW_H
#define BAASSISTANT_WINDOW_H

#include <cassert>

#include "frame.h"
#include "log.h"

namespace Baa {

struct Point {
    double x, y;
};

class Window {
protected:
    Window();
    double height, width;

public:
    virtual ~Window() = default;
    virtual void mouseup(Point point);
    virtual void mousedown(Point point);
    virtual Frame getFrame() = 0;
};
}

#endif  // BAASSISTANT_WINDOW_H
