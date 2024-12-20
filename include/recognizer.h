#ifndef BAASSISTANT_RECOGNIZER_H
#define BAASSISTANT_RECOGNIZER_H

#include <type_traits>
#include <variant>

#include "frame.h"
#include "recognizer/methods.h"

template<typename T>
concept EnumClass = std::is_enum_v<T> && !std::is_convertible_v<T, int>;

namespace Baa::Recognizer {

template<EnumClass T>
struct Step {
    const T condition;
    const Methods::Base method;
    const bool multiple = false;

    Methods::MatchFuncReturn operator()(const Frame &frame) const {
        return method(frame, multiple);
    }
};

/* Example of specialization:
 *
 * template<>
 * struct Recognizer<SomeEnum> {
 *     std::vector<Step<SomeEnum>> const& Recognizer<SomeEnum>::steps()
 * };
 *
 * // since order of global variable initialization is not guaranteed, use a
 * // function instead
 * std::vector<Step<BA::Location>> const& Recognizer<BA::Location>::steps() {
 *     static const std::vector<Step<BA::Location>> steps = { ... };
 *     return steps;
 * }
 */
template<EnumClass T>
struct Recognizer;  // forward declaration

template<typename T>
concept RecognizerEnum = EnumClass<T> && requires {
    {
        Baa::Recognizer::Recognizer<T>::steps()
    } -> std::same_as<std::vector<Step<T>> const &>;
};

template<RecognizerEnum T>
T recognize(Frame &frame) {
    auto steps = Recognizer<T>::steps();
    auto it = std::ranges::find_if_not(
        steps, [&](const auto &step) { return step(frame).empty(); });
    return it != steps.end() ? it->condition : steps.back().condition;
}

}

#endif  // BAASSISTANT_RECOGNIZER_H
