#include "recognizer.h"

namespace Baa::Recognizer::Methods {

TemplateMatching::TemplateMatching(const cv::Mat &img) : templateImage(img) {}

TemplateMatching::TemplateMatching(cv::Mat &&img)
    : templateImage(std::move(img)) {}

Visitor::Visitor(const Frame &frame) : frame(frame) {}

template<>
bool Visitor::operator()(const TemplateMatching &method) {
    cv::Mat img_gray, result;

    cv::cvtColor(*frame.raw, img_gray, cv::COLOR_BGR2GRAY);
    cv::matchTemplate(img_gray, method.templateImage, result,
                      cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    return maxVal > 0.8;
}

}
