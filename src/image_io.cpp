#include "image_io.h"
#include <iostream>

cv::Mat readImage(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "读取失败: " << imagePath << std::endl;
    }
    return image;
}

void showImage(const cv::Mat& image, const std::string& windowName) {
    if (image.empty()) return;
    cv::imshow(windowName, image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

bool saveImage(const cv::Mat& image, const std::string& savePath) {
    if (image.empty()) return false;
    bool success = cv::imwrite(savePath, image);
    if (success) {
        std::cout << "保存成功: " << savePath << std::endl;
    } else {
        std::cerr << "保存失败: " << savePath << std::endl;
    }
    return success;
}
