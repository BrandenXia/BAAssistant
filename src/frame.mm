#include "frame.h"

#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs/macosx.h>

namespace Baa {

Frame::Frame(const cv::Mat &raw, const Timestamp &timestamp)
    : raw(std::make_shared<cv::Mat>(raw)), timestamp(timestamp) {}

Frame::Frame(const cv::Mat &mat)
    : Frame(mat, std::chrono::steady_clock::now()) {}

Frame::Frame(const CGImageRef &cgImage)
    : timestamp(std::chrono::steady_clock::now()) {
    cv::Mat img;
    CGImageToMat(cgImage, img);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    raw = std::make_shared<cv::Mat>(img);
}

}