#ifndef BAASSISTANT_IPHONE_MIRROR_H
#define BAASSISTANT_IPHONE_MIRROR_H

#import <CoreGraphics/CoreGraphics.h>

#include "control/window.h"

namespace Baa {

class IPhoneMirrorWindow final : public Window {
    CGWindowID windowID;

public:
    IPhoneMirrorWindow();
    void mousedown(Point point) final;
    void mouseup(Point point) final;
    ~IPhoneMirrorWindow() final = default;
};

}

#endif  // BAASSISTANT_IPHONE_MIRROR_H
