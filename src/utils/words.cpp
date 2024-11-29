#include "utils/words.h"

#include <algorithm>

namespace Baa::Utils {

bool match_words(const char *text, std::vector<std::string_view> words) {
    const auto input = std::string_view{text};

    return std::ranges::any_of(
        words, [&input](const auto &word) { return input.contains(word); });
}

}
