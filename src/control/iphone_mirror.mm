#include "control/iphone_mirror.h"

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#include <sys/types.h>

#include <stdexcept>
#include <string_view>

#import "spdlog/spdlog.h"

#define ERROR(msg)                     \
    {                                  \
        spdlog::error(msg);            \
        throw std::runtime_error(msg); \
    }

CGWindowID getWindowID(std::string_view appName);

NSDictionary *getWindowInfo(CGWindowID windowID);

CGSize getScreenSize(CGWindowID windowID);

namespace Baa {

IPhoneMirrorWindow::IPhoneMirrorWindow() : Window() {
    windowID = getWindowID("iPhone Mirroring");

    CGSize screenSize = getScreenSize(windowID);
    width = screenSize.width, height = screenSize.height;

    spdlog::info("Initialized IPhoneMirrorWindow");
}

void IPhoneMirrorWindow::click(double x, double y) {
    Window::click(x, y);

    @autoreleasepool {
        auto *info = getWindowInfo(windowID);
        CGRect bounds;
        CGRectMakeWithDictionaryRepresentation(
            (__bridge CFDictionaryRef)info[(NSString *)kCGWindowBounds],
            &bounds);

        CGPoint point = CGPointMake(bounds.origin.x + x,
                                    bounds.origin.y + y);

        CGEventRef down = CGEventCreateMouseEvent(
            nullptr, kCGEventLeftMouseDown, point, kCGMouseButtonLeft);
        CGEventRef up = CGEventCreateMouseEvent(
            nullptr, kCGEventLeftMouseUp, point, kCGMouseButtonLeft);

        CGEventPost(kCGHIDEventTap, down);
        CGEventPost(kCGHIDEventTap, up);

        CFRelease(down);
        CFRelease(up);
    }
}

}

CGWindowID getWindowID(std::string_view appName) {
    spdlog::info("Getting window ID for {}", appName);

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
    spdlog::debug("Window ID: {}", windowID);

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
    spdlog::debug("Screen size: {}x{}", bounds.size.width, bounds.size.height);

    return bounds.size;
}
