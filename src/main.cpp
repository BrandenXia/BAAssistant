#include "control/iphone_mirror.h"
#include "game/blue_archive.h"
#include "log.h"
#include "recognizer.h"
#include "recognizer/blue_archive.h"

int main(int argc, const char *argv[]) {
    using namespace Baa;

    initLog();

    Window *window = new IPhoneMirrorWindow();
    Frame frame = window->getFrame();

    std::cout << (int)Recognizer::recognize<Games::BlueArchive::Location>(frame)
              << std::endl;
}
