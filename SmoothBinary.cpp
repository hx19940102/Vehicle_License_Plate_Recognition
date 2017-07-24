#include "Head.h"

IplImage* SmoothBinary(IplImage*image_in)
{
	IplImage* image1 = cvCreateImage(cvGetSize(image_in), IPL_DEPTH_8U, 3);
	IplImage* image2 = cvCreateImage(cvGetSize(image_in), IPL_DEPTH_8U, 3);
	IplImage* image_out = cvCreateImage(cvGetSize(image_in), IPL_DEPTH_8U, 1);
	//高斯滤波
	cvSmooth(image_in, image1, CV_GAUSSIAN, 3, 3);
	//中值滤波
	cvSmooth(image1, image2, CV_MEDIAN, 3, 3);
	//转成灰度图
	cvCvtColor(image2, image_out, CV_BGR2GRAY);
	return image_out;
}