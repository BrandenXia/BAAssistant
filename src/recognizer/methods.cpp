#include "recognizer/methods.h"

#include <tesseract/baseapi.h>

#include <opencv4/opencv2/imgproc.hpp>

#include "log.h"

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

OCR::OCR(std::string_view text, std::string_view lang)
    : text(text), lang(lang) {}

MatchFuncReturn OCR::operator()(const Baa::Frame &frame, bool multiple) const {
    auto *api = new tesseract::TessBaseAPI();
    if (api->Init(nullptr, lang.data(), tesseract::OEM_LSTM_ONLY))
        ERROR("Failed to initialize Tesseract");

    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetImage(frame.raw->data, frame.raw->cols, frame.raw->rows, 3,
                  static_cast<int>(frame.raw->step));
    api->Recognize(nullptr);

    auto *ri = api->GetIterator();
    MatchFuncReturn locations;
    do {
        const auto *word = ri->GetUTF8Text(tesseract::RIL_WORD);
        if (word == nullptr) continue;

        if (std::string_view(word).contains(text)) {
            int x, y, w, h;
            ri->BoundingBox(tesseract::RIL_WORD, &x, &y, &w, &h);
            locations.emplace_back(x, y);
        }

        delete[] word;
    } while (ri->Next(tesseract::RIL_PARA));

    api->End();
    delete api;

    return locations;
}

}
