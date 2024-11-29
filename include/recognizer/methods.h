#ifndef BAASSISTANT_RECOGNIZER_METHODS_H
#define BAASSISTANT_RECOGNIZER_METHODS_H

#include <functional>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <variant>

#include "frame.h"

template<typename... Args>
concept CanCallImread = requires(Args &&...args) {
    { cv::imread(std::forward<Args>(args)...) } -> std::same_as<cv::Mat>;
};

namespace Baa::Recognizer::Methods {

using MatchFuncReturn = std::vector<cv::Point>;

using Base = std::function<MatchFuncReturn(const Frame &, bool)>;

// templateImage should be in grayscale
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

    MatchFuncReturn operator()(const Frame &frame, bool multiple) const;
};

struct Tesseract {
    const std::vector<std::string_view> words;
    const std::string lang;

    explicit Tesseract(std::string_view t, std::string_view l = "eng");
    explicit Tesseract(std::vector<std::string_view> t, std::string_view l = "eng");
    MatchFuncReturn operator()(const Frame &frame, bool multiple) const;
};

}

#endif  // BAASSISTANT_RECOGNIZER_METHODS_H
