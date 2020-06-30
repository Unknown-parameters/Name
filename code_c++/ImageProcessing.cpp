#include "StdAfx.h"
#include "ImageProcessing.h"
#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
#include <time.h>
using namespace std;
using namespace cv;

CImageProcessing::CImageProcessing(void)
{
}

CImageProcessing::~CImageProcessing(void)
{
}


//������Աȶ�//change
void CImageProcessing::LightAndContrast(IplImage* pImgSrc,IplImage* dst,int* params)
{

	if (pImgSrc == NULL) {
		return  ;
	}

	float inv_255 = 0.003921569;
	IplImage* dst = cvCloneImage(pImgSrc);

	cvCvtColor(dst, dst, COLOR_RGB2HSV);


	//���ȣ��ԱȶȲ�����Χ��ת��
	//����Z�����ȵ�������ǿ,��Χ[0,2]���̶�0.004<510>
	float Z = params[0]*inv_255+1.0;
	//����gamma,�Աȶȵķ�������ǿ(0,2)���̶�0.01<200>
	float gamma = params[1]*0.01+1;

	int nWidth = dst->width;
	int nHeight = dst->height;
	IplImage* V = cvCreateImage(cvSize(nWidth, nHeight), dst->depth, 1);
	//ͨ���ֿ�;
	cvSplit(dst, 0, 0, V, 0);
	Mat VL = cvarrToMat(V);
	for (int r = 0; r < nHeight; r++)
	{

		for (int w = 0; w < nWidth; w++)
		{
			float I = VL.at< uchar >(r, w);
			I = 255 * powf(I * inv_255*Z, gamma);//�Աȶ�,����
			if (I> 255) {
				I = 255;

			}
			
				VL.at< uchar >(r, w) = I;

			
		}
	}

	IplImage* vl = &IplImage(VL);

	cvMerge(0, 0, vl, 0, dst);

	//�ع�ԭ����ɫ��ͨ��
	cvCvtColor(dst, dst, COLOR_HSV2RGB);

	
}


//����laplace�˲�����//change
IplImage* CImageProcessing::LaplaceSharpen(IplImage* pImgSrc)
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


//��ɫƽ������Ӧ����  //change
IplImage* CImageProcessing::ColorLevelsAutoAdjusts(IplImage* dst)
{
	if(dst == NULL || (dst->nChannels != 3 && dst->nChannels != 1))
	{
		return NULL;
	}

	cvCvtColor(dst, dst, COLOR_RGB2HSV);
	IplImage* V = cvCreateImage(cvSize(dst->width, dst->height), dst->depth, 1);
	cvSplit(dst, 0, 0, V, 0);
	cvEqualizeHist(V, V);

	Mat VL = cvarrToMat(V);
	Ptr<cv::CLAHE>  claheimg = createCLAHE();
	claheimg->setClipLimit(4.);
	claheimg->setTilesGridSize(Size(8, 8));
	claheimg->apply(VL, VL);
	IplImage* vl = &IplImage(VL);
	cvMerge(0, 0, vl, 0, dst);
	cvCvtColor(dst, dst, COLOR_HSV2RGB);
	return dst;
}


//ɫ�࣬���Ͷȣ�����
void CImageProcessing::HueAndSaturationAndValue(IplImage* src, IplImage* dst,int* params)
{

	if (src == NULL) {
		return ;
	}
	

	float inv_255 = 0.003921569;
	float inv_90 = 0.011111111;
	float inv_128 = 0.0078125;
    dst = cvCloneImage(src);
	//ͨ��ת��
	cvCvtColor(dst, dst, COLOR_RGB2HSV);



	//����H��ɫ�෶Χ[0,2]���̶� (180)
	float H = params[0]*inv_90+1.0;
	//����S,���Ͷ�(0,2)���̶�   (256)
	float S = params[1]*inv_128+1.0;
	//����V  �����ȣ�0��2�����̶�   (256)
	float V = params[2]*inv_128+1.0;


	int nWidth = dst->width;
	int nHeight = dst->height;

	//int nStep = dst->widthStep;
	int ndepth = dst->depth;


	IplImage* cH = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);
	IplImage* cS = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);
	IplImage* cV = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);
	//ͨ���ֿ�;
	cvSplit(dst, cH, cS, cV, 0);
	Mat mH = cvarrToMat(cH);
	Mat mS = cvarrToMat(cS);
	Mat mV = cvarrToMat(cV);
	//������һ��

	//CvScalar I = { 0,0,0,0 };
	float hsv[] = { 0,0,0 };
	for (int r = 0; r < nHeight; r++)
	{

		for (int w = 0; w < nWidth; w++)
		{
			//ɫ��
			mH.at< uchar >(r, w) = 90 * powf(mH.at< uchar >(r, w) * inv_90, H);

			//���Ͷ�
			mS.at<uchar>(r, w) = 255 * powf(mS.at<uchar>(r, w) * inv_255, S);

			//����
			mV.at< uchar >(r, w) = 255 * powf(mV.at< uchar >(r, w) * inv_255, V);




		}
	}

	IplImage* ih = &IplImage(mH);
	IplImage* is = &IplImage(mS);
	IplImage* iv = &IplImage(mV);
	cvMerge(ih, is, iv, 0, dst);//ͨ���ϲ�


	//�ع�ԭ����ɫ��ͨ��
	cvCvtColor(dst, dst, COLOR_HSV2RGB);


}


