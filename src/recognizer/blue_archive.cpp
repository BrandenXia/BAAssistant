#include "recognizer/blue_archive.h"

#include "assets.h"

namespace Baa::Recognizer {

using Methods::TemplateMatching;
namespace BA = Games::BlueArchive;

// TODO: Implement recognizers, currently only a placeholder
const std::list<Step<BA::Location>> Recognizer<BA::Location>::steps = {
    {BA::Location::Start, TemplateMatching{cv::Mat{}}},
};

}
