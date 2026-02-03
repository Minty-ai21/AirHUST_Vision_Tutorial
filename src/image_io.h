#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <opencv2/opencv.hpp>
#include <string>

// 读取图像
cv::Mat readImage(const std::string& imagePath);

// 展示图像
void showImage(const cv::Mat& image, const std::string& windowName = "Display Image");

// 保存图像
bool saveImage(const cv::Mat& image, const std::string& savePath);

#endif // IMAGE_IO_H
