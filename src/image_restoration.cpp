#include "image_restoration.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<int> parsePixelData(const std::string& filename) {
    std::vector<int> pixelValues;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return pixelValues;
    }
    
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::stringstream ss(line);
        std::string token;
        
        while (std::getline(ss, token, ',')) {
            if (!token.empty()) {
                try {
                    pixelValues.push_back(std::stoi(token));
                } catch (...) {
                }
            }
        }
    }
    
    return pixelValues;
}

cv::Mat ImageRestorer::restoreImageFromText(const std::string& filename, 
                                           int width, int height, 
                                           int channels) {
    std::vector<int> pixelData = parsePixelData(filename);
    
    if (pixelData.empty()) {
        std::cerr << "没有读取到像素数据: " << filename << std::endl;
        return cv::Mat();
    }
    
    int expectedPixels = width * height * channels;
    if (pixelData.size() != expectedPixels) {
        std::cerr << "像素数量不匹配: 期望" << expectedPixels 
                  << ", 实际" << pixelData.size() << std::endl;
        return cv::Mat();
    }
    
    // 检查是否为二值图像（0/1）
    int min_val = *std::min_element(pixelData.begin(), pixelData.end());
    int max_val = *std::max_element(pixelData.begin(), pixelData.end());
    
    if (min_val == 0 && max_val == 1) {
        // 将1映射为255
        for (size_t i = 0; i < pixelData.size(); i++) {
            if (pixelData[i] == 1) {
                pixelData[i] = 255;
            }
        }
    }
    
    cv::Mat image;
    if (channels == 1) {
        image = cv::Mat(height, width, CV_8UC1);
    } else {
        image = cv::Mat(height, width, CV_8UC3);
    }
    
    int index = 0;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (channels == 1) {
                image.at<uchar>(row, col) = static_cast<uchar>(pixelData[index++]);
            } else {
                cv::Vec3b pixel;
                pixel[0] = static_cast<uchar>(pixelData[index++]); // B
                pixel[1] = static_cast<uchar>(pixelData[index++]); // G  
                pixel[2] = static_cast<uchar>(pixelData[index++]); // R
                image.at<cv::Vec3b>(row, col) = pixel;
            }
        }
    }
    
    return image;
}

bool ImageRestorer::saveRestoredImage(const cv::Mat& image, 
                                    const std::string& outputPath) {
    bool success = cv::imwrite(outputPath, image);
    if (!success) {
        std::cerr << "保存失败: " << outputPath << std::endl;
    }
    
    return success;
}
