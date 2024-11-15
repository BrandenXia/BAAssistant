#include "control/iphone_mirror.h"
#include "log.h"

int main(int argc, const char *argv[]) {
    using namespace Baa;

    initLog();

    Window *window = new IPhoneMirrorWindow();

    window->click(70, 460);
}
