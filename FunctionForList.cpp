#include "Head.h"

void InitRectList(RectList*list)
{
	list->length = 0;
}//初始化矩阵顺序表

void InitNumList(NumList*list)
{
	list->length = 0;
}//初始化顺序表

void InitSeqList(SeqList* list)
{
	list->length = 0;
}

void InitThresList(ThresList* list)
{
	list->length = 0;
}



void AddRectToList(RectList* list, CvRect rect)
{
	list->rect[list->length] = rect;
	list->length++;
}//添加矩阵到顺序表末尾

void AddNumToList(NumList* list, IplImage* num)
{
	list->num[list->length] = num;
	list->length++;
}//添加矩阵到顺序表末尾

void AddThresToList(ThresList* list, IplImage* num)
{
	IplImage* thres = cvCreateImage(cvGetSize(num), IPL_DEPTH_8U, 1);
	thres = SmoothBinary(num);
	cvThreshold(thres, thres, 0, 255, CV_THRESH_OTSU);
	list->num[list->length] = thres;
	list->length++;
}

void AddSeqToList(SeqList* list, IplImage* num)
{
	IplImage* binary = cvCreateImage(cvGetSize(num), IPL_DEPTH_8U, 1);
	binary = SmoothBinary(num);
	IplImage* Thres = cvCreateImage(cvGetSize(num), IPL_DEPTH_8U, 1);
	cvThreshold(binary, Thres, 0, 255, CV_THRESH_OTSU);
	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* seq = 0;
	int contour_num = cvFindContours(Thres, storage, &seq, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	list->seq[list->length] = seq;
	list->length++;
}

void DeleteRect(RectList* list, int num)
{
	for (int j = num; j < list->length - 1; j++)
	{
		list->rect[j] = list->rect[j + 1];
	}
	list->length--;
}//删除元素