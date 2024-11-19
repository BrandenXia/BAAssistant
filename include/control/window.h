#ifndef BAASSISTANT_WINDOW_H
#define BAASSISTANT_WINDOW_H

#include <cassert>
#include <opencv2/opencv.hpp>

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
    virtual ~Window() = default;
    virtual void mouseup(Point point);
    virtual void mousedown(Point point);
    virtual void getImg(cv::Mat &img);
};
}

#endif  // BAASSISTANT_WINDOW_H
