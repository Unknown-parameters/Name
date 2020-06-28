#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
#include <time.h>
using namespace std;
using namespace cv;

//=========================================imageprogress=================
//基础锐化，简化
IplImage* LaplaceSharpen1(IplImage* pImgSrc)
{
	if (pImgSrc == NULL)
	{
		return NULL;
	}

	double a[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
	const CvMat kernel = cvMat(3, 3, CV_64FC1, a);
	cvFilter2D(pImgSrc, pImgSrc, &kernel);
	return pImgSrc;
}


//改通道直方图均衡化
IplImage* Equalize1(IplImage* dst)
{
	cvCvtColor(dst, dst, COLOR_RGB2HSV);
	IplImage* V = cvCreateImage(cvSize(dst->width, dst->height), dst->depth, 1);
	cvSplit(dst, 0, 0, V, 0);
	cvEqualizeHist(V, V);
	cvMerge(0, 0, V, 0, dst);
	cvCvtColor(dst, dst, COLOR_HSV2RGB);
	return dst;
}



//亮度与对比度
IplImage* LightAndContrast_change2(IplImage* pImgSrc)
{
	//控制增幅
	float para = 2.0;
	//gamma1 参数
	float gamma = 0.9;
	//增强范围
	const int LowLevel = 5, HighLevel = 50;
	//
	const float MinCDF = 0.1f;


	IplImage* dst = cvCloneImage(pImgSrc);
	cvCvtColor(dst, dst, COLOR_RGB2HSV);


	int nWidth = dst->width;
	int nHeight = dst->height;
	int mult = nWidth * nHeight;
	int ndepth = dst->depth;
	int wh = nWidth * nHeight;


	float invlin;
	float I;
	Scalar     mean;
	Scalar     dev;
	int detv;
	IplImage* V = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);

	float Z = 0, P = 0;
	int CDF = 0, L = 0;
	float inv_255 = 0.003921569;


	//通道分开;
	cvSplit(dst, 0, 0, V, 0);
	Mat VL = cvarrToMat(V);



	IplImage** testv = &V;
	int bins = 256;
	int hist_size[] = { bins };
	float v_ranges[] = { 0,256 };
	float* ranges[] = { v_ranges };

	CvHistogram* hist = cvCreateHist(1, hist_size, CV_HIST_ARRAY, ranges, 1);

	cvCalcHist(testv, hist);

	int lin;


	//均值和方差
	meanStdDev(VL, mean, dev);
	float m = mean.val[0];
	float s = dev.val[0];

	//计算Z和P值

	for (L = 0; L < bins; L++)
	{
		//CDF += Histgram[L];
		CDF += cvGetReal1D((hist)->bins, (L));
		if (CDF >= wh * MinCDF)
			break;
	}
	//cvReleaseHist(&hist);

	if (L <= LowLevel)
		Z = 0;
	else if (L <= HighLevel)
		Z = (L - LowLevel) * 1.0f / (HighLevel - LowLevel);                            
	else
		Z = 1;

	if (s <= 3)                                  
		P = 3;
	else if (s <= 10)
		P = (27 - 2 * s) / 7.0f;
	else
		P = 1;



	Mat light;

	GaussianBlur(VL, light, cv::Size(25, 25), 0, 0);



	//根据全局的参量，进行亮度值的加权和修正/


	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			lin = VL.at< uchar >(i, j);
			invlin = 1 / (lin + 1.0f);
			I = lin * inv_255; //    归一化                                

			//gamma2
			//I =  powf(I , 0.8);
			//lin = I*255;
			I = ((powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f); //    线性亮度增强 //公式3

			I = (255 * powf(I, powf((light.at< uchar >(i, j) + 1.0f) * invlin, P)));
			//gamma1
			I = 255 * powf(I / 255, gamma);//对比度增强

			//压制过高的调节
			detv = para * lin - I;
			if (detv > 0)
			{
				VL.at< uchar >(i, j) = I;
			}
			else
			{
				VL.at< uchar >(i, j) = para * lin;
			}


		}

	}

	

	IplImage* vl = &IplImage(VL);//浅拷贝

	cvMerge(0, 0, vl, 0, dst);//通道合并


	//回归原本的色彩通道
	cvCvtColor(dst, dst, COLOR_HSV2RGB);
	return dst;
}




//限制对比度自适应直方图均衡(Contrast Limited Adaptive Histogram Equalization,CLAHE)

