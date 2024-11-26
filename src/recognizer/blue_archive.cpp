#include "recognizer/blue_archive.h"

#include "assets.h"
#include "recognizer/methods.h"

namespace Baa::Recognizer {

using Methods::TemplateMatching, Methods::Tesseract;
namespace BA = Games::BlueArchive;

// TODO: Implement recognizers, currently only a placeholder
std::vector<Step<BA::Location>> const& Recognizer<BA::Location>::steps() {
    static const std::vector<Step<BA::Location>> steps = {
        Step{BA::Location::Start, Tesseract{"TOUCH TO START"}},
    };

    return steps;
}

}
