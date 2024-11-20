#ifndef BAASSISTANT_FRAME_H
#define BAASSISTANT_FRAME_H

#import <CoreGraphics/CoreGraphics.h>
#ifdef NO  // workaround for conflict with NO macro in objc and opencv
#undef NO
#endif

#include <memory>
#include <opencv2/opencv.hpp>

namespace Baa {

class Frame {
    using RawImage = cv::Mat;
    using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

    std::shared_ptr<RawImage> raw;
    const Timestamp timestamp;

public:
    Frame(const RawImage &raw, const Timestamp &timestamp);
    explicit Frame(const RawImage &raw);
    explicit Frame(const CGImageRef &raw);
};

}

#endif  // BAASSISTANT_FRAME_H
