#include "object_detector.h"

std::vector<std::string> ObjectDetector::output_layer_names_;
std::vector<std::string> ObjectDetector::classes_;

ObjectDetector::ObjectDetector(std::string &model_config, std::string &model_weights, std::string &classes_file, float &conf_threshold, float &nms_threshold) {
    model_config_ = model_config;
    model_weights_ = model_weights;
    classes_file_ = classes_file;
    conf_threshold = conf_threshold; 
    nms_threshold = nms_threshold;
    net_ = cv::dnn::readNetFromDarknet(model_config_, model_weights_);
    net_.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net_.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    GetOutputLayerNames();
    ReadClassesFromFile();
}

ObjectDetector::ObjectDetector(const ObjectDetector &other) {
    model_config_ = other.model_config_;
    model_weights_ = other.model_weights_;
    classes_file_ = other.classes_file_;
    net_ = other.net_;
}

ObjectDetector &ObjectDetector::operator=(const ObjectDetector &other) {
    if (this == &other){
        return *this;
    }
    model_config_ = other.model_config_;
    model_weights_ = other.model_weights_;
    classes_file_ = other.classes_file_;
    net_ = other.net_;

    return *this;
}

ObjectDetector::ObjectDetector(ObjectDetector &&other) {
    model_config_ = std::move(other.model_config_);
    model_weights_ = std::move(other.model_weights_);
    classes_file_ = std::move(other.classes_file_);
    net_ = std::move(other.net_);
}

ObjectDetector &ObjectDetector::operator=(ObjectDetector &&other) {
    if (this == &other) {
        return *this;
    }
    model_config_ = std::move(other.model_config_);
    model_weights_ = std::move(other.model_weights_);
    classes_file_ = std::move(other.classes_file_);
    net_ = std::move(other.net_);

    return *this;
}

cv::Mat ObjectDetector::DetectObjects(cv::Mat &frame) {
    cv::Mat blob;
    Get4DBlob(frame, blob);
    net_.setInput(blob);
    std::vector<cv::Mat> outs;
    net_.forward(outs, output_layer_names_);
    PostProcess(frame, outs, conf_threshold);
    cv::Mat detected_frame;
    frame.convertTo(detected_frame, CV_8U);
    return std::move(detected_frame);
}

void ObjectDetector::Get4DBlob(cv::Mat &frame, cv::Mat &blob) {
    cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(inpWidth, inpHeight), cv::Scalar(0, 0, 0), true, false);
}

// Remove bbox with low confidence using nms
void ObjectDetector::PostProcess(cv::Mat &frame, const std::vector<cv::Mat> &outs, float &conf_threshold) {
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    for (size_t i = 0; i < outs.size(); ++i) {   
            // Network produces output blob with a shape NxC where N is a number of
            // detected objects and C is a number of classes + 4 where the first 4
            // numbers are [center_x, center_y, width, height]
        float *data = (float *)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            double confidence;

            // Get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > conf_threshold) {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    // Non-Max Supression
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, conf_threshold, nms_threshold, indices);
    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        DrawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, frame);
    }
}

void ObjectDetector::DrawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat &frame) {
    //Draw a rectangle displaying the bounding box
    cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(255, 178, 50), 3);

    //Get the label for the class name and its confidence
    std::string label = cv::format("%.2f", conf);
    if (!classes_.empty())
    {
        CV_Assert(classId < (int)classes_.size());
        label = classes_[classId] + ":" + label;
    }

    //Display the label at the top of the bounding box
    int baseLine;
    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = cv::max(top, labelSize.height);
    cv::rectangle(frame, cv::Point(left, top - round(1.5 * labelSize.height)), cv::Point(left + round(1.5 * labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
    cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0), 1);
}

void ObjectDetector::GetOutputLayerNames() {
    if (output_layer_names_.empty()) {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> out_layers = net_.getUnconnectedOutLayers();
        //get the names of all the layers in the network
        std::vector<std::string> layer_names = net_.getLayerNames();
        output_layer_names_.resize(out_layers.size());
        for (std::size_t i = 0; i < out_layers.size(); i++) {
            output_layer_names_.at(i) = layer_names[out_layers[i] - 1];
        }
    }
}
    // Open and read class file
void ObjectDetector::ReadClassesFromFile() {
    std::ifstream ifs(classes_file_.c_str());
    if(!ifs.is_open())
        CV_Error(cv::Error::StsError, "Class File (" + classes_file_ + ") not found.");
    std::string line;
    while(std::getline(ifs, line)) {
        classes_.push_back(line);
    }
}