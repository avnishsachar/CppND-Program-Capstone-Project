#include "input.h"

Input::Input(std::string &input_path) {
    end_of_file_ = false;
    std::ifstream image_stream(input_path);
    if (image_stream) {
        cap_.open(input_path);
    }
    else {
        throw std::runtime_error("[ERROR:] Cannot open input file\n");
    }
}

bool Input::EndOfFile() {
    return end_of_file_;
}

Input::~Input() {
    cap_.release();
}

bool Input::GetImageFrame(cv::Mat &frame) {
    if (!Input::EndOfFile()) {
        cap_ >> frame;
    }
    end_of_file_ = true;
    return !Input::EndOfFile();
}
