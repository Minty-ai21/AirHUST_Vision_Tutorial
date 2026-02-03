#include "image_io.h"

int main() {
    const std::string inputDir = "data/input/";
    const std::string outputDir = "data/output/";
    
    // 处理 hesiqi.png
    cv::Mat img1 = readImage(inputDir + "hesiqi.png");
    if (!img1.empty()) {
        showImage(img1, "hesiqi.png");
        saveImage(img1, outputDir + "hesiqi.png");
    }

    // 处理 ranjinle.jpg
    cv::Mat img2 = readImage(inputDir + "ranjinle.jpg");
    if (!img2.empty()) {
        showImage(img2, "ranjinle.jpg");
        saveImage(img2, outputDir + "ranjinle.jpg");
    }

    return 0;
}
