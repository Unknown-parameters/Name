#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
using namespace std;
using namespace cv;

IplImage* LightAndContrast_change(IplImage* pImgSrc)
{

	IplImage *dst = cvCloneImage(pImgSrc);
	cvCvtColor(dst, dst, COLOR_RGB2HSV);


	int nWidth = dst->width;
	int nHeight = dst->height;
	int mult = nWidth * nHeight;
	int ndepth = dst->depth;
	//int nChannel = dst->nChannels;
	int wh = nWidth * nHeight;
	//int nStep = dst->widthStep;
	int RadiusS = 5, RadiusM = 20, RadiusL = 120;
	const int LowLevel = 50, HighLevel = 150;
	const float MinCDF = 0.1f;
	float invlin;
	float proportion = 0.33333333;
	float I;
	Scalar     mean;
	Scalar     dev;
	int detv;
	int *Histgram = (int *)calloc(256, sizeof(int));
	IplImage *V = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);
	//Mat VL;
	float Z = 0, P = 0;
	int CDF = 0, L = 0;
	float inv_255 = 0.003921569;
	//Mat vlin = cvarrToMat(V);

	//通道分开;
	cvSplit(dst, 0, 0, V, 0);
	Mat VL = cvarrToMat(V);

	//统计亮度分量的直方图

	//CvHistogram *hist =cvCreateHist( );

	//cvCalcHist(&V, hist);//([img], [0], None, [256], [0, 255]);

	int lin;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			lin = VL.at< uchar >(i, j);
			Histgram[lin]++;
		}

	}

	//均值和方差
	meanStdDev(VL, mean, dev);
	float m = mean.val[0];
	float s = dev.val[0];

	//计算Z和P值

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

	if (s <= 3)                                    //    计算P值，Also, P is determined by the globaln standard deviation  of the input intensity image Ix, y as
		P = 3;
	else if (s <= 10)
		P = (27 - 2 * s) / 7.0f;
	else
		P = 1;


	//高斯滤波//处理时需要实参);


	//矩阵
	Mat light[3];

	GaussianBlur(VL, light[0], cv::Size(5, 5), 0, 0);
	GaussianBlur(VL, light[1], cv::Size(21, 21), 0, 0);
	GaussianBlur(VL, light[2], cv::Size(121, 121), 0, 0);


	//根据全局的参量，进行亮度值的加权和修正
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			lin = VL.at< uchar >(i, j);
			invlin = 1 / (lin + 1.0f);
			I = lin * inv_255;                            //    归一化                                  //整除问题
			I = (powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f; //    线性亮度增强 //公式3

			I = (255 * powf(I, powf((light[0].at< uchar >(i, j) + 1.0f) *invlin, P)) +
				255 * powf(I, powf((light[1].at< uchar >(i, j) + 1.0f) * invlin, P)) +
				255 * powf(I, powf((light[2].at< uchar >(i, j) + 1.0f) *invlin, P)) + 0.5f)*proportion;//powf 比较耗时


			detv = 4.0* lin - I;
			if (detv > 0)
			{
				VL.at< uchar >(i, j) = I;
			}
			else
			{
				VL.at< uchar >(i, j) = 4 * lin;
			}

		}

	}
	V = &IplImage(VL);//浅拷贝

	cvMerge(0, 0, V, 0, dst);//通道合并



	//回归原本的色彩通道
	cvCvtColor(dst, dst, COLOR_HSV2RGB);
	//增强后的
	return dst;
}


int main()
{

	IplImage *src = cvLoadImage("d:/test3.jpg");

	IplImage *dst = LightAndContrast_change(src);

	cvShowImage("zero", dst);

	//imshow("yuan", scr);
	waitKey();
	return 0;
}
