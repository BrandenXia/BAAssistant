#include "control/window.h"

#define CHECK_BOUNDS(point) assert(point.x <= width && point.y <= height)

namespace Baa {

auto format_as(const Point &point) {
    return fmt::format("({}, {})", point.x, point.y);
}

Window::Window() { LOG_INFO("Initializing IPhoneMirrorWindow"); }

void Window::mousedown(Baa::Point point) {
    CHECK_BOUNDS(point);
    LOG_INFO("Mouse down at {}", point);
};

void Window::mouseup(Baa::Point point) {
    CHECK_BOUNDS(point);
    LOG_INFO("Mouse up at {}", point);
};

void Window::getImg(cv::Mat &img) { LOG_INFO("Getting image"); };

}