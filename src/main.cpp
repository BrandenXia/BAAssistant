#include "control/iphone_mirror.h"
#include "log.h"

int main(int argc, const char *argv[]) {
    using namespace Baa;

    initLog();

    cv::Mat img;

    Window *window = new IPhoneMirrorWindow();
    window->getImg(img);

    cv::imshow("Image", img);
    cv::waitKey(0);
}
