#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
using namespace std;
using namespace cv;


//动态范围压缩与局部对比度增强的并行计算
//PNAE



//动态范围压缩与局部对比度增强的非并行算法
bool adaptblack1(Mat &scr)
{


	//得到亮度分量
	Mat ycc;
	int lin;
	int detv;
	float invlin;
	Mat matArray[3];
	Mat light[3];//卷积参数
	float proportion =  0.33333333;//卷积权重比值影像较大
	float Z = 0, P = 0;
	float Sum = 0, Mean = 0, StdDev = 0;
	vector<int> Histgram(256);
	int LowLevel = 50, HighLevel = 150;
	float MinCDF = 0.1f;
	int CDF = 0, L = 0;
	float I;
	int wh = scr.rows *scr.cols; //像素总和

	cvtColor(scr, ycc, COLOR_RGB2HSV);//更改通道表示
	split(ycc, matArray);//分通道

	
	//统计亮度分量的直方图
	for (int i = 0; i < scr.rows; i++)
	{
		for (int j = 0; j < scr.cols; j++)
		{
			lin = matArray[2].at< uchar >(i, j);
			Sum = Sum + lin;
			Histgram[lin]++;
		}

	}

	//平均值和均方差
	Mean = Sum / wh;
	for (int Y = 0; Y < 256; Y++)
	{
		StdDev += Histgram[Y] * (Y - Mean) * (Y - Mean);

	}
	//    全局图像的均方差	
	StdDev = sqrtf(StdDev / wh);
	//    where L is the intensity level corresponding to a cumulative distribution function CDF of 0.1.
	
	for (L = 0; L < 256; L++)
	{
		CDF += Histgram[L];
		if (CDF >= wh * MinCDF)
			break;
	}

	if (L <= LowLevel)
		Z = 0;
	else if (L <= HighLevel)
		Z = (L - LowLevel) * 1.0f / (HighLevel - LowLevel);                            //    计算Z值
	else
		Z = 1;

	if (StdDev <= 3)                                    //    计算P值，Also, P is determined by the globaln standard deviation  of the input intensity image Ix, y as
		P = 3;
	else if (StdDev <= 10)
		P = (27 - 2 * StdDev) / 7.0f;
	else
		P = 1;
	//局部对比度增强
		//依据领域信息，以高斯模糊的多级的权重实现
	
	GaussianBlur(matArray[2], light[0], cv::Size(5, 5), 0, 0);
	GaussianBlur(matArray[2], light[1], cv::Size(21, 21), 0, 0);
	GaussianBlur(matArray[2], light[2], cv::Size(121, 121), 0, 0);

	for (int i = 0; i < scr.rows; i++)
	{
		for (int j = 0; j < scr.cols; j++)
		{
			lin = matArray[2].at< uchar >(i, j);
			invlin = 1 / (lin + 1.0f);
		    I = lin * 0.003921569;                            //    归一化                                  //整除问题
			I = (powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f; //    线性亮度增强 //公式3

			I = (255 * powf(I, powf((light[0].at< uchar >(i, j) + 1.0f) *invlin, P))  +
				255 * powf(I, powf((light[1].at< uchar >(i, j) + 1.0f) * invlin , P)) +
				255 * powf(I, powf((light[2].at< uchar >(i, j) + 1.0f) *invlin, P)) + 0.5f)*proportion;//powf 比较耗时

		
			detv =  4.0* lin-I;
			if (detv >0)
			{
				matArray[2].at< uchar >(i, j) = I;
			}
			else
			{
				matArray[2].at< uchar >(i, j) = 4 * lin;
			}

		}

	}

	
	merge(matArray, 3, ycc);

	cvtColor(ycc, scr, COLOR_HSV2RGB);

	return true;
}

int main()
{

	Mat scr = imread("d:/test.jpg");
	adaptblack1(scr);
	imshow("yuan", scr);
	waitKey();
	return 0;
}


