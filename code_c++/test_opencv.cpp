#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
#include <time.h>
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
	double proportion =  0.33333333;//卷积权重比值影像较大
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

	//==============================自适应的直方图均衡化=============
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

//改成指针类型的
IplImage* LightAndContrast_change(IplImage* pImgSrc )
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


	//根据全局的参量，进行亮度值的加权和修正/


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
	return dst;
}





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


	IplImage *dst = cvCloneImage(pImgSrc);
	cvCvtColor(dst, dst, COLOR_RGB2HSV);


	int nWidth = dst->width;
	int nHeight = dst->height;
	int mult = nWidth * nHeight;
	int ndepth = dst->depth;
	//int nChannel = dst->nChannels;
	int wh = nWidth * nHeight;
	//int nStep = dst->widthStep;
	//int RadiusS = 5, RadiusM = 20, RadiusL = 120;
	
	
	float invlin;
	//float proportion = 0.33333333;
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
	//CvMat mathdr, *VL = cvGetMat(V, &mathdr);
	//Mat VL(V,0);
	//统计亮度分量的直方图，函数对象的调用

	//创建直方图参数
	/*int dims = 1;
	int sizes[1] = { 255 };
	int type = CV_HIST_ARRAY;
	float arr[] = { 0.0f,255.0f };
	float *rangs[] = { arr };
*/

	int lin;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			
			lin = VL.at< uchar >(i, j);
			//gamma3
			//lin = 255 * powf(lin*inv_255, gamma);
			//VL.at< uchar >(i, j) = lin;
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
	Mat light;

	GaussianBlur(VL, light, cv::Size(25,25), 0, 0);
	//GaussianBlur(VL, light[1], cv::Size(21, 21), 0, 0);
	//GaussianBlur(VL, light[2], cv::Size(121, 121), 0, 0);


	//根据全局的参量，进行亮度值的加权和修正/


	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			lin = VL.at< uchar >(i, j);
			invlin = 1 / (lin + 1.0f);
			I = lin * inv_255; //    归一化                                  //整除问题
			
			//gamma2
			//I =  powf(I , 0.8);
			//lin = I*255;
			I = ((powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f); //    线性亮度增强 //公式3

			I =  (255 * powf(I, powf((light.at< uchar >(i, j) + 1.0f) *invlin, P)));// +
				//255 * powf(I, powf((light[1].at< uchar >(i, j) + 1.0f) * invlin, P)) +
				//255 * powf(I, powf((light[2].at< uchar >(i, j) + 1.0f) *invlin, P)) + 0.5f)*proportion;//powf 比较耗时
			//gamma1
			I =255* powf(I/255, gamma);
			
			
			//权重
			//addWeighted(input, 1.5, blur, -0.5, 0, usm);
			//cvAddWeighted();



			//压制过高的调节
			detv = para * lin - I;
			if (detv > 0)
			{
				VL.at< uchar >(i, j) = I;
			}
			else
			{
				VL.at< uchar >(i, j) = para*lin;
			}

		
	/*		
			detv = para* lin - I;
			if (detv > 0)
			{
				VL.at< uchar >(i, j) =255* powf(I*inv_255,gamma);
			}
			else
			{
				VL.at< uchar >(i, j) = 255*powf(para * lin*inv_255,gamma);
			}
*/
		}

	}

	//usm Unshrpen Mask
	//addWeighted(VL, 1.5, light, -0.5, 0, VL);

	//abs
	//convertScaleAbs(VL,VL);


	//laplacian 锐化
	//int scale = 1;
	//int delta = 0;
	//int ddepth = CV_16S;
	//int kernel_size = 1;
	//Laplacian(VL, VL, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);

	
	//这里的问题
	V = &IplImage(VL);//浅拷贝

	cvMerge(0, 0, V, 0, dst);//通道合并
	 //laplacian 锐化	//cvFilter2D

	/*IplImage *lapce = cvCloneImage(pImgSrc);
	cvLaplace(dst, lapce, 2);*/
	//cvConvertScaleAbs(lapce, dst);
	
	//回归原本的色彩通道
	cvCvtColor(dst, dst, COLOR_HSV2RGB);
	return dst;
}


//sharpening

void SHARPENING(Mat IMG)
{
	Mat input(IMG);
	//处理二位数据的滤波核不同
	Mat h1_kernel = (Mat_<char>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
	Mat h2_kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	Mat h1_result, h2_result;
	filter2D(input, h1_result, CV_32F, h1_kernel);
	filter2D(input, h2_result, CV_32F, h2_kernel);
	convertScaleAbs(h1_result, h1_result);
	convertScaleAbs(h2_result, h2_result);

	imshow("h1_result", h1_result);
	imshow("h2_result", h2_result);
	imwrite("d:/mix/changesharping.png", h2_result);
	waitKey();

}



//更改通道的直方图均衡
IplImage* changechannelslight(IplImage* dst)
{
	cvCvtColor(dst, dst, COLOR_RGB2HSV);
	IplImage *V = cvCreateImage(cvSize(dst->width, dst->height), dst->depth, 1);
	cvSplit(dst, 0, 0, V, 0);
	cvEqualizeHist(V, V);
	cvMerge(0, 0, V, 0, dst);//通道合并
	cvCvtColor(dst, dst, COLOR_HSV2RGB);//回归原本的色彩通道
	return dst;

}

int main()
{

	//cout << '111';
	clock_t start, finish;
	double  duration;
	
	IplImage *src =cvLoadImage("d:/mix/test.jpg");



	//IplImage *src = cvLoadImage("d:/mix/change.png");
	//Mat imgtest = cvarrToMat(src);
	//SHARPENING(imgtest);




	start = clock();

	//IplImage *dst = LightAndContrast_change2(src);

	IplImage *dst = changechannelslight(src);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);
	//IplImage *dst1 = LaplaceSharpen(src);
	cvShowImage("zero", dst);

	Mat img = cvarrToMat(dst);
	imwrite("d:/mix/change.jpg", img);

	//cvSaveImage("d:/mix/chang1.jpg", dst);
	//cvWrite( "d:/mix/chang.jpg");
	//cout << '2222';
	//imshow("yuan", scr);
	waitKey();
	return 0;
}


