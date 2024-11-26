#include "control/window.h"

#define CHECK_BOUNDS(point) assert(point.x <= width && point.y <= height)

namespace Baa {

auto format_as(const Point &point) {
    return fmt::format("({}, {})", point.x, point.y);
}

Window::Window() : width(0), height(0) { LOG_INFO("Initializing Window"); }

void Window::mousedown(Baa::Point point) {
    CHECK_BOUNDS(point);
    LOG_INFO("Mouse down at {}", point);
};

void Window::mouseup(Baa::Point point) {
    CHECK_BOUNDS(point);
    LOG_INFO("Mouse up at {}", point);
};

}