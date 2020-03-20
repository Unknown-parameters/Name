#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
using namespace std;
using namespace cv;


bool adaptlight(Mat &src)
{
	Mat gray;
	Mat dst;
	float weght;
	cvtColor(src, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, dst);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			int  tmp_dst = dst.at<uchar>(i, j);
			int tmp_gray = gray.at<uchar>(i, j);
			if (tmp_gray != 0)
				weght = tmp_dst / tmp_gray;
			else
				weght = 0;
			for (int k = 0; k < 3; k++) {
				int tmp = (uchar)src.at<Vec3b>(i, j)[k] * weght;
				src.at<Vec3b>(i, j)[k] = tmp;
			}
		}
	return true;
}




int main()
{
	
	Mat src = imread("D:/test.jpg");
	Mat srcup = src.clone();
	adaptlight(srcup);
	imshow("yuantu", src);
	imshow("junhenhua", srcup);
	waitKey();

	return 0;
}