#ifndef BAASSISTANT_IPHONE_MIRROR_H
#define BAASSISTANT_IPHONE_MIRROR_H

#import <CoreGraphics/CoreGraphics.h>
#ifdef NO  // workaround for conflict with NO macro in objc and opencv
#undef NO
#endif

#include <opencv2/opencv.hpp>

#include "control/window.h"

namespace Baa {

class IPhoneMirrorWindow final : public Window {
    CGWindowID windowID;

public:
    IPhoneMirrorWindow();
    ~IPhoneMirrorWindow() final = default;
    void mouseup(Point point) final;
    void mousedown(Point point) final;
    void getImg(cv::Mat &img) final;
};

}

#endif  // BAASSISTANT_IPHONE_MIRROR_H
