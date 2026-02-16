#include <opencv2/opencv.hpp>
#include <vector>

std::vector<cv::Point2f> srcPoints;
cv::Mat image, imageCopy;

void onMouse(int event, int x, int y, int flags, void* param) {
    if (event == cv::EVENT_LBUTTONDOWN && srcPoints.size() < 4) {
        srcPoints.push_back(cv::Point2f(x, y));
        cv::circle(imageCopy, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), 2);
        cv::imshow("选择四个点 (ESC取消)", imageCopy);
    }
}

int main() {
    image = cv::imread("data/input/chessboard.png");
    imageCopy = image.clone();
    
    cv::namedWindow("选择四个点 (ESC取消)");
    cv::setMouseCallback("选择四个点 (ESC取消)", onMouse);
    
    while (srcPoints.size() < 4) {
        cv::imshow("选择四个点 (ESC取消)", imageCopy);
        if (cv::waitKey(20) == 27) return 0;
    }
    
    // 2:1长方形目标区域
    int width = 400;  
    int height = 200;  
    
    std::vector<cv::Point2f> dstPoints = {
        cv::Point2f(0, 0),
        cv::Point2f(width-1, 0),
        cv::Point2f(0, height-1),
        cv::Point2f(width-1, height-1)
    };
    
    // 透视变换
    cv::Mat M = cv::getPerspectiveTransform(srcPoints, dstPoints);
    cv::Mat perspective;
    cv::warpPerspective(image, perspective, M, cv::Size(width, height));
    
    cv::imwrite("data/output/perspective_result.jpg", perspective);
    cv::imshow("透视变换结果 (2:1长方形)", perspective);
    cv::waitKey(0);
    
    // 逆变换
    cv::Mat inverseM = M.inv();
    cv::Mat inverse;
    cv::warpPerspective(perspective, inverse, inverseM, image.size());
    
    cv::imwrite("data/output/inverse_result.jpg", inverse);
    cv::imshow("逆变换结果", inverse);
    cv::waitKey(0);
    
    // 对比
    cv::Mat combined;
    cv::hconcat(image, inverse, combined);
    cv::imshow("对比: 原图(左) 逆变换结果(右)", combined);
    cv::waitKey(0);
    
    return 0;
}
