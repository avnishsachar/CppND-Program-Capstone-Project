#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "buffer.h"
#include "input.h"
#include "object_detector.h"
#include "output.h"

Buffer<cv::Mat> frame_buffer;
std::string image_out = "../output/out.jpg";
std::string config_path{"../model/yolov3-tiny.cfg"};
std::string weights_path{"../model/yolov3-tiny.weights"};
std::string classes_path{"../model/coco.names"};

int main(int argc, char **argv)
{
    // Command line options.
    const cv::String keys =
        "{help h usage ? | | Usage examples: \n\t\t./object_etector --image=../data/bird.jpg}"
        "{c conf         |   .5 | Confidence threshold. }"
        "{n nms          |   .4 | Non-max suppression threshold. }"
        "{input i        |<none>| Input image. }";
        
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Use this script to detect objects in an image file using OpenCV.");

    if (parser.has("help") || argc ==1 ) {
        parser.printMessage();
        return 0;
    }
     // Get the conf and nms thresholds if specified.
    float conf_threshold = parser.get<float>("c");
    float nms_threshold = parser.get<float>("n");

    // Check for valid input file. Open a video file or an image file or a camera stream.
    if (parser.has("input")) {
        std::string input = parser.get<std::string>("input");
        std::ifstream input_stream(input);
        if (!input_stream) {
            std::cout << "No Media Input Found \n";
            return 0;
        }
        std::unique_ptr<Input> capture = std::make_unique<Input>(input);
        cv::Mat frame;
        if (parser.has("input")) {capture->GetImageFrame(frame);}
        std::unique_ptr<ObjectDetector> detector = std::make_unique<ObjectDetector>(config_path, weights_path, classes_path, conf_threshold, nms_threshold);
        cv::Mat detected_frame = detector->DetectObjects(frame);
        std::unique_ptr<Output> output = std::make_unique<Output>(image_out);
        output->WriteFrame(detected_frame);
        static const std::string kWinName = "Deep learning object detection in OpenCV";
        namedWindow(kWinName, cv::WINDOW_NORMAL);
        imshow(kWinName, frame);
        cv::waitKey(10000);
        cv::destroyAllWindows();
    }

    else {
        std::cout << "Invalid Input Parameters\n";
    }
}