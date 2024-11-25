#ifndef BAASSISTANT_RECOGNIZER_METHODS_H
#define BAASSISTANT_RECOGNIZER_METHODS_H

#include <boost/function.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <variant>

#include "frame.h"

template<typename... Args>
concept CanCallImread = requires(Args &&...args) {
    { cv::imread(std::forward<Args>(args)...) } -> std::same_as<cv::Mat>;
};

namespace Baa::Recognizer::Methods {

using MatchFuncReturn = std::vector<cv::Point>;

using Base = boost::function<MatchFuncReturn(const Frame &, bool)>;

struct TemplateMatching {
    const cv::Mat templateImage;

    template<typename... Args>
        requires std::is_constructible_v<cv::Mat, Args...>
    explicit TemplateMatching(Args &&...args)
        : templateImage(std::forward<Args>(args)...) {}

    template<typename... Args>
        requires CanCallImread<Args...>
    explicit TemplateMatching(Args &&...args)
        : templateImage(cv::imread(std::forward<Args>(args)...)) {}

    TemplateMatching(const TemplateMatching &) = default;
    TemplateMatching(TemplateMatching &&) noexcept = default;

    MatchFuncReturn operator()(const Frame &frame, bool multiple) const;
};

}

#endif  // BAASSISTANT_RECOGNIZER_METHODS_H
