//
// File: main.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "main.h"
#include "lightpro.h"
#include "lightpro_initialize.h"
#include "rt_nonfinite.h"
//add image function
#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
using namespace std;
using namespace cv;


// Function Declarations
static unsigned char argInit_uint8_T();
static coder::array<unsigned char, 3U> c_argInit_UnboundedxUnboundedxU();
static void main_lightpro();

// Function Definitions

//
// Arguments    : void
// Return Type  : unsigned char
//
static unsigned char argInit_uint8_T()
{
  return 0U;
}

//
// Arguments    : void
// Return Type  : coder::array<unsigned char, 3U>
//
static coder::array<unsigned char, 3U> c_argInit_UnboundedxUnboundedxU()
{
  coder::array<unsigned char, 3U> result;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(2, 2, 2);

  // Loop over the array to initialize each element.
  for (int idx0 = 0; idx0 < result.size(0); idx0++) {
    for (int idx1 = 0; idx1 < result.size(1); idx1++) {
      for (int idx2 = 0; idx2 < result.size(2); idx2++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[(idx0 + result.size(0) * idx1) + result.size(0) * result.size(1) *
          idx2] = argInit_uint8_T();
      }
    }
  }

  return result;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_lightpro()
{
  coder::array<unsigned char, 3U> a;
  coder::array<double, 3U> iml;

  // Initialize function 'lightpro' input arguments.
  // Initialize function input argument 'a'.
  a = c_argInit_UnboundedxUnboundedxU();

  // Call the entry-point 'lightpro'.
  lightpro(a, iml);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//

//Iplimage-> coder::array<unsigned char, 3U>


static coder::array<unsigned char, 3U> ipl2arr(IplImage* img)
{
	coder::array<unsigned char, 3U> arr;
	int nWidth = img->width;
	int nHeight = img->height;
	int ndepth = img->depth;
	arr.set_size( nWidth, nHeight, 3);

	//ipl->byte

	//BYTE_T daya = img->imageData;

	//ipl 分通道
	//定义ipl
	IplImage *R = cvCreateImage(cvSize(nWidth,nHeight), ndepth, 1);
	IplImage *G = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);
	IplImage *B = cvCreateImage(cvSize(nWidth, nHeight), ndepth, 1);
	cvSplit(img,R, G, B, 0);

	//ipl->mat
	Mat mR = cvarrToMat(R);
	Mat mG = cvarrToMat(G);
	Mat mB = cvarrToMat(B);
	//Mat m = cvarrToMat(img);
	//double mx = m.at<uchar>(1,1);

	// Loop over the array to initialize each element.
	for (int idx0 = 0; idx0 < arr.size(0); idx0++) {
		for (int idx1 = 0; idx1 < arr.size(1); idx1++) {
			//mat->vector 的对应（高，宽）->(宽，高）
			arr[(idx0 + arr.size(0) * idx1) + arr.size(0) * arr.size(1) * 0] = 0;//mR.at<uchar>(idx1,idx0);
			arr[(idx0 + arr.size(0) * idx1) + arr.size(0) * arr.size(1) * 1] = 0;//mG.at<uchar>(idx1,idx0);
			arr[(idx0 + arr.size(0) * idx1) + arr.size(0) * arr.size(1) * 2] = 0;//mB.at<uchar>(idx1,idx0);
			
		}
	}
	return arr;
}





// coder::array<double, 3U> iml->Iplimage


static IplImage* arr2ipl(coder::array<double, 3U> iml)
{
	Mat m(iml.size(0), iml.size(1), iml.size(2), CV_8UC3);
	for (int idx0 = 0; idx0 < iml.size(0); idx0++) {
		for (int idx1 = 0; idx1 < iml.size(1); idx1++) {
			for (int idx2 = 0; idx2 < iml.size(2); idx2++) {
				 m.at<uchar>(idx0, idx1, idx2)=iml[(idx0 + iml.size(0) * idx1) + iml.size(0) * iml.size(1) *
					idx2] ;
			}
		}
	}

	IplImage* ipl = &IplImage(m);




	return ipl;
}










//main test
static void main_test()
{
	cout << '111';
	coder::array<double, 3U> iml;
	//读取数据
	IplImage *src = cvLoadImage("d:/mix/test.jpg");
	Mat img = imread("d:/mix/test.jpg");
	//数据类型转换*
	coder::array<unsigned char, 3U> arr = ipl2arr(src);
	//增强处理
	lightpro(arr, iml);
	//数据类型回归*
	IplImage* ipl = arr2ipl(iml);
	//显示处理结果
	cvShowImage("zero", ipl);

	cout << '2222';
	//imshow("yuan", scr);
	waitKey();

}





int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  lightpro_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.

  //add test 
  main_test();

  main_lightpro();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
