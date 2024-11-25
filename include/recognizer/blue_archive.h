#ifndef BAASSISTANT_RECOGNIZER_BLUE_ARCHIVE_H
#define BAASSISTANT_RECOGNIZER_BLUE_ARCHIVE_H

#include "game/blue_archive.h"
#include "recognizer.h"

namespace Baa::Recognizer {

template<>
struct Recognizer<Games::BlueArchive::Location> {
    static std::vector<Step<Games::BlueArchive::Location>> const &steps();
};

}

#endif  // BAASSISTANT_RECOGNIZER_BLUE_ARCHIVE_H
