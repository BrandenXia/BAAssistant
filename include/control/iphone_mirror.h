#ifndef BAASSISTANT_IPHONE_MIRROR_H
#define BAASSISTANT_IPHONE_MIRROR_H

#include "control/window.h"

#import <CoreGraphics/CoreGraphics.h>

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
