#ifndef IMAGE_RESTORATION_H
#define IMAGE_RESTORATION_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class ImageRestorer {
public:
    static cv::Mat restoreImageFromText(const std::string& filename, 
                                       int width, int height, 
                                       int channels);
    
    static bool saveRestoredImage(const cv::Mat& image, 
                                 const std::string& outputPath);
};

#endif
