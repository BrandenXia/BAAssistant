#include "frame.h"

#include <opencv4/opencv2/imgcodecs/macosx.h>

namespace Baa {

Frame::Frame(const RawImage &raw, const Timestamp &timestamp)
    : raw(std::make_shared<RawImage>(raw)), timestamp(timestamp) {}

Frame::Frame(const RawImage &mat)
    : Frame(mat, std::chrono::steady_clock::now()) {}

Frame::Frame(const CGImageRef &cgImage)
    : timestamp(std::chrono::steady_clock::now()) {
    RawImage img;
    CGImageToMat(cgImage, img);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    raw = std::make_shared<RawImage>(img);
}

}