#ifndef BAASSISTANT_FRAME_H
#define BAASSISTANT_FRAME_H

#import <CoreGraphics/CoreGraphics.h>
#ifdef NO  // workaround for conflict with NO macro in objc and opencv
#undef NO
#endif

#include <memory>
#include <opencv4/opencv2/core/mat.hpp>

namespace Baa {

class Frame {
    using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

public:
    std::shared_ptr<cv::Mat> raw;
    const Timestamp timestamp;

    Frame(const cv::Mat &raw, const Timestamp &timestamp);
    explicit Frame(const cv::Mat &raw);
    explicit Frame(const CGImageRef &raw);
};

}

#endif  // BAASSISTANT_FRAME_H
