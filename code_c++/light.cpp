#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
using namespace std;
using namespace cv;

//动态范围压缩与局部对比度增强的并行计算




//动态范围压缩与局部对比度增强的非并行算法
bool adaptblack(Mat &scr)
{
	//得到亮度分量
	Mat ycc;
	Mat matArray[3];
	Mat light[3];//原始亮度，增强的亮度，增强的对比度亮度；
	Mat dst;
	//int tmp;
	float proportion[3] = { 0.33333,0.33333,0.33333};//卷积权重比值影像较大
	float Z = 0, P = 0;
	//int RadiusS = 5, RadiusM = 20, RadiusL = 120;
	float Sum = 0, Mean = 0, StdDev = 0;
	vector<int> Histgram(256);
	cvtColor(scr, ycc, COLOR_RGB2HSV);//更改了通道口
	split(ycc, matArray);
	//light[0] = matArray[0];
	int Width = scr.cols;
	int	Height = scr.rows;
	//统计亮度分量的直方图,像素总和
	for (int i = 0; i < scr.rows; i++)
	{ 
		for (int j = 0; j < scr.cols; j++)
		{
			
			Sum = Sum + matArray[2].at< uchar >(i, j);
			Histgram[matArray[2].at< uchar >(i, j)]++;
			}

	}
	//平均值和均方差
	Mean = Sum / (scr.rows *scr.cols);
	for (int Y = 0; Y < 256; Y++) 
	{
		StdDev += Histgram[Y] * (Y - Mean) * (Y - Mean);

	}
	//    全局图像的均方差	
	StdDev = sqrtf(StdDev / (scr.rows *scr.cols)); 
	//    where L is the intensity level corresponding to a cumulative distribution function CDF of 0.1.
	int LowLevel = 50, HighLevel = 150;
	float MinCDF = 0.1f;
	int CDF = 0, L = 0;
		for (L = 0; L < 256; L++)
		{
			CDF += Histgram[L];
			if (CDF >= Width * Height * MinCDF)        
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
		int valu[3];
		GaussianBlur(matArray[2], light[0], cv::Size(5, 5), 0, 0);
		GaussianBlur(matArray[2], light[1], cv::Size(21, 21), 0, 0);
		GaussianBlur(matArray[2], light[2], cv::Size(121, 121), 0, 0);
		for (int i = 0; i < scr.rows; i++)
		{
			for (int j = 0; j < scr.cols; j++)
			{
				float I = matArray[2].at< uchar >(i, j) /255.0f;                            //    归一化                                  //整除问题
				I = (powf(I, 0.75f * Z + 0.25f) + (1 - I) * 0.4f * (1 - Z) + powf(I, 2 - Z)) * 0.5f; //    线性亮度增强 //公式3
				for (int k = 0; k < 3; k++)
				{
					valu[k] = proportion[k]*255 * powf(I, powf((light[k].at< uchar >(i, j) + 1.0f) / (matArray[2].at< uchar >(i, j) + 1.0f), P)) + 0.5f;

				}
				I = valu[0] + valu[1] + valu[2];
				
				if (I / matArray[2].at< uchar >(i, j) < 4.0)
				{
					matArray[2].at< uchar >(i, j) = I;
				}
				else
				{
					matArray[2].at< uchar >(i, j) = 4 * matArray[2].at< uchar >(i, j);
				}			
					
			}

		}		
		merge(matArray, 3, ycc);
		cvtColor(ycc, scr, COLOR_HSV2RGB);

return true;
}
bool adaptHSV(Mat &scr)
{
	Mat ycc;
	Mat matArray[3];
	Mat dst;
	cvtColor(scr,ycc, COLOR_RGB2HSV);
	split(ycc, matArray);
	equalizeHist(matArray[2], matArray[0]);
	merge(matArray, 3, ycc);
	cvtColor(ycc, scr, COLOR_HSV2RGB);


	return true;
}


bool adaptlightadd(Mat &scr)
{
	Mat gray;
	Mat dst;
	int weght;
	//float proportion[3] = { 76.245 / 255.0,77.685 / 255.0,29.07 / 255.0 };
	float proportion[3] = { 0.30,0.45,0.25};
	cvtColor(scr, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, dst);
	for (int i = 0; i < scr.rows; i++)
		for (int j = 0; j < scr.cols; j++) {
			int tmp_dst = dst.at<uchar>(i, j);
			int tmp_gray = gray.at<uchar>(i, j);
			weght = tmp_dst -tmp_gray;
			if(tmp_gray>150)
				for (int k = 0; k < 3; k++) {
					//weght = weght * proportion[k];
					int tmp = (uchar)scr.at<Vec3b>(i, j)[k] + weght*proportion[k];//更改权重赋值关系
					if (tmp > 255)
						tmp = (uchar)scr.at<Vec3b>(i, j)[k];
					scr.at<Vec3b>(i, j)[k] = tmp;
				}
			else 
				for (int k = 0; k < 3; k++) {
					//weght = weght * proportion[k];
					int tmp = (uchar)scr.at<Vec3b>(i, j)[k] + weght * proportion[k];//更改权重赋值关系
					if (tmp > 255)
						tmp = (uchar)scr.at<Vec3b>(i, j)[k];
					scr.at<Vec3b>(i, j)[k] = tmp;
				}
			
		}
	return true;
}

bool adaptlightmult(Mat &scr)
{
	Mat gray;
	Mat dst;
	float weght[2];
	float proportion[3] = { 76.245 / 255.0,77.685 / 255.0,29.07 / 255.0 };
	cvtColor(scr, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, dst);
	for (int i = 0; i < scr.rows; i++)
		for (int j = 0; j < scr.cols; j++) {
			int tmp_dst = dst.at<uchar>(i, j);
			int tmp_gray = gray.at<uchar>(i, j);
			if (tmp_gray != 0)
				weght[0] = tmp_dst / tmp_gray;
				weght[0] = tmp_dst;
			weght[1] = tmp_dst - tmp_gray;
			if (tmp_gray>180)
				for (int k = 0; k < 3; k++) {
					int tmp = (uchar)scr.at<Vec3b>(i, j)[k] + weght[1] * proportion[k];//更改权重赋值关系
					if (tmp > 255)
						tmp = (uchar)scr.at<Vec3b>(i, j)[k];
					scr.at<Vec3b>(i, j)[k] = tmp;
				}
			else 
				for (int k = 0; k < 3; k++) {
					//weght[1] = weght[1]*proportion[k];
					int tmp = (uchar)scr.at<Vec3b>(i, j)[k] + weght[1] * proportion[k];//更改权重赋值关系
					if (tmp > 255)
						tmp = (uchar)scr.at<Vec3b>(i, j)[k];
					scr.at<Vec3b>(i, j)[k] = tmp;
				}

			
		}
	return true;
}
int equalizeHist_Color(Mat &matSrc)
{
	if (matSrc.empty())
	{
		return -1;
	}
	Mat matArray[3];
	split(matSrc, matArray);//分通道
	// 直方图均衡化
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(matArray[i], matArray[i]);
	}
	Mat matResult;
	merge(matArray, 3, matResult);//合通道


	//imshow("src", matSrc);
	imshow("equlizeHist", matResult);

	//imwrite(strPath + "pic2_equlizeHist_color.jpg", matResult);
	return 0;
}


