#include "Head.h"

NumList* NumRec(IplImage* image_in)//车片内各个字母数字的分割
{
	IplImage* Grey = cvCreateImage(cvGetSize(image_in), IPL_DEPTH_8U, 1);
	Grey = SmoothBinary(image_in);
	IplImage* Thres = cvCreateImage(cvGetSize(image_in), IPL_DEPTH_8U, 1);
	cvThreshold(Grey, Thres, 0, 255, CV_THRESH_OTSU);


	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* contour = 0;
	RectList* list = (RectList*)malloc(sizeof(RectList));
	InitRectList(list);
	int contour_num = cvFindContours(Thres, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	for (; contour != NULL; contour = contour->h_next)
	{
		CvRect rect = cvBoundingRect(contour, 0);
		if (((rect.width)*(rect.height) < 1200) && ((rect.width)*(rect.height) >200) && (rect.width<100))//此处存在缺陷 由于数字1矩形包围的面积太小直接被忽略
		{
			AddRectToList(list, rect);
		}

	}


	//冒泡法:x坐标从左往右排序
	for (int i = 0; i < list->length; i++)
	{
		for (int j = i + 1; j<list->length; j++)
		{
			if (list->rect[i].x > list->rect[j].x)
			{
				CvRect rect;
				rect = list->rect[i];
				list->rect[i] = list->rect[j];
				list->rect[j] = rect;
			}
		}
	}


	//检测铆钉！含有铆钉的数字矩形必然比其他数字的矩形要长，以此作为判断依据
	for (int i = 0; i < list->length; i++)
	{
		float rate = 1.100000;
		float rate2 = 0.100000;
		if ((float)list->rect[i].height >(rate*(float)list->rect[3].height))//中间的数字是肯定没有铆钉的，如果某个矩形长度它要大0.1倍，可能含有铆钉
		{
			//铆钉钉在上面,那么y坐标比其他矩形要小
			if ((list->rect[3].y - list->rect[i].y) > (rate2*(float)list->rect[3].height))
			{
				CvRect rect = cvRect(list->rect[i].x, list->rect[i].y + (list->rect[i].height - list->rect[3].height), list->rect[i].width, list->rect[3].height);
				list->rect[i] = rect;
			}

			//铆钉钉在下面
			else{ CvRect rect = cvRect(list->rect[i].x, list->rect[i].y, list->rect[i].width, list->rect[3].height); }
		}

		rate = 0.900000;
		if ((float)list->rect[0].height < ((rate)*(float)list->rect[3].height))//如果第一个矩形比中间的要小很多，可能是省份的汉字被截断
		{
			CvRect rect = cvRect(list->rect[0].x, list->rect[0].y - list->rect[3].height + list->rect[0].height, list->rect[0].width, list->rect[3].height);
			list->rect[0] = rect;
		}
	}

	//如果有8个矩形，最后一个可能是干扰项，删去
	if (list->length == 8)
	{
		list->length--;
	}


	//补漏，如果不足7个数，必然是前面步骤把数字1给遗漏了
	if (list->length < 7)
	{
		for (int i = 0; i < list->length-1; i++)
		{
			//如果前后两个数字矩阵位置相差大于两个矩形宽度，中间肯定漏掉了一个1
			if ((list->rect[i + 1].x - list->rect[i].x) >= (2 * list->rect[i+1].width))
			{
				CvRect rect1 = cvRect(list->rect[i].x + list->rect[i].width, list->rect[i].y, 15, 20);//把1的矩阵定义为15*20大小的（15*20在后面可以作为判别1的依据）
				for (int j = list->length; j > i + 1; j--)
				{
					list->rect[j] = list->rect[j - 1];//往后移位
				}
				list->rect[i + 1] = rect1;//补上1
				list->length++;
			}
		}
	}

	//再次改进：可能数字1在最后一位！所以经历上一步之后仍然不足7个，那么最后一位补1(循环5次，可能车牌号是11111)
	for (int i = 0; i <= 4; i++)
	{
		if (list->length < 7)
		{
			CvRect rect1 = cvRect(list->rect[list->length - 1].x + list->rect[list->length - 1].width, list->rect[list->length - 1].y, 15, 20);
			list->rect[list->length] = rect1;
			list->length++;
		}
	}


	//画矩形边框(没有必要)
	//for (int i = 0; i < list->length; i++)
	//{
	//CvPoint point1 = cvPoint(list->rect[i].x, list->rect[i].y );
	//CvPoint point2 = cvPoint(list->rect[i].x + list->rect[i].width, list->rect[i].y + list->rect[i].height);
	//cvRectangle(image_in, point1, point2, CV_RGB(0, 255, 0), 1, 8, 0);
	//}
	//cvNamedWindow("numberrec");
	//cvShowImage("numberrec", image_in);


	//把数字区域ROI复制到新的图片，加入线性表
	NumList* numlist = (NumList*)malloc(sizeof(NumList));
	InitNumList(numlist);
	for (int i = 0; i < list->length; i++)
	{
		cvSetImageROI(image_in, list->rect[i]);
		IplImage* ROI = cvCreateImage(cvSize(list->rect[i].width, list->rect[i].height), IPL_DEPTH_8U, 3);
		cvCopy(image_in, ROI);
		AddNumToList(numlist, ROI);
		cvResetImageROI(image_in);
	}
	return numlist;
}