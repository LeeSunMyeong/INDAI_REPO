//
// Created by 이선명 on 2023/10/25.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int threshold_value = 128;
Mat src, src_gray, dst;

vector<RotatedRect> find_coins(Mat img) {
    vector<vector<Point>> contours;

    findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<RotatedRect> circles;
    for (int i = 0; i < (int) contours.size(); i++) {
        RotatedRect mr = minAreaRect(contours[i]);
        mr.angle = (mr.size.width + mr.size.height) / 4.0f;
        
        if(mr.angle > 18)
            circles.push_back(mr);
    }
    return circles;
}

int main()
{

    src = imread("/Users/smmm/Downloads/coin_final.png", IMREAD_GRAYSCALE);

    if (src.empty() || src.empty()) {
        cerr << "Image load failed!" << endl;
        return 0;
    }
    int money = 0;
    int ten = 0;
    int oneHundred = 0;
    int fiveHundred = 0;
    threshold(src, dst, 72, 255, THRESH_BINARY);
    morphologyEx(dst, dst, MORPH_OPEN, Mat(), Point(-1, -1), 1);
    imshow("원영상", src);
    imshow("이진화 영상", dst);
    vector<RotatedRect> circles = find_coins(dst);
    for (int i = 0; i < circles.size(); i++) {
        float radius = circles[i].angle;
        if (radius < 46) {
            money = money + 10;
            ten++;
        } else if (radius >= 46 && radius < 50) {
            money = money + 100;
            oneHundred++;
        }
        else if (radius > 50) {
            money = money + 500;
            fiveHundred++;
        }
        circle(src, circles[i].center, radius, Scalar(0, 0, 255), 2);
    }
    cerr << "10원 개수 : " << ten << endl;
    cerr << "100원 개수 : " << oneHundred << endl;
    cerr << "500원 개수 : " << fiveHundred << endl;
    cerr << "총 금액 : " << money << endl;
    imshow("외관선 영상", src);
    waitKey();

    return 0;
}