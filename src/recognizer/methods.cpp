#include "recognizer/methods.h"

#include <tesseract/baseapi.h>

#include <opencv4/opencv2/imgproc.hpp>
#include <ranges>
#include <vector>

#include "assets.h"
#include "log.h"
#include "utils/opencv.h"
#include "utils/words.h"

constexpr float THRESHOLD = 0.8;

namespace Baa::Recognizer::Methods {

MatchFuncReturn TemplateMatching::operator()(const Frame &frame,
                                             bool multiple) const {
    cv::Mat grayFrame;
    cv::cvtColor(*frame.raw, grayFrame, cv::COLOR_BGR2GRAY);

    cv::Mat_<float> res;
    cv::matchTemplate(grayFrame, templateImage, res, cv::TM_CCOEFF_NORMED);

    MatchFuncReturn locations;
    if (multiple) {
        for (int i = 0; i < res.rows; ++i)
            for (int j = 0; j < res.cols; ++j)
                if (res(i, j) >= THRESHOLD) locations.emplace_back(j, i);
    } else {
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);

        if (maxVal >= THRESHOLD) locations.emplace_back(maxLoc);
    }

    return locations;
}

Tesseract::Tesseract(std::string_view t, std::string_view l)
    : words{t}, lang(l) {}

Tesseract::Tesseract(std::vector<std::string_view> t, std::string_view l)
    : words(std::move(t)), lang(l) {}

MatchFuncReturn Tesseract::operator()(const Baa::Frame &frame,
                                      bool multiple) const {
    // find text in the frame
    cv::Mat mask;
    cv::cvtColor(*frame.raw, mask, cv::COLOR_BGR2GRAY);
    cv::threshold(mask, mask, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::erode(mask, mask, element);
    cv::dilate(mask, mask, element);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_SIMPLE);

    auto img_height = frame.raw->rows;
    auto img_width = frame.raw->cols;
    auto rects = Utils::OpenCV::contours2rects(contours, img_width, img_height);

    auto *api = new tesseract::TessBaseAPI();
    if (api->Init((assets / "tessdata").c_str(), lang.data(),
                  tesseract::OEM_LSTM_ONLY))
        ERROR("Failed to initialize Tesseract");

#ifdef DEBUG
    cv::Mat dbg;
    frame.raw->copyTo(dbg);
#endif

    MatchFuncReturn locations;
    for (const auto &rect : rects) {
#ifdef DEBUG  // for debugging purposes, draw rectangles
        cv::rectangle(dbg, rect, cv::Scalar(0, 255, 0), 2);
#endif

        cv::Mat roi = (*frame.raw)(rect);
        Utils::OpenCV::binarize(roi);
        api->SetImage(roi.data, roi.cols, roi.rows, 3,
                      static_cast<int>(roi.step));
        api->Recognize(nullptr);

        const auto text = api->GetUTF8Text();
        if (Utils::match_words(text, words)) locations.emplace_back(rect.tl());
        delete[] text;
    }

    api->End();
    delete api;

    return locations;
}

}
