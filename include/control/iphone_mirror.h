#ifndef BAASSISTANT_IPHONE_MIRROR_H
#define BAASSISTANT_IPHONE_MIRROR_H

#import <CoreGraphics/CoreGraphics.h>

#include "control/window.h"

namespace Baa {

class IPhoneMirrorWindow : public Window {
    CGWindowID windowID;
public:
    IPhoneMirrorWindow();
    void click(double x, double y) final;
};

}

#endif  // BAASSISTANT_IPHONE_MIRROR_H
