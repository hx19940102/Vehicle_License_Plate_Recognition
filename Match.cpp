#include "Head.h"

void ContourMatch(IplImage* num, SeqList* seqlist)//方案一：拿车牌上的轮廓与收集的标准数字轮廓进行匹配，效果比较差！
{
	IplImage* binary = cvCreateImage(cvGetSize(num), IPL_DEPTH_8U, 1);
	binary = SmoothBinary(num);
	IplImage* Thres = cvCreateImage(cvGetSize(num), IPL_DEPTH_8U, 1);
	cvThreshold(binary, Thres, 0, 255, CV_THRESH_OTSU);//二值化数字
	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* contour = 0;
	int contour_num = cvFindContours(Thres, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	double k = cvMatchShapes(contour, seqlist->seq[0], CV_CONTOURS_MATCH_I1);
	int result = 0;
	for (int i = 0; i < seqlist->length; i++)
	{
		if (seqlist->seq[i] == 0){ continue; }
		double j = cvMatchShapes(contour, seqlist->seq[i], CV_CONTOURS_MATCH_I1);
		if (k > j)
		{
			k = j;
			result = i;//轮廓匹配返回值最小的那个最相近
		}
	}
	if ((result == 8) || (result == 11))
	{
		CvMemStorage* storage2 = cvCreateMemStorage();
		CvSeq* lines;
		lines = cvHoughLines2(Thres, storage2, CV_HOUGH_STANDARD, 1, CV_PI / 180, 28, 0);
		if (lines->total >= 2)
		{
			result = 11;
		}
		else{ result = 8; }
	}
	if (result < 10)
	{
		printf("%d ", result);
	}
	if (result >= 10)
	{
		printf("%c ", result + 55);
	}
}


int PointMatch(IplImage* num, ThresList* threslist)//方案二：像素逐点比较，相似程度最高的模板即为带测量的值
{

	int step = num->widthStep;
	int pos = 0;
	int Identity = 0;
	for (int k = 0; k < threslist->length; k++)
	{
		if (threslist->num[k] == 0){ continue; }

		IplImage* thres = threslist->num[k];
		int Similarity = 0;
		for (int i = 0; i < num->height; i++)
		{
			for (int j = 0; j < num->width; j++)
			{
				if ((*(num->imageData + step*i + j)) == ((*(thres->imageData + step*i + j))))//比较每一个像素点，step为推向每行宽度，imagedata为像素信息（char*指针）
				{
					Similarity++;
				}
			}
		}
		if (k == 0){ Identity = Similarity; }
		if (Similarity > Identity){ Identity = Similarity; pos = k; }
	}


	if ((pos == 5) || (pos == 28))//区分5和S
	{
		if ((*(num->imageData + 2) == -1) || (*(num->imageData + 15)==-1))
		{
			pos = 5;
		}
		else{ pos = 28; }
	}


	if ((pos == 0) || (pos == 26))//区分0和Q
	{
		if (*(num->imageData + num->widthStep * 33 + 14) == -1)
		{
			pos = 26;
		}
		else{ pos = 0; }
	}


	if ((pos == 2) || (pos == 35))// 2/Z
	{
		if (*(num->imageData + 1) == 0)
		{
			pos = 2;
		}
		else{ pos = 35; }
	}


	if ((pos == 8) || (pos == 11)) //8 and B
	{
		if ((*(num->imageData + 33 * num->widthStep + 1) == -1)||(*(num->imageData+1)==-1))
		{
			pos = 11;
		}
		else{ pos = 8; }
	}

	return pos;
}


//第一个中文匹配的
int ProvinceMatch(IplImage* province, ThresList* standard)
{

	int step = province->widthStep;
	int pos = 0;
	int Identity = 0;
	for (int i = 0; i < standard->length; i++)
	{
		if (standard->num[i] == NULL){ continue; }
		IplImage* thres = standard->num[i];
		int similarity = 0;
		for (int j = 0; j < province->height; j++)
		{
			for (int k = 0; k < province->width; k++)
			{
				if (*(province->imageData + j*step + k) == *(thres->imageData + j*step + k))
				{
					similarity++;
				}
			}
		}
		if (i == 0){ Identity = similarity; }
		if (similarity >= Identity){
			Identity = similarity;
			pos = i;
		}
	}

	return pos;
}