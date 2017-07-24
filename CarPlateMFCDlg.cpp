
// CarPlateMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CarPlateMFC.h"
#include "CarPlateMFCDlg.h"
#include "afxdialogex.h"
#include "Head.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCarPlateMFCDlg dialog



CCarPlateMFCDlg::CCarPlateMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CARPLATEMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCarPlateMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
}

BEGIN_MESSAGE_MAP(CCarPlateMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCarPlateMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCarPlateMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCarPlateMFCDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CCarPlateMFCDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CCarPlateMFCDlg message handlers

BOOL CCarPlateMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	//创建字体
	m_editFont.CreatePointFont(250, _T("宋体"));
	GetDlgItem(IDC_EDIT1)->SetFont(&m_editFont); // 设置新字体

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCarPlateMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCarPlateMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCarPlateMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCarPlateMFCDlg::ShowImage(IplImage* pic, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	SetRect(rect, rect.left, rect.top, rect.right, rect.bottom);
	CvvImage cimg;
	cimg.CopyOf(pic);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}

IplImage* image = new IplImage;

void CCarPlateMFCDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString PicPath;
	//弹出对话框选择图片
	CFileDialog dlg(true, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, _T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), NULL);
	dlg.m_ofn.lpstrTitle = _T("open Image");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	PicPath = dlg.GetPathName();
	PicPath.Replace(_T("//"), _T("////"));

	IplImage* pic = cvLoadImage((CT2CA)PicPath);
	if (pic == NULL)
	{
		return;
	}

	ShowImage(pic, IDC_STATIC_PIC);
	image = pic;
}


void CCarPlateMFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//高斯滤波，中值滤波，转为灰度图像
	IplImage* binary = SmoothBinary(image);

	//进行X方向求导，求出X方向垂直边缘明显的区域，清除其他无用部分
	IplImage* _sobel = cvCreateImage(cvGetSize(image), IPL_DEPTH_16S, 1);
	cvSobel(binary, _sobel, 1, 0, 3);
	//cvsobel使用16位有符号，现将其恢复为8位无符号图片
	IplImage* sobel = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvConvertScale(_sobel, sobel);

	//接着进行二值化
	IplImage* Thres = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvThreshold(sobel, Thres, 0, 255, CV_THRESH_OTSU);

	//X方向膨胀连通车牌区域，然后腐蚀去除小碎片，膨胀恢复有用部分
	IplImage* dilate = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	IplConvKernel* kernel = cvCreateStructuringElementEx(3, 1, 0, 0, CV_SHAPE_RECT);
	cvDilate(Thres, dilate, kernel, 18);
	cvErode(dilate, dilate, kernel, 36);
	cvDilate(dilate, dilate, kernel, 32);

	IplImage* erode = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	kernel = cvCreateStructuringElementEx(1, 3, 0, 0, CV_SHAPE_RECT);
	cvErode(dilate, erode, kernel, 8);
	cvDilate(erode, erode, kernel, 16);//Y方向腐蚀小碎片，膨胀恢复
									   //cvNamedWindow("xx", CV_WINDOW_AUTOSIZE);
									   //cvShowImage("xx", erode);

									   //接下来做轮廓检测并用矩形包围
	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* contour = 0;
	RectList* list = (RectList*)malloc(sizeof(RectList));
	InitRectList(list);
	int contour_num = cvFindContours(erode, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));//寻找外围轮廓
	for (; contour != NULL; contour = contour->h_next)
	{
		CvRect rect = cvBoundingRect(contour, 0);//将轮廓用矩形包围
		AddRectToList(list, rect);
	}

	IplImage* imagecopy = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvCopy(image, imagecopy);
	for (int i = 0; i < list->length; i++)
	{
		CvPoint point1 = cvPoint(list->rect[i].x + 90, list->rect[i].y + 20);//膨胀腐蚀之后位置的矫正
		CvPoint point2 = cvPoint(list->rect[i].x + list->rect[i].width + 90, list->rect[i].y + list->rect[i].height + 20);
		cvRectangle(imagecopy, point1, point2, CV_RGB(255, 0, 0), 3, 8, 0);//绘制得到的矩形轮廓
	}

	//筛选矩形(长宽比/原图像该区域是否包含蓝色和白色/面积大概多少)
	for (int i = 0; i <= list->length - 1; i++)
	{
		float rate = (float)(list->rect[i].width) / (list->rect[i].height);//长宽比
		int area = (list->rect[i].width)*(list->rect[i].height);//面积
		if ((rate<2.800000) || (rate>4.4000000)) { DeleteRect(list, i); i--; continue; }//长宽比不符合则删除，继续下一个循环

		if ((area <= 4000) || (area >= 18000)) { DeleteRect(list, i); i--; continue; }//面积不符合删去，继续下一个循环

		if (((list->rect[i].x + 90 + list->rect[i].width) > imagecopy->width)) { DeleteRect(list, i); i--; continue; };//矫正之后矩形若超过图像边界删除

		CvRect rect = cvRect(list->rect[i].x + 90, list->rect[i].y + 20, list->rect[i].width, list->rect[i].height);
		cvSetImageROI(imagecopy, rect);//设置ROI
		IplImage* ROI = cvCreateImage(cvSize(list->rect[i].width, list->rect[i].height), IPL_DEPTH_8U, 3);
		cvCopy(imagecopy, ROI);//将矩形部分图像提取出来
		IplImage* CvtROI = cvCreateImage(cvGetSize(ROI), IPL_DEPTH_8U, 3);
		cvCvtColor(ROI, CvtROI, CV_BGR2HSV);//转化为HSV
		cvReleaseImage(&ROI);
		IplImage* H = cvCreateImage(cvGetSize(CvtROI), IPL_DEPTH_8U, 1);
		IplImage* S = cvCreateImage(cvGetSize(CvtROI), IPL_DEPTH_8U, 1);
		IplImage* V = cvCreateImage(cvGetSize(CvtROI), IPL_DEPTH_8U, 1);
		cvSplit(CvtROI, H, S, V, 0);//分成三通道
		cvReleaseImage(&CvtROI);
		int widthstep = H->widthStep;
		uchar data;
		int total = 0;//蓝色点个数的总数
		for (int k = 0; k < H->height; k++)
		{
			for (int j = 0; j < H->width; j++)
			{
				data = H->imageData[k*widthstep + j];
				if ((data>95) && (data < 120))//H空间每个像素点的值在95到120之间大概是蓝色
				{
					total++;//蓝色像素点总数
				}
			}
		}
		float portion = ((float)total / (float)(H->height*H->width));
		if (portion < 0.200000) { DeleteRect(list, i); i--; }
		cvResetImageROI(imagecopy);//取消ROI
	}

	IplImage* imagecopy2 = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvCopy(image, imagecopy2);
	for (int i = 0; i < list->length; i++)
	{
		CvPoint point1 = cvPoint(list->rect[i].x + 90, list->rect[i].y + 20);
		CvPoint point2 = cvPoint(list->rect[i].x + list->rect[i].width + 90, list->rect[i].y + list->rect[i].height + 20);
		cvRectangle(imagecopy2, point1, point2, CV_RGB(255, 0, 0), 3, 8, 0);
	}
	ShowImage(imagecopy2, IDC_STATIC_PIC);
}


void CCarPlateMFCDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//高斯滤波，中值滤波，转为灰度图像
	IplImage* binary = SmoothBinary(image);

	//进行X方向求导，求出X方向垂直边缘明显的区域，清除其他无用部分
	IplImage* _sobel = cvCreateImage(cvGetSize(image), IPL_DEPTH_16S, 1);
	cvSobel(binary, _sobel, 1, 0, 3);
	//cvsobel使用16位有符号，现将其恢复为8位无符号图片
	IplImage* sobel = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvConvertScale(_sobel, sobel);

	//接着进行二值化
	IplImage* Thres = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvThreshold(sobel, Thres, 0, 255, CV_THRESH_OTSU);

	//X方向膨胀连通车牌区域，然后腐蚀去除小碎片，膨胀恢复有用部分
	IplImage* dilate = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	IplConvKernel* kernel = cvCreateStructuringElementEx(3, 1, 0, 0, CV_SHAPE_RECT);
	cvDilate(Thres, dilate, kernel, 18);
	cvErode(dilate, dilate, kernel, 36);
	cvDilate(dilate, dilate, kernel, 32);

	IplImage* erode = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	kernel = cvCreateStructuringElementEx(1, 3, 0, 0, CV_SHAPE_RECT);
	cvErode(dilate, erode, kernel, 8);
	cvDilate(erode, erode, kernel, 16);//Y方向腐蚀小碎片，膨胀恢复
									   //cvNamedWindow("xx", CV_WINDOW_AUTOSIZE);
									   //cvShowImage("xx", erode);

									   //接下来做轮廓检测并用矩形包围
	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* contour = 0;
	RectList* list = (RectList*)malloc(sizeof(RectList));
	InitRectList(list);
	int contour_num = cvFindContours(erode, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));//寻找外围轮廓
	for (; contour != NULL; contour = contour->h_next)
	{
		CvRect rect = cvBoundingRect(contour, 0);//将轮廓用矩形包围
		AddRectToList(list, rect);
	}

	IplImage* imagecopy = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvCopy(image, imagecopy);
	for (int i = 0; i < list->length; i++)
	{
		CvPoint point1 = cvPoint(list->rect[i].x + 90, list->rect[i].y + 90);//膨胀腐蚀之后位置的矫正
		CvPoint point2 = cvPoint(list->rect[i].x + list->rect[i].width + 90, list->rect[i].y + list->rect[i].height + 20);
		cvRectangle(imagecopy, point1, point2, CV_RGB(255, 0, 0), 3, 8, 0);//绘制得到的矩形轮廓
	}

	//筛选矩形(长宽比/原图像该区域是否包含蓝色和白色/面积大概多少)
	for (int i = 0; i <= list->length - 1; i++)
	{
		float rate = (float)(list->rect[i].width) / (list->rect[i].height);//长宽比
		int area = (list->rect[i].width)*(list->rect[i].height);//面积
		if ((rate<2.800000) || (rate>4.4000000)) { DeleteRect(list, i); i--; continue; }//长宽比不符合则删除，继续下一个循环

		if ((area <= 4000) || (area >= 18000)) { DeleteRect(list, i); i--; continue; }//面积不符合删去，继续下一个循环

		if (((list->rect[i].x + 90 + list->rect[i].width) > imagecopy->width)) { DeleteRect(list, i); i--; continue; };//矫正之后矩形若超过图像边界删除

		CvRect rect = cvRect(list->rect[i].x + 90, list->rect[i].y + 20, list->rect[i].width, list->rect[i].height);
		cvSetImageROI(imagecopy, rect);//设置ROI
		IplImage* ROI = cvCreateImage(cvSize(list->rect[i].width, list->rect[i].height), IPL_DEPTH_8U, 3);
		cvCopy(imagecopy, ROI);//将矩形部分图像提取出来
		IplImage* CvtROI = cvCreateImage(cvGetSize(ROI), IPL_DEPTH_8U, 3);
		cvCvtColor(ROI, CvtROI, CV_BGR2HSV);//转化为HSV
		cvReleaseImage(&ROI);
		IplImage* H = cvCreateImage(cvGetSize(CvtROI), IPL_DEPTH_8U, 1);
		IplImage* S = cvCreateImage(cvGetSize(CvtROI), IPL_DEPTH_8U, 1);
		IplImage* V = cvCreateImage(cvGetSize(CvtROI), IPL_DEPTH_8U, 1);
		cvSplit(CvtROI, H, S, V, 0);//分成三通道
		cvReleaseImage(&CvtROI);
		int widthstep = H->widthStep;
		uchar data;
		int total = 0;//蓝色点个数的总数
		for (int k = 0; k < H->height; k++)
		{
			for (int j = 0; j < H->width; j++)
			{
				data = H->imageData[k*widthstep + j];
				if ((data>95) && (data < 120))//H空间每个像素点的值在95到120之间大概是蓝色
				{
					total++;//蓝色像素点总数
				}
			}
		}
		float portion = ((float)total / (float)(H->height*H->width));
		if (portion < 0.200000) { DeleteRect(list, i); i--; }
		cvResetImageROI(imagecopy);//取消ROI
	}

	IplImage* imagecopy2 = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvCopy(image, imagecopy2);
	for (int i = 0; i < list->length; i++)
	{
		CvPoint point1 = cvPoint(list->rect[i].x + 90, list->rect[i].y + 20);
		CvPoint point2 = cvPoint(list->rect[i].x + list->rect[i].width + 90, list->rect[i].y + list->rect[i].height + 20);
		cvRectangle(imagecopy2, point1, point2, CV_RGB(255, 0, 0), 3, 8, 0);
	}
	//ShowImage(imagecopy2, IDC_STATIC_PIC);


	CvRect plate = cvRect(list->rect[0].x + 90, list->rect[0].y + 20, list->rect[0].width, list->rect[0].height);//车牌矩形的位置
	cvSetImageROI(imagecopy2, plate);//设置ROI
	IplImage* ROI = cvCreateImage(cvSize(list->rect[0].width, list->rect[0].height), IPL_DEPTH_8U, 3);
	cvCopy(imagecopy2, ROI);

	IplImage* num = SecondRec(ROI);//二次提取车牌

	NumList* numlist = NumRec(num);//数字分割提取

	for (int j = 0; j < numlist->length; j++)
	{
		IplImage* num1 = cvCreateImage(cvGetSize(numlist->num[j]), IPL_DEPTH_8U, 3);
		if ((num1->width == 15) && (num1->height == 20))//如果IPL图像尺寸是15*20，那么这个矩阵包含的是1
		{
			IplImage* standardsize = cvCreateImage(cvSize(17, 34), IPL_DEPTH_8U, 3);
			for (int i = 0; i < standardsize->height; i++)
			{
				for (int j = 0; j < 3 * standardsize->width; j++)
				{
					*(standardsize->imageData + standardsize->widthStep*i + j) = 255;//遍历元素，均变成白色
				}
			}
			numlist->num[j] = standardsize;
		}
		else {
			IplImage* standardsize = cvCreateImage(cvSize(17, 34), IPL_DEPTH_8U, 3);
			cvResize(numlist->num[j], standardsize);//转化成统一规格的大小17*34
			numlist->num[j] = standardsize;
		}
	}
	//cvWaitKey(2);
	//cvSaveImage("province\\京.jpg", numlist->num[0]);
	//cvSaveImage("C:\\Users\\sony\\Desktop\\17 34\\H.jpg", numlist->num[1]);
	//cvSaveImage("C:\\Users\\sony\\Desktop\\17 34\\R.jpg", numlist->num[2]);
	//cvSaveImage("C:\\Users\\sony\\Desktop\\17 34\\J.jpg", numlist->num[3]);
	//cvSaveImage("C:\\Users\\sony\\Desktop\\17 34\\1.jpg", numlist->num[4]);
	//cvSaveImage("C:\\Users\\sony\\Desktop\\17 34\\3.jpg", numlist->num[5]);
	//cvSaveImage("C:\\Users\\sony\\Desktop\\17 34\\D.jpg", numlist->num[6]);

	ThresList* province = (ThresList*)malloc(sizeof(ThresList));
	InitThresList(province);
	IplImage* province0 = cvLoadImage("province\\鄂.jpg");
	IplImage* province1 = cvLoadImage("province\\沪.jpg");
	IplImage* province2 = cvLoadImage("province\\冀.jpg");
	IplImage* province3 = cvLoadImage("province\\津.jpg");
	IplImage* province4 = cvLoadImage("province\\晋.jpg");
	IplImage* province5 = cvLoadImage("province\\京.jpg");
	IplImage* province6 = cvLoadImage("province\\辽.jpg");
	IplImage* province7 = cvLoadImage("province\\鲁.jpg");
	IplImage* province8 = cvLoadImage("province\\闽.jpg");
	IplImage* province9 = cvLoadImage("province\\湘.jpg");
	IplImage* province10 = cvLoadImage("province\\渝.jpg");
	IplImage* province11 = cvLoadImage("province\\豫.jpg");
	IplImage* province12 = cvLoadImage("province\\粤.jpg");
	IplImage* province13 = cvLoadImage("province\\云.jpg");
	IplImage* province14 = cvLoadImage("province\\浙.jpg");
	AddThresToList(province, province0);
	AddThresToList(province, province1);
	AddThresToList(province, province2);
	AddThresToList(province, province3);
	AddThresToList(province, province4);
	AddThresToList(province, province5);
	AddThresToList(province, province6);
	AddThresToList(province, province7);
	AddThresToList(province, province8);
	AddThresToList(province, province9);
	AddThresToList(province, province10);
	AddThresToList(province, province11);
	AddThresToList(province, province12);
	AddThresToList(province, province13);
	AddThresToList(province, province14);
	IplImage* thresprovince = SmoothBinary(numlist->num[0]);
	cvThreshold(thresprovince, thresprovince, 0, 255, CV_THRESH_OTSU);

	CString str;

	int s = ProvinceMatch(thresprovince, province);
	switch (s)
	{
	case 0:str.AppendFormat(_T("鄂")); break;
	case 1:str.AppendFormat(_T("沪")); break;
	case 2:str.AppendFormat(_T("冀")); break;
	case 3:str.AppendFormat(_T("津")); break;
	case 4:str.AppendFormat(_T("晋")); break;
	case 5:str.AppendFormat(_T("京")); break;
	case 6:str.AppendFormat(_T("辽")); break;
	case 7:str.AppendFormat(_T("鲁")); break;
	case 8:str.AppendFormat(_T("闽")); break;
	case 9:str.AppendFormat(_T("湘")); break;
	case 10:str.AppendFormat(_T("渝")); break;
	case 11:str.AppendFormat(_T("豫")); break;
	case 12:str.AppendFormat(_T("粤")); break;
	case 13:str.AppendFormat(_T("云")); break;
	case 14:str.AppendFormat(_T("浙")); break;
	}


	IplImage* num0 = cvLoadImage("num\\0.jpg");
	IplImage* num1 = cvLoadImage("num\\1.jpg");
	IplImage* num2 = cvLoadImage("num\\2.jpg");
	IplImage* num3 = cvLoadImage("num\\3.jpg");
	IplImage* num4 = cvLoadImage("num\\4.jpg");
	IplImage* num5 = cvLoadImage("num\\5.jpg");
	IplImage* num6 = cvLoadImage("num\\6.jpg");
	IplImage* num7 = cvLoadImage("num\\7.jpg");
	IplImage* num8 = cvLoadImage("num\\8.jpg");
	IplImage* num9 = cvLoadImage("num\\9.jpg");
	IplImage* A = cvLoadImage("num\\A.jpg");
	IplImage* B = cvLoadImage("num\\B.jpg");
	IplImage* C = cvLoadImage("num\\C.jpg");
	IplImage* D = cvLoadImage("num\\D.jpg");
	IplImage* E = cvLoadImage("num\\E.jpg");
	IplImage* F = cvLoadImage("num\\F.jpg");
	IplImage* G = cvLoadImage("num\\G.jpg");
	IplImage* H = cvLoadImage("num\\H.jpg");
	//IplImage* I = cvLoadImage("num\\9.jpg");
	IplImage* J = cvLoadImage("num\\J.jpg");
	IplImage* K = cvLoadImage("num\\K.jpg");
	IplImage* L = cvLoadImage("num\\L.jpg");
	IplImage* M = cvLoadImage("num\\M.jpg");
	IplImage* N = cvLoadImage("num\\N.jpg");
	//IplImage* O = cvLoadImage("num\\9.jpg");
	IplImage* P = cvLoadImage("num\\P.jpg");
	IplImage* Q = cvLoadImage("num\\Q.jpg");
	IplImage* R = cvLoadImage("num\\R.jpg");
	IplImage* S = cvLoadImage("num\\S.jpg");
	IplImage* T = cvLoadImage("num\\T.jpg");
	IplImage* U = cvLoadImage("num\\U.jpg");
	IplImage* V = cvLoadImage("num\\V.jpg");
	IplImage* W = cvLoadImage("num\\W.jpg");
	IplImage* X = cvLoadImage("num\\X.jpg");
	IplImage* Y = cvLoadImage("num\\Y.jpg");
	IplImage* Z = cvLoadImage("num\\Z.jpg");
	ThresList* standard = (ThresList*)malloc(sizeof(ThresList));
	InitThresList(standard);
	AddThresToList(standard, num0);
	AddThresToList(standard, num1);
	AddThresToList(standard, num2);
	AddThresToList(standard, num3);
	AddThresToList(standard, num4);
	AddThresToList(standard, num5);
	AddThresToList(standard, num6);
	AddThresToList(standard, num7);
	AddThresToList(standard, num8);
	AddThresToList(standard, num9);
	AddThresToList(standard, A);
	AddThresToList(standard, B);
	AddThresToList(standard, C);
	AddThresToList(standard, D);
	AddThresToList(standard, E);
	AddThresToList(standard, F);
	AddThresToList(standard, G);
	AddThresToList(standard, H);
	standard->num[18] = 0;
	standard->length++; //Attention:车牌上没有I只有1！
	AddThresToList(standard, J);
	AddThresToList(standard, K);
	AddThresToList(standard, L);
	AddThresToList(standard, M);
	AddThresToList(standard, N);
	standard->num[24] = 0;
	standard->length++; //车牌没有O
	AddThresToList(standard, P);
	AddThresToList(standard, Q);
	AddThresToList(standard, R);
	AddThresToList(standard, S);
	AddThresToList(standard, T);
	AddThresToList(standard, U);
	AddThresToList(standard, V);
	AddThresToList(standard, W);
	AddThresToList(standard, X);
	AddThresToList(standard, Y);
	AddThresToList(standard, Z);//加载所有的数字字母模板

	//显示
	ShowImage(numlist->num[0], IDC_STATIC_N0);
	ShowImage(numlist->num[1], IDC_STATIC_N1);
	ShowImage(numlist->num[2], IDC_STATIC_N2);
	ShowImage(numlist->num[3], IDC_STATIC_N3);
	ShowImage(numlist->num[4], IDC_STATIC_N4);
	ShowImage(numlist->num[5], IDC_STATIC_N5);
	ShowImage(numlist->num[6], IDC_STATIC_N6);
	for (int i = 1; i < numlist->length; i++)
	{
		IplImage* thresnum = cvCreateImage(cvGetSize(numlist->num[i]), IPL_DEPTH_8U, 1);
		thresnum = SmoothBinary(numlist->num[i]);
		cvThreshold(thresnum, thresnum, 0, 255, CV_THRESH_OTSU);
		int pos = PointMatch(thresnum, standard);
		//打印数字
		if (pos < 10)
		{
			str.AppendFormat(_T("%d"), pos);
		}
		//打印字母
		if (pos >= 10)
		{
			str.AppendFormat(_T("%c"), pos + 55);
		}
		cvReleaseImage(&thresnum);
	}
	m_edit1.SetWindowTextW(str);
}


void CCarPlateMFCDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
