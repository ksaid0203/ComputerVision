#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

// 255 흰색, 나머지는 검은색

// 가로로 projection
void getHorizontal(Mat & image, Mat & vertical) {
	for (int x = 0; x < image.rows; x += 1) {
		int cnt = 0;
		for (int y = 0; y < image.cols; y += 1) {
			Scalar tmp = image.at<uchar>(x, y);
			if (tmp.val[0] != 0) {
				cnt += 1;
			}
		}

		for (int y = 0; y < image.cols; y += 1) {
			if (cnt > 0) vertical.at<uchar>(x, y) = 0;
			else vertical.at<uchar>(x, y) = 255;
			cnt -= 1;
		}
	}
}
// rows = 높이
// cols = 너비
// 세로로 projection
void getVertical(Mat & image, Mat & vertical) {
	for (int y = 0; y < image.cols; y += 1) {
		int cnt = 0;
		for (int x = 0; x < image.rows; x += 1) {
			Scalar tmp = image.at<uchar>(x, y);
			if (tmp.val[0] != 0) {
				cnt += 1;
			}
		}

		for (int x = 0; x < image.rows; x += 1) {
			if (cnt > 0) vertical.at<uchar>(x, y) = 0;
			else vertical.at<uchar>(x, y) = 255;
			cnt -= 1;
		}
	}
}

int main(int argc, char** argv)
{
	// Load the image
	Mat imgOriginal = imread("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\lotto.jpg", 1);

	const char* pzRotatedImage = "Rotated Image";
	const char* pzHorizontal = "horizontal";
	const char* pzVertical = "vertical";
	namedWindow(pzRotatedImage, WINDOW_NORMAL);
	namedWindow(pzHorizontal, WINDOW_NORMAL);
	namedWindow(pzVertical, WINDOW_NORMAL);
	double iAngle = 160.9287;

	int iImageHieght = imgOriginal.rows / 2;
	int iImageWidth = imgOriginal.cols / 2;

	Mat matRotation = getRotationMatrix2D(Point(iImageWidth, iImageHieght), (iAngle - 180), 1);
	
	// Rotate the image
	Mat imgRotated;
	warpAffine(imgOriginal, imgRotated, matRotation, imgOriginal.size());
	//imwrite("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\사진각도.jpg", imgRotated);
	Rect rect(161, 520, 564, 170);
	Mat gray256;
	cvtColor(imgRotated, gray256, COLOR_RGB2GRAY);
	//imwrite("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\256gray.jpg", gray256);
	Mat lotto = gray256(rect);
	//imwrite("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\캡쳐.jpg", lotto);
	Mat result;
	threshold(lotto, result, 127, 255, THRESH_OTSU);
	//imwrite("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\이진화.jpg", result);
	Mat horizontal(170, 564, CV_8U), vertical(170, 564, CV_8U);
	getHorizontal(result, horizontal);
	getVertical(result, vertical);
	imshow(pzRotatedImage, result);
	imshow(pzHorizontal, horizontal);
	imshow(pzVertical, vertical);
	waitKey(0);

	return 0;
}