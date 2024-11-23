#ifndef BAASSISTANT_RECOGNIZER_H
#define BAASSISTANT_RECOGNIZER_H

#include <filesystem>
#include <opencv4/opencv2/opencv.hpp>
#include <type_traits>
#include <variant>

#include "frame.h"

template<typename T>
concept EnumClass = std::is_enum_v<T> && !std::is_convertible_v<T, int>;

namespace Baa::Recognizer {

namespace Methods {

struct TemplateMatching {
    const cv::Mat templateImage;

    explicit TemplateMatching(const cv::Mat &img);
    explicit TemplateMatching(cv::Mat &&img);

    template<typename... Args>
    explicit TemplateMatching(Args &&...args)
        : templateImage(cv::imread(std::forward<Args>(args)...)) {}
};

using Types = std::variant<TemplateMatching>;

struct Visitor {
    const Frame &frame;
    explicit Visitor(const Frame &frame);

    template<typename T>
    bool operator()(const T &) {
        return false;
    }
};

template<>
bool Visitor::operator()(const TemplateMatching &method);

}

template<EnumClass T>
struct Step {
    using MethodFunc = std::function<bool(const Frame &)>;
    using Method = std::variant<Methods::Types, MethodFunc>;

    const T condition;
    const Method method;

    bool operator()(const Frame &frame) const {
        if (std::holds_alternative<Methods::Types>(method))
            return std::visit(Methods::Visitor(frame), method);
        else
            return std::get<MethodFunc>(method)(frame);
    }
};

/* Example of specialization:
 *
 * template<>
 * struct Recognizer<SomeEnum> {
 *     // implement steps here
 *     static const std::list<Step<SomeEnum>> steps;
 * };
 * const std::list<Step<SomeEnum>> Recognizer<SomeEnum>::steps = { ... };
 */
template<EnumClass T>
struct Recognizer;  // forward declaration

template<EnumClass T>
T recognize(Frame &frame) {
    return std::ranges::find_if(
               Recognizer<T>::steps,
               [frame](const auto &step) { return step(frame); })
        ->condition;
}

}

#endif  // BAASSISTANT_RECOGNIZER_H
