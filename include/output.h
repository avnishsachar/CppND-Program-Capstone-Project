#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

//Class to write output to an image file
class Output {
public:
    Output(){}; //constructor
    Output(std::string &output_path); //passing path for output file
    void WriteFrame(cv::Mat &frame); //writing the frame to the output file
    ~Output(){}; //destructor

protected:
    std::string output_path_{""}; //path for output file
};
