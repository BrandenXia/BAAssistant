#ifndef BAASSISTANT_UTILS_WORDS_H
#define BAASSISTANT_UTILS_WORDS_H

#include <string_view>
#include <vector>

namespace Baa::Utils {

bool match_word(std::string_view text, std::string_view word);

bool match_words(std::string_view text, const std::vector<std::string_view>& words);

}

#endif  // BAASSISTANT_UTILS_WORDS_H
