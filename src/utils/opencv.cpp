#include "utils/opencv.h"

#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/photo.hpp>
#include <ranges>

namespace views = std::views;
namespace ranges = std::ranges;

bool overlap(const cv::Rect &r1, const cv::Rect &r2);

std::vector<cv::Rect> getAllOverlaps(const std::vector<cv::Rect> &boxes,
                                     const cv::Rect &bounds, int index);

namespace Baa::Utils::OpenCV {

void binarize(cv::Mat &src, cv::Mat &dst) {
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX);
    cv::fastNlMeansDenoising(dst, dst, 3, 7, 21);
    cv::adaptiveThreshold(dst, dst, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY, 11, 2);
}

// from https://stackoverflow.com/a/66523571, translated from Python to C++
std::vector<cv::Rect> mergeRects(std::vector<cv::Rect> boxes,
                                 int merge_margin) {
    bool finished = false;

    while (!finished) {
        finished = true;

        for (int index = static_cast<int>(boxes.size()) - 1; index >= 0;
             --index) {
            cv::Rect curr = boxes[index];
            cv::Rect expanded = curr;
            expanded.x -= merge_margin;
            expanded.y -= merge_margin;
            expanded.width += 2 * merge_margin;
            expanded.height += 2 * merge_margin;

            std::vector<cv::Rect> overlaps =
                getAllOverlaps(boxes, expanded, index);

            if (!overlaps.empty()) {
                overlaps.push_back(curr);

                cv::Rect merged = overlaps[0];
                for (const auto &rect : overlaps) merged |= rect;

                for (auto it = boxes.begin(); it != boxes.end();) {
                    if (std::find(overlaps.begin(), overlaps.end(), *it) !=
                        overlaps.end()) {
                        it = boxes.erase(it);
                    } else {
                        ++it;
                    }
                }

                boxes.push_back(merged);
                finished = false;
                break;
            }
        }
    }

    return boxes;
}

std::vector<cv::Rect> contours2rects(
    const std::vector<std::vector<cv::Point>> &contours, int width,
    int height) {
    bool img_horizontal = width > height;
    auto size_filter = [&](const auto &rect) {
        // TODO: I can only think of this for now, add more rules if needed
        return rect.height < width * 0.4;
    };

    // clang-format off
    auto rects_view = contours
        | views::transform(cv::boundingRect)
        | views::filter(size_filter);
    // clang-format on
    auto rects_ = ranges::to<std::vector<cv::Rect>>(rects_view);

    int margin = 15;
    std::vector<cv::Rect> rects;
    while ((rects = mergeRects(rects_, margin)).size() <= 2 && margin > 0)
        margin -= 2;

    return rects;
}

}

bool overlap(const cv::Rect &r1, const cv::Rect &r2) {
    return (r1 & r2).area() > 0;
}

std::vector<cv::Rect> getAllOverlaps(const std::vector<cv::Rect> &boxes,
                                     const cv::Rect &bounds, int index) {
    std::vector<cv::Rect> overlaps;
    for (size_t i = 0; i < boxes.size(); ++i) {
        if (i != index && overlap(bounds, boxes[i])) {
            overlaps.push_back(boxes[i]);
        }
    }
    return overlaps;
}
