#include "output.h"

Output::Output(std::string &output_path) {
    output_path_ = output_path;
}

void Output::WriteFrame(cv::Mat &frame) {
    cv::imwrite(output_path_, frame);
}