//ֱ��ͼ���⻯  //change
IplImage* CImageProcessing::Equalize(IplImage* dst)
{
	cvCvtColor(dst, dst, COLOR_RGB2HSV);
	IplImage* V = cvCreateImage(cvSize(dst->width, dst->height), dst->depth, 1);
	cvSplit(dst, 0, 0, V, 0);
	cvEqualizeHist(V, V);
	cvMerge(0, 0, V, 0, dst);//ͨ���ϲ�
	cvCvtColor(dst, dst, COLOR_HSV2RGB);//�ع�ԭ����ɫ��ͨ��
	return dst;
}





//��ת
IplImage *CImageProcessing::RotateImage2(IplImage* img, int degree)  
{  
	double angle = degree  * CV_PI / 180.;
	double a = sin(angle), b = cos(angle);
	int width=img->width, height=img->height;

	//��ת�����ͼ�ߴ�
	int width_rotate= int(height * fabs(a) + width * fabs(b));
	int height_rotate=int(width * fabs(a) + height * fabs(b));
	IplImage* img_rotate = cvCreateImage(cvSize(width_rotate, height_rotate), img->depth, img->nChannels);
	cvZero(img_rotate);

	//��֤ԭͼ��������Ƕ���ת����С�ߴ�
	int tempLength = sqrt((double)width * width + (double)height *height) + 10;
	int tempX = (tempLength + 1) / 2 - width / 2;
	int tempY = (tempLength + 1) / 2 - height / 2;
	IplImage* temp = cvCreateImage(cvSize(tempLength, tempLength), img->depth, img->nChannels);
	cvZero(temp);

	//��ԭͼ���Ƶ���ʱͼ��tmp����
	cvSetImageROI(temp, cvRect(tempX, tempY, width, height));
	cvCopy(img, temp, NULL);
	cvResetImageROI(temp);

	//��ת����map
	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
	// [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
	float m[6];
	int w = temp->width;
	int h = temp->height;
	m[0] = b;
	m[1] = a;
	m[3] = -m[1];
	m[4] = m[0];

	// ����ת��������ͼ���м�  
	m[2] = w * 0.5f;
	m[5] = h * 0.5f;
	CvMat M = cvMat(2, 3, CV_32F, m);
	cvGetQuadrangleSubPix(temp, img_rotate, &M);
	cvReleaseImage(&temp);

	return img_rotate;
}


//��ת
void CImageProcessing::RunrotateImage(IplImage* src,IplImage* dst,int* params)
{
	IplImage *temp=cvCloneImage(src);
	temp = RotateImage2(temp,params[0]);
	cvResize(temp,dst);
}


//��ֵ����Ӧ����//RGB����ͨ������ֵ����
bool CImageProcessing::LevelsAutoAdjusts(IplImage* pSrcImg, IplImage* pDstImg, int nType)
{
	if(!pSrcImg&&!pDstImg) return FALSE;

	char* pSrc;
	char* pDst;

	int hist_size[] = {256};
	int max_value =0;
	int min_value =0;
	int max_new = 0;
	int min_new = 0;
	int min =0;
	float dif_value=0;

	long imgSize = pSrcImg->height * pSrcImg->width;
	float delSize = (float)imgSize * 0.055; 
	
	//����ֱ��ͼ
	CvHistogram* hist = cvCreateHist(1, hist_size, CV_HIST_ARRAY );
	//��ȡ��ͨ��ֱ��ͼͳ��
	cvCalcHist(&pSrcImg, hist, 0, 0 );
	//cvGetMinMaxHistValue(hist,0, 0,  &min_value, &max_value );
	//dif_value = max_value - min_value;
	//max_new = max_value;
	//min_new = min_value;
	float sum =0;
	int i ;
	bool br = TRUE;
	for(i=0;i<256;i++)
	{
		//��ȡֱ��ͼ��ɫ��ͳ�Ƶ�����
		float bin_val = cvQueryHistValue_1D( hist,i );

		//�״�ΪTRUE
		if(br)
		{
			if(bin_val>0)
			{
				min_value =i;
				br = FALSE;

			}
		}
		else
		{
			sum += bin_val ;
			if(sum>delSize)
			{
				min_new = i;
				break;
			}

		}

	}
	sum =0 ;
	br = TRUE;
	for(i=255;i>0;i--)
	{
		float bin_val = cvQueryHistValue_1D( hist,i );
		if(br)
		{
			if(bin_val>0)
			{
				max_value =i;
				br = FALSE;

			}
		}
		else
		{
			sum += bin_val ;
			if(sum>delSize)
			{
				max_new = i;
				break;
			}
		}

	}

	float differ=1;
	if(0==nType)
	{
		differ= max_new - min_new;
		min = min_new;
	}
	else
	{
		differ= max_value - min_value;
		min = min_value;
	}
	float val = 0;
	if(0==differ)
	{
		differ =1;
	}

	for(i=0;i<pSrcImg->height;i++)
		for(int j=0;j<pSrcImg->widthStep;j++)
		{
			pSrc = pSrcImg->imageData + i* pSrcImg->widthStep +j;
			pDst = pDstImg->imageData + i* pDstImg->widthStep +j;
			int r = (unsigned char)*pSrc;
			val = ((float)(r - min)/differ)*255;
			if(val<0)
				*pDst =0;
			else if(val>255)
				*pDst =255;
			else
				*pDst =(int)val;

		}
		return TRUE;
}








