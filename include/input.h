#pragma once

#include <fstream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//Base class to get image input.
class Input
{
public:
    explicit Input(std::string &input_path); //parsing path for input image file
    bool EndOfFile(); //parse end of image file
    bool GetImageFrame(cv::Mat &frame); //frame of input image
    ~Input();

protected:
    bool end_of_file_;  //end of image file
    cv::VideoCapture cap_; //get image through cv
};
