#ifndef BAASSISTANT_RECOGNIZER_BLUE_ARCHIVE_H
#define BAASSISTANT_RECOGNIZER_BLUE_ARCHIVE_H

#include "recognizer.h"
#include "game/blue_archive.h"

namespace Baa::Recognizer {

template<>
struct Recognizer<Games::BlueArchive::Location> {
    static const std::list<Step<Games::BlueArchive::Location>> steps;
};

}

#endif  // BAASSISTANT_RECOGNIZER_BLUE_ARCHIVE_H
