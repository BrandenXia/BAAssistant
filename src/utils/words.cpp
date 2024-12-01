#include "utils/words.h"

#include <algorithm>
#include <cctype>
#include <ranges>
#include <rapidfuzz/fuzz.hpp>

#define FUZZ_THRESHOLD 90

namespace views = std::views;
namespace ranges = std::ranges;

namespace Baa::Utils {

std::string strip(std::string_view text) {
    auto first = std::find_if_not(text.begin(), text.end(), ::isspace);
    auto last = std::find_if_not(text.rbegin(), text.rend(), ::isspace).base();

    return {first, last};
}

bool match_word(std::string_view text, std::string_view word) {
    if (text.empty() || word.empty()) return false;

    auto text_lower = text | views::transform(::tolower);
    auto word_lower = word | views::transform(::tolower);

    return rapidfuzz::fuzz::partial_ratio(text_lower, word_lower) >=
           FUZZ_THRESHOLD;
}

bool match_words(std::string_view text,
                 const std::vector<std::string_view>& words) {
    return ranges::any_of(
        words, [text](const auto& word) { return match_word(text, word); });
}

}
