#ifndef BAASSISTANT_UTILS_OPENCV_H
#define BAASSISTANT_UTILS_OPENCV_H

#include <opencv4/opencv2/core.hpp>
#include <vector>

namespace Baa::Utils::OpenCV {

void binarize(cv::Mat &src, cv::Mat &dst);

std::vector<cv::Rect> mergeRects(std::vector<cv::Rect> boxes, int merge_margin);

std::vector<cv::Rect> contours2rects(
    const std::vector<std::vector<cv::Point>> &contours, int width, int height);

}

#endif  // BAASSISTANT_UTILS_OPENCV_H