bool getVarianceMean(Mat &scr, Mat &meansDst, Mat &varianceDst, int winSize)
{
	if (!scr.data)  //判断图像是否被正确读取；
	{
		cerr << "获取方差与均值的函数读入图片有误";
		return false;
	}

	if (winSize % 2 == 0)
	{
		cerr << "计算局部均值与标准差的窗口大小应该为单数";
		return false;
	}

	Mat copyBorder_yChannels;                        //扩充图像边界；
	int copyBorderSize = (winSize - 1) / 2;
	copyMakeBorder(scr, copyBorder_yChannels, copyBorderSize, copyBorderSize, copyBorderSize, copyBorderSize, BORDER_REFLECT);

	for (int i = (winSize - 1) / 2; i < copyBorder_yChannels.rows - (winSize - 1) / 2; i++)
	{
		for (int j = (winSize - 1) / 2; j < copyBorder_yChannels.cols - (winSize - 1) / 2; j++)
		{

			Mat temp = copyBorder_yChannels(Rect(j - (winSize - 1) / 2, i - (winSize - 1) / 2, winSize, winSize));   //截取扩展后的图像中的一个方块；

			Scalar  mean;
			Scalar  dev;
			meanStdDev(temp, mean, dev);

			varianceDst.at<float>(i - (winSize - 1) / 2, j - (winSize - 1) / 2) = dev.val[0];     ///一一对应赋值；
			meansDst.at<float>(i - (winSize - 1) / 2, j - (winSize - 1) / 2) = mean.val[0];
		}
	}


	return true;
}


