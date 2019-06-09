#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <algorithm>
#include <vector>
using namespace std;
using namespace cv;

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int width;
int height;
bool safe(int y, int x) {
	return 0 <= y && y < height && 0 <= x && x < width;
}

vector<vector<int> > skeleton(vector<vector<int> > & first, vector<vector<int> > & tmp) {
	vector<vector<int> > ret(height, (vector<int>(width, 0)));
	for (int y = 0; y < height; y += 1) {
		for (int x = 0; x < width; x += 1) {
			int val = 20000000;
			for (int i = 0; i < 4; i += 1) {
				int x2 = x + dx[i];
				int y2 = y + dx[i];
				if (safe(y2, x2)) {
					val = min(val, tmp[y2][x2]);
				}
				else {
					val = 0;
				}
			}
			ret[y][x] = val + first[y][x];
		}
	}
	return ret;
}

vector<vector<int> > skeleton2(vector<vector<int> > & tmp) {
	vector<vector<int> > ret(height, (vector<int>(width, 0)));
	for (int y = 0; y < height; y += 1) {
		for (int x = 0; x < width; x += 1) {
			bool flag = true;
			for (int i = 0; i < 4; i += 1) {
				int y2 = y + dy[i];
				int x2 = x + dx[i];
				if (safe(y2, x2)) {
					if (tmp[y][x] < tmp[y2][x2]) {
						flag = false;
						break;
					}
				}
				else continue;
			}
			if (flag) ret[y][x] = tmp[y][x];
		}
	}
	return ret;
}

bool equal(const vector<vector<int> > & cand, const vector<vector<int> > & tmp) {
	for (int y = 0; y < height; y += 1) {
		for (int x = 0; x < width; x += 1) {
			if (cand[y][x] != tmp[y][x]) return false;
		}
	}
	return true;
}

int main() {
	Mat image = imread("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\rectangle_2.jpg", 0);
	const char * pzSkeleton = "skeleton";
	threshold(image, image, 127, 255, THRESH_BINARY);
	width = (int)image.rows;
	height = (int)image.cols;
	vector<vector<int> > first(height, (vector<int>(width,0)));
	for (int y = 0; y < height; y += 1) {
		for (int x = 0; x < width; x += 1) {
			Scalar p = image.at<uchar>(x, y);
			first[y][x] = (p.val[0] != 255 ? 1 : 0);
		}
	}
	vector<vector<int> > tmp(first);
	bool flag;
	do {
		auto cand = skeleton(first, tmp);
		flag = equal(cand, tmp);
		tmp = cand;
	} while (!flag);
	
	auto tmp2 = skeleton2(tmp);
	
	for (int y = 0; y < height; y += 1) {
		for (int x = 0; x < width; x += 1) {
			if(tmp2[y][x]) image.at<uchar>(x, y) = 0;
			else image.at<uchar>(x, y) = 255;
		}
	}

	namedWindow(pzSkeleton, WINDOW_NORMAL);
	imshow(pzSkeleton, image);
	imwrite("C:\\Users\\ksaid\\Downloads\\4-1\\시각개론\\rectangle_2_result.jpg", image);
	waitKey(0);

	return 0;
}