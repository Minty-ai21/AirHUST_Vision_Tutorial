#include <opencv2/opencv.hpp>
#include <iostream>

// 修复通道顺序函数
cv::Mat fixChannels(const cv::Mat& image) {
    cv::Mat result = image.clone();
    
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            uchar b = image.at<cv::Vec3b>(y, x)[0];
            uchar g = image.at<cv::Vec3b>(y, x)[1];
            uchar r = image.at<cv::Vec3b>(y, x)[2];
            
            if (b > r && b > g) {
                result.at<cv::Vec3b>(y, x) = cv::Vec3b(r, g, b);
            }
            else if (g > r && g > b) {
                result.at<cv::Vec3b>(y, x) = cv::Vec3b(b, r, g);
            }
        }
    }
    
    return result;
}

int main() {
    // 读取图像
    cv::Mat image = cv::imread("data/input/processed_lena.jpg");
    if (image.empty()) {
        std::cerr << "无法读取图像" << std::endl;
        return 1;
    }
    
    // 显示原图
    cv::imshow("原图", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    // 修复图像
    cv::Mat fixed = fixChannels(image);
    
    // 显示修复后的图
    cv::imshow("修复后", fixed);
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    // 保存图像
    cv::imwrite("data/output/fixed_lena.jpg", fixed);
    
    return 0;
}
