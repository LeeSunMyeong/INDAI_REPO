#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

Mat createColorMask(const Mat& image, const Scalar& lowerBound, const Scalar& upperBound) {
    Mat mask;
    inRange(image, lowerBound, upperBound, mask);
    return mask;
}

Mat detectEdges(const Mat& mask) {
    Mat edges;
    Canny(mask, edges, 50, 150);
    return edges;
}

int main() {

    string imagePath;
    cout << "Enter the full path of the image: ";
    cin >> imagePath;

    Mat image = imread(imagePath);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return 0;
    }


    // 색상 범위 정의 (이 부분은 조정이 필요합니다)
    Scalar lowerYellow = Scalar(20, 100, 100), upperYellow = Scalar(30, 255, 255);
    Scalar lowerWhite = Scalar(0, 0, 200), upperWhite = Scalar(180, 25, 255);
    Scalar lowerBlue = Scalar(100, 150, 0), upperBlue = Scalar(140, 255, 255);
    Scalar lowerGreen = Scalar(40, 50, 50), upperGreen = Scalar(80, 255, 255);
    Scalar lowerBlack = Scalar(0, 0, 0), upperBlack = Scalar(180, 255, 30);


    // 색상에 따른 마스크 생성
    Mat yellowMask = createColorMask(image, lowerYellow, upperYellow);
    Mat whiteMask = createColorMask(image, lowerWhite, upperWhite);
    Mat blueMask = createColorMask(image, lowerBlue, upperBlue);
    Mat greenMask = createColorMask(image, lowerGreen, upperGreen);
    Mat blackMask = createColorMask(image, lowerBlack, upperBlack);

    // 각 마스크에 대한 엣지 검출
    Mat yellowEdges = detectEdges(yellowMask);
    Mat whiteEdges = detectEdges(whiteMask);
    Mat blueEdges = detectEdges(blueMask);
    Mat greenEdges = detectEdges(greenMask);
    Mat blackEdges = detectEdges(blackMask);

    Mat combinedEdges;
    bitwise_or(yellowEdges, whiteEdges, combinedEdges);
    bitwise_or(combinedEdges, blueEdges, combinedEdges);
    bitwise_or(combinedEdges, greenEdges, combinedEdges);
    bitwise_or(combinedEdges, blackEdges, combinedEdges);

    // 결합된 엣지 이미지에서 컨투어 찾기
    vector<vector<Point>> contours;
    findContours(combinedEdges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 결과를 저장할 텍스트 파일 경로 생성
    string outputPath = imagePath.substr(0, imagePath.find_last_of('.')) + ".txt";
    ofstream outputFile(outputPath);

    // 각 컨투어에 대한 바운딩 박스 및 라벨링
    Mat labeledImage = image.clone();
    int index = 1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > 100) {
            Rect boundingBox = boundingRect(contours[i]);
            rectangle(labeledImage, boundingBox, Scalar(0, 255, 0), 2);

            // 바운딩 박스 정보를 텍스트 파일에 출력
            outputFile << index << "\t" << boundingBox.x << "\t" << boundingBox.y << "\t"
                << boundingBox.width << "\t" << boundingBox.height << endl;
            index = index + 1;
        }
    }

    // 파일 닫기
    outputFile.close();

    // 라벨링된 이미지 표시
    imshow("Labeled Bounding Boxes", labeledImage);
    waitKey(0);
    return 0;
    }