#include "utils/words.h"

#include <algorithm>
#include <locale>
#include <ranges>
#include <rapidfuzz/fuzz.hpp>

namespace views = std::views;
namespace ranges = std::ranges;

namespace Baa::Utils {

bool match_word(std::string_view text, std::string_view word) {
    if (text.empty() || word.empty()) return false;

    auto text_lower = text | views::transform(::tolower);
    auto word_lower = word | views::transform(::tolower);

    return rapidfuzz::fuzz::partial_ratio(text_lower, word_lower) > 90;
}

bool match_words(std::string_view text,
                 const std::vector<std::string_view>& words) {
    return ranges::any_of(
        words, [text](const auto& word) { return match_word(text, word); });
}

}
