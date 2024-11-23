#include "control/iphone_mirror.h"
#include "log.h"
#include "recognizer.h"

int main(int argc, const char *argv[]) {
    using namespace Baa;

    initLog();

    Window *window = new IPhoneMirrorWindow();
    Frame frame = window->getFrame();
}
