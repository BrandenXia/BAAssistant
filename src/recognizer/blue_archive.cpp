#include "recognizer/blue_archive.h"

#include "assets.h"
#include "recognizer/methods.h"

namespace Baa::Recognizer {

namespace BA = Games::BlueArchive;

// TODO: Implement recognizers, currently only a placeholder
std::vector<Step<BA::Location>> const& Recognizer<BA::Location>::steps() {
    static const std::vector<Step<BA::Location>> steps = {
        Step{BA::Location::Start, Methods::OCR{"TOUCH TO START"}},
        Step{BA::Location::Lobby, Methods::Empty},
    };

    return steps;
}

}
