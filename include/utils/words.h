#ifndef BAASSISTANT_UTILS_WORDS_H
#define BAASSISTANT_UTILS_WORDS_H

#include <string_view>
#include <vector>

namespace Baa::Utils {

bool match_words(const char *text, std::vector<std::string_view> words);

}

#endif  // BAASSISTANT_UTILS_WORDS_H
