#ifndef BAASSISTANT_IPHONE_MIRROR_H
#define BAASSISTANT_IPHONE_MIRROR_H

#import <CoreGraphics/CoreGraphics.h>
#ifdef NO  // workaround for conflict with NO macro in objc and opencv
#undef NO
#endif

#include "control/window.h"
#include "frame.h"

namespace Baa {

class IPhoneMirrorWindow final : public Window {
    CGWindowID windowID;

public:
    IPhoneMirrorWindow();
    ~IPhoneMirrorWindow() final = default;
    void mouseup(Point point) final;
    void mousedown(Point point) final;
    Frame getFrame() final;
};

}

#endif  // BAASSISTANT_IPHONE_MIRROR_H