IplImage* Claheligt(IplImage* dst)
{
	cvCvtColor(dst, dst, COLOR_RGB2HSV);
	IplImage* V = cvCreateImage(cvSize(dst->width, dst->height), dst->depth, 1);
	cvSplit(dst, 0, 0, V, 0);
	Mat MATV = cvarrToMat(V);

	Ptr<cv::CLAHE>  claheimg = createCLAHE();

	claheimg->setClipLimit(4.);
	claheimg->setTilesGridSize(Size(8, 8));
	claheimg->apply(MATV, MATV);


	IplImage* vl = &IplImage(MATV);//浅拷贝
	cvMerge(0, 0, vl, 0, dst);//通道合并
	cvCvtColor(dst, dst, COLOR_HSV2RGB);//回归原本的色彩通道
	return dst;

}


//CLAHE +light
IplImage* adaptlight(IplImage* pImgSrc)
{
	//控制增幅
	float para = 2.0;
	//gamma1 参数
	float gamma = 0.9;
	//增强范围
	const int LowLevel = 5, HighLevel = 50;
	//
	const float MinCDF = 0.1f;


	IplImage* dst = cvCloneImage(pImgSrc);
	cvCvtColor(dst, dst, COLOR_RGB2HSV);


	int nWidth = dst->width;
	int nHeight = dst->height;
	int mult = nWidth * nHeight;
	int ndepth = dst->depth;
	int wh = nWidth * nHeight;


	float invlin;
	float I;
	Scalar     mean;
	Scalar     dev;
	int detv;
	IplImage* V = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);

	float Z = 0, P = 0;
	int CDF = 0, L = 0;
	float inv_255 = 0.003921569;


	//通道分开;
	cvSplit(dst, 0, 0, V, 0);
	Mat VL = cvarrToMat(V);



	IplImage** testv = &V;
	int bins = 256;
	int hist_size[] = { bins };
	float v_ranges[] = { 0,256 };
	float* ranges[] = { v_ranges };

	CvHistogram* hist = cvCreateHist(1, hist_size, CV_HIST_ARRAY, ranges, 1);

	cvCalcHist(testv, hist);

	int lin;


	//均值和方差
	meanStdDev(VL, mean, dev);
	float m = mean.val[0];
	float s = dev.val[0];

	//计算Z和P值

	for (L = 0; L < bins; L++)
	{
		//CDF += Histgram[L];
		CDF += cvGetReal1D((hist)->bins, (L));
		if (CDF >= wh * MinCDF)
			break;
	}
	//cvReleaseHist(&hist);

	if (L <= LowLevel)
		Z = 0;
	else if (L <= HighLevel)
		Z = (L - LowLevel) * 1.0f / (HighLevel - LowLevel);
	else
		Z = 1;

	if (s <= 3)
		P = 3;
	else if (s <= 10)
		P = (27 - 2 * s) / 7.0f;
	else
		P = 1;



	Mat light;

	GaussianBlur(VL, light, cv::Size(25, 25), 0, 0);



	//根据全局的参量，进行亮度值的加权和修正/


	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			lin = VL.at< uchar >(i, j);
			invlin = 1 / (lin + 1.0f);
			I = lin * inv_255; //    归一化                                

			//gamma2
			//I =  powf(I , 0.8);
			//lin = I*255;
			I = ((powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f); //    线性亮度增强 //公式3

			I = (255 * powf(I, powf((light.at< uchar >(i, j) + 1.0f) * invlin, P)));
			//gamma1
			I = 255 * powf(I / 255, gamma);//对比度增强

			//压制过高的调节
			detv = para * lin - I;
			if (detv > 0)
			{
				VL.at< uchar >(i, j) = I;
			}
			else
			{
				VL.at< uchar >(i, j) = para * lin;
			}


		}

	}


	Ptr<cv::CLAHE>  claheimg = createCLAHE();

	claheimg->setClipLimit(4.);
	claheimg->setTilesGridSize(Size(8, 8));
	claheimg->apply(VL, VL);

	IplImage* vl = &IplImage(VL);//浅拷贝

	cvMerge(0, 0, vl, 0, dst);//通道合并


	//回归原本的色彩通道
	cvCvtColor(dst, dst, COLOR_HSV2RGB);
	return dst;
}








int main()
{

	//cout << '111';
	clock_t start, finish;
	double  duration;

	IplImage* src = cvLoadImage("d:/mix/test.jpg");



	//IplImage *src = cvLoadImage("d:/mix/testex.png");
	//Mat imgtest = cvarrToMat(src);
	//SHARPENING(imgtest);




	start = clock();


	//function start


	//IplImage* dst = Claheligt(src);

	//IplImage *dst = Claheligt(src);



	IplImage *dst = LaplaceSharpen1(src);
	//IplImage *dst = HueAndSaturationAndValue(src);


	//=============function end==============================
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);


	//show
	cvShowImage("zero", dst);


	//写入
	Mat img = cvarrToMat(dst);
	imwrite("d:/mix/change.jpg", img);


	waitKey();
	return 0;
}