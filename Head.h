#include <opencv2\opencv.hpp>
#include "stdio.h"
#include "math.h"

typedef struct _rectList{
	CvRect rect[200];
	int length;
}RectList;

typedef struct _NumList{
	IplImage* num[20];
	int length;
}NumList;

typedef struct _SeqList{
	CvSeq* seq[100];
	int length;
}SeqList;

typedef struct _ThresList{
	IplImage* num[100];
	int length;
}ThresList;

void InitRectList(RectList*list);
void InitNumList(NumList*list);
void InitSeqList(SeqList* list);
void InitThresList(ThresList* list);
void AddRectToList(RectList* list, CvRect rect);
void AddNumToList(NumList* list, IplImage* num);
void AddSeqToList(SeqList* list, IplImage* num);
void AddThresToList(ThresList* list, IplImage* num);
void DeleteRect(RectList* list, int num);
IplImage* SmoothBinary(IplImage*image_in);
IplImage* SecondRec(IplImage* image_in);
NumList* NumRec(IplImage* image_in);
void ContourMatch(IplImage* num, SeqList* seqlist);
int PointMatch(IplImage* num, ThresList* threslist);
int ProvinceMatch(IplImage* province, ThresList* standard);