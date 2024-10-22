//
// Created by 이선명 on 2023/10/25.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat image;
    Mat kernel(5, 25, CV_8UC1, Scalar(1));

    // 원 영상
    image = imread("/Users/smmm/Downloads/KakaoTalk_20231025_184952102.png", 1);

    // 동전 내부는 흰색, 배경읜 검정색의 이진화 영상
    int threshold_value = 70;
    Mat binaryImg, gray;
    cvtColor(image, gray, COLOR_RGB2GRAY);
    blur(gray, gray, Size(5, 5));
    threshold(gray, binaryImg, threshold_value, 255, THRESH_BINARY);
    // 동전의 에지만 흰색으로 출력
    Mat result;
    Sobel(binaryImg, result, CV_8U, 1, 1, 3);
    morphologyEx(result, result, MORPH_CLOSE, kernel);


    imshow("원 영상 (컬러 영상) 출력", image);
    imshow("이진화 영상 출력", binaryImg);
    imshow("에지만 흰색인 영상 출력", result);
    waitKey(0);
    return 0;
}
