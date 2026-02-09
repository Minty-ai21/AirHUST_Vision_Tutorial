#include "image_restoration.h"
#include <iostream>
#include <vector>

struct ImageInfo {
    std::string filename;
    int width, height, channels;
    std::string outputName;
};

int main() {
    
    std::vector<ImageInfo> images = {
        {"data/input/pic1.txt", 1440, 1920, 3, "data/output/restored_pic1.png"},
        {"data/input/pic2.txt", 161, 108, 1, "data/output/restored_pic2.png"},
        {"data/input/pic3.txt", 1202, 776, 1, "data/output/restored_pic3.png"}
    };
    
    for (const auto& img : images) {
        std::cout << "处理: " << img.filename << std::endl;
        
        cv::Mat restored = ImageRestorer::restoreImageFromText(
            img.filename, img.width, img.height, img.channels);
        
        if (!restored.empty()) {
            if (ImageRestorer::saveRestoredImage(restored, img.outputName)) {
                std::cout << " 成功" << std::endl;
            } else {
                std::cout << " 保存失败" << std::endl;
            }
        } else {
            std::cout << " 恢复失败" << std::endl;
        }
    }
    
    std::cout << "处理完成" << std::endl;
    
    return 0;
}