bool adaptContrastEnhancement(Mat &scr, Mat &dst, int winSize, int maxCg)
{
	if (!scr.data)  //判断图像是否被正确读取；
	{
		cerr << "自适应对比度增强函数读入图片有误";
		return false;
	}

	Mat ycc;                        //转换空间到YCrCb；
	cvtColor(scr, ycc, COLOR_RGB2YCrCb);

	vector<Mat> channels(3);        //分离通道；
	split(ycc, channels);


	Mat localMeansMatrix(scr.rows, scr.cols, CV_32FC1);
	Mat localVarianceMatrix(scr.rows, scr.cols, CV_32FC1);

	if (!getVarianceMean(channels[0], localMeansMatrix, localVarianceMatrix, winSize))   //对Y通道进行增强；
	{
		cerr << "计算图像均值与标准差过程中发生错误";
		return false;
	}

	Mat temp = channels[0].clone();

	Scalar  mean;
	Scalar  dev;
	meanStdDev(temp, mean, dev);

	float meansGlobal = mean.val[0];
	Mat enhanceMatrix(scr.rows, scr.cols, CV_8UC1);

	for (int i = 0; i < scr.rows; i++)            //遍历，对每个点进行自适应调节
	{
		for (int j = 0; j < scr.cols; j++)
		{
			if (localVarianceMatrix.at<float>(i, j) >= 0.01)
			{
				float cg = 0.2*meansGlobal / localVarianceMatrix.at<float>(i, j);
				float cgs = cg > maxCg ? maxCg : cg;
				cgs = cgs < 2 ? 2 : cgs;

				int e = localMeansMatrix.at<float>(i, j) + cgs * (temp.at<uchar>(i, j) - localMeansMatrix.at<float>(i, j));
				if (e > 255) { e = 255; }
				else if (e < 0) { e = 0; }
				enhanceMatrix.at<uchar>(i, j) = e;
			}
			else
			{
				enhanceMatrix.at<uchar>(i, j) = temp.at<uchar>(i, j);
			}
		}

	}

	channels[0] = enhanceMatrix;    //合并通道，转换颜色空间回到RGB
	merge(channels, ycc);

	cvtColor(ycc, dst, COLOR_YCrCb2RGB);

}


int main()
{
	
	Mat scr = imread("d:/test9.jpg");
	//Mat scrup1 = scr.clone();
	Mat scrup2 = scr.clone();
	//adaptlightadd(scrup1);
	//adaptlightmult(scrup2);
	//equalizeHist_Color(scr);
	//adaptHSV(scrup1);
	adaptblack(scrup2);
	//const int WINSIZE = 15;      //WINSIZE表示求均值与方差的窗口大小，应该是单数
	//const int MAXCG = 10;        //设定最大的增强比例

	//Mat dst = scr.clone();

	//adaptContrastEnhancement(scrup1, dst, WINSIZE,MAXCG);

	imshow("yuantu", scr);
	//imshow("HSV", scrup1);
	imshow("black", scrup2);
	imwrite("D:/testlight.jpg", scrup2);
	//imshow("3", dst);
	waitKey();

	return 0;
}