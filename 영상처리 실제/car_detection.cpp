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


    // ���� ���� ���� (�� �κ��� ������ �ʿ��մϴ�)
    Scalar lowerYellow = Scalar(20, 100, 100), upperYellow = Scalar(30, 255, 255);
    Scalar lowerWhite = Scalar(0, 0, 200), upperWhite = Scalar(180, 25, 255);
    Scalar lowerBlue = Scalar(100, 150, 0), upperBlue = Scalar(140, 255, 255);
    Scalar lowerGreen = Scalar(40, 50, 50), upperGreen = Scalar(80, 255, 255);
    Scalar lowerBlack = Scalar(0, 0, 0), upperBlack = Scalar(180, 255, 30);


    // ���� ���� ����ũ ����
    Mat yellowMask = createColorMask(image, lowerYellow, upperYellow);
    Mat whiteMask = createColorMask(image, lowerWhite, upperWhite);
    Mat blueMask = createColorMask(image, lowerBlue, upperBlue);
    Mat greenMask = createColorMask(image, lowerGreen, upperGreen);
    Mat blackMask = createColorMask(image, lowerBlack, upperBlack);

    // �� ����ũ�� ���� ���� ����
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

    // ���յ� ���� �̹������� ������ ã��
    vector<vector<Point>> contours;
    findContours(combinedEdges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // ����� ������ �ؽ�Ʈ ���� ��� ����
    string outputPath = imagePath.substr(0, imagePath.find_last_of('.')) + ".txt";
    ofstream outputFile(outputPath);

    // �� ����� ���� �ٿ�� �ڽ� �� �󺧸�
    Mat labeledImage = image.clone();
    int index = 1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > 100) {
            Rect boundingBox = boundingRect(contours[i]);
            rectangle(labeledImage, boundingBox, Scalar(0, 255, 0), 2);

            // �ٿ�� �ڽ� ������ �ؽ�Ʈ ���Ͽ� ���
            outputFile << index << "\t" << boundingBox.x << "\t" << boundingBox.y << "\t"
                << boundingBox.width << "\t" << boundingBox.height << endl;
            index = index + 1;
        }
    }

    // ���� �ݱ�
    outputFile.close();

    // �󺧸��� �̹��� ǥ��
    imshow("Labeled Bounding Boxes", labeledImage);
    waitKey(0);
    return 0;
    }