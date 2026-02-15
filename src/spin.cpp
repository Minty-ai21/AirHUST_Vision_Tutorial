#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
    Mat srcImg = imread("data/input/ranjinle.jpg");
    int srcW = srcImg.cols;
    int srcH = srcImg.rows;
    cout << "原始图像尺寸：宽度 = " << srcW << " 高度 = " << srcH << endl;
    cout << "色彩通道数：" << srcImg.channels() << endl;

    double angle = 30.0;
    double radian = angle * CV_PI / 180.0;

    int newW = static_cast<int>(abs(srcW * cos(radian)) + abs(srcH * sin(radian)));
    int newH = static_cast<int>(abs(srcH * cos(radian)) + abs(srcW * sin(radian)));

    Point2f srcCenter(srcW / 2.0, srcH / 2.0); // 原图中心
    Mat rotationMatrix1 = getRotationMatrix2D(srcCenter, angle, 1.0);
    // 调整偏移量，让旋转后的图像居中
    rotationMatrix1.at<double>(0, 2) += (newW - srcW) / 2.0;
    rotationMatrix1.at<double>(1, 2) += (newH - srcH) / 2.0;
    
    Mat pic1;
    warpAffine(srcImg, pic1, rotationMatrix1, Size(newW, newH), INTER_LINEAR, BORDER_CONSTANT, Scalar(255,255,255));
    cout << "pic1尺寸：宽度 = " << newW << " 高度 = " << newH << endl;
    imshow("逆时针旋转30度", pic1);
    waitKey(0);
    imwrite("data/output/pic1.jpg", pic1);

    Point2f pic1Center(newW / 2.0, newH / 2.0); // pic1的中心
    Mat rotationMatrix2 = getRotationMatrix2D(pic1Center, -angle, 1.0); 
    
    Mat pic2;
    warpAffine(pic1, pic2, rotationMatrix2, Size(newW, newH), INTER_LINEAR, BORDER_CONSTANT, Scalar(255,255,255));
    cout << "pic2尺寸：宽度 = " << newW << " 高度 = " << newH << endl;
    imshow("pic2", pic2);
    waitKey(0);
    imwrite("data/output/pic2.jpg", pic2);

    Mat srcResized;
    resize(srcImg, srcResized, Size(newW, newH)); // 原图缩放到pic2尺寸
    Mat compareImg;
    hconcat(srcResized, pic2, compareImg); // 水平拼接对比
    imshow("原图 (左，缩放后) vs pic2 (右，无裁剪)", compareImg);
    waitKey(0);

    return 0;
}
