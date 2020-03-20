#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
using namespace std;
using namespace cv;


bool adaptlight(Mat &scr)
{
	Mat gray;
	Mat dst;
	double weght;
	cvtColor(scr, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, dst);
	for (int i = 0; i < scr.rows; i++)
		for (int j = 0; j < scr.cols; j++) {
			int tmp_dst = dst.at<uchar>(i, j);
			int tmp_gray = gray.at<uchar>(i, j);
			if (tmp_gray != 0)
				weght = tmp_dst / tmp_gray;
			else
				weght = 0;
			for (int k = 0; k < 3; k++) {
				int tmp = (uchar)scr.at<Vec3b>(i, j)[k] * weght;
				scr.at<Vec3b>(i, j)[k] = tmp;
			}
		}
	return true;
}




int main()
{
	
	Mat scr = imread("D:/test.jpg");
	Mat scrup = scr.clone();
	adaptlight(scrup);
	imshow("yuantu", scr);
	imshow("junhenhua", scrup);
	waitKey();

	return 0;
}