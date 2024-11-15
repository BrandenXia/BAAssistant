#include "control/iphone_mirror.h"

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

#include <stdexcept>
#include <string_view>

#include "log.h"

#define ERROR(msg)                     \
    {                                  \
        LOG_ERROR(msg);                \
        throw std::runtime_error(msg); \
    }

#define CALC_POINT(point, bounds) \
    CGPointMake(bounds.origin.x + point.x, bounds.origin.y + point.y)
#define CALC_POINT_WIN_ID(point, windowID) \
    CALC_POINT(point, getBounds(windowID))
#define CREATE_MOUSE_EVENT(kCGEvent, dst) \
    CGEventCreateMouseEvent(nullptr, kCGEvent, dst, kCGMouseButtonLeft)
#define EXEC_EVENT(kCGEvent)                                  \
    {                                                         \
        CGPoint dst = CALC_POINT_WIN_ID(point, windowID);     \
        CGEventRef event = CREATE_MOUSE_EVENT(kCGEvent, dst); \
        CGEventPost(kCGHIDEventTap, event);                   \
        CFRelease(event);                                     \
    }                                                         \
    while (0)

CGWindowID getWindowID(std::string_view appName);

NSDictionary *getWindowInfo(CGWindowID windowID);

CGSize getScreenSize(CGWindowID windowID);

CGRect getBounds(CGWindowID windowID);

namespace Baa {

IPhoneMirrorWindow::IPhoneMirrorWindow() : Window() {
    windowID = getWindowID("iPhone Mirroring");

    CGSize screenSize = getScreenSize(windowID);
    width = screenSize.width, height = screenSize.height;

    LOG_INFO("Initialized IPhoneMirrorWindow");
}

void IPhoneMirrorWindow::mousedown(Point point) {
    Window::mousedown(point);

    @autoreleasepool
    EXEC_EVENT(kCGEventLeftMouseDown);
}

void IPhoneMirrorWindow::mouseup(Point point) {
    Window::mouseup(point);

    @autoreleasepool
    EXEC_EVENT(kCGEventLeftMouseUp);
}

}

CGWindowID getWindowID(std::string_view appName) {
    LOG_INFO("Getting window ID for {}", appName);

    CGWindowID windowID = 0;

    @autoreleasepool {
        CFArrayRef windows = CGWindowListCopyWindowInfo(
            kCGWindowListOptionOnScreenOnly, kCGNullWindowID);

        for (NSDictionary *window in (__bridge NSArray *)windows) {
            NSString *windowAppName = window[(NSString *)kCGWindowOwnerName];

            if ([windowAppName
                    isEqualToString:[NSString
                                        stringWithUTF8String:appName.data()]]) {
                windowID =
                    [window[(NSString *)kCGWindowNumber] unsignedIntValue];
                break;
            }
        }
        CFRelease(windows);
    }

    if (windowID == 0) ERROR("Failed to get window ID for iPhone Mirroring");
    LOG_DEBUG("Window ID: {}", windowID);

    return windowID;
}

NSDictionary *getWindowInfo(CGWindowID windowID) {
    NSDictionary *info;

    CFArrayRef windows = CGWindowListCopyWindowInfo(
        kCGWindowListOptionIncludingWindow, windowID);
    if (windows == nullptr || CFArrayGetCount(windows) == 0)
        ERROR("Failed to get window info for iPhone Mirroring");

    info = (__bridge NSDictionary *)CFArrayGetValueAtIndex(windows, 0);

    return info;
}

CGSize getScreenSize(CGWindowID windowID) {
    CGRect bounds;

    @autoreleasepool {
        auto *info = getWindowInfo(windowID);

        CGRectMakeWithDictionaryRepresentation(
            (__bridge CFDictionaryRef)info[(NSString *)kCGWindowBounds],
            &bounds);
    }

    if (CGRectIsEmpty(bounds))
        ERROR("Failed to get screen size for iPhone Mirroring");
    LOG_DEBUG("Screen size: {}x{}", bounds.size.width, bounds.size.height);

    return bounds.size;
}

CGRect getBounds(CGWindowID windowID) {
    CGRect bounds;

    auto *info = getWindowInfo(windowID);

    CGRectMakeWithDictionaryRepresentation(
        (__bridge CFDictionaryRef)info[(NSString *)kCGWindowBounds], &bounds);

    return bounds;
}
