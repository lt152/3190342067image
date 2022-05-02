
// 3190342067imageView.cpp: CMy3190342067imageView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "3190342067image.h"
#endif

#include "3190342067imageDoc.h"
#include "3190342067imageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3190342067imageView

IMPLEMENT_DYNCREATE(CMy3190342067imageView, CView)

BEGIN_MESSAGE_MAP(CMy3190342067imageView, CView)
	ON_COMMAND(ID_opencvOpen, &CMy3190342067imageView::Onopencvopen)
	ON_COMMAND(ID_bmptoRaw, &CMy3190342067imageView::Onbmptoraw)
	ON_COMMAND(ID_Gray, &CMy3190342067imageView::OnGray)
END_MESSAGE_MAP()

// CMy3190342067imageView 构造/析构

CMy3190342067imageView::CMy3190342067imageView() noexcept
{
	// TODO: 在此处添加构造代码
	State = 0;

}




CMy3190342067imageView::~CMy3190342067imageView()
{
}

BOOL CMy3190342067imageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy3190342067imageView 绘图

void CMy3190342067imageView::OnDraw(CDC* pDC)
{
	CMy3190342067imageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码


	ShowName(pDC);
	if (State == 1) OnBmpShow(pDC);
	if (State == 2) onGrayShow(pDC);
	
}


// CMy3190342067imageView 诊断

#ifdef _DEBUG
void CMy3190342067imageView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3190342067imageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3190342067imageDoc* CMy3190342067imageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3190342067imageDoc)));
	return (CMy3190342067imageDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3190342067imageView 消息处理程序
void CMy3190342067imageView::ShowName(CDC* pDC)
{
	pDC->TextOut(800, 200, "3190342067 李腾");
}

void CMy3190342067imageView::OnBmpShow(CDC* pDC)
{
	int i, j;
	for (i = 0; i < RAW; i++)//显示图像
	{
		for (j = 0; j < LINE; j++)
		{
			pDC->SetPixel(j + 280, i + 10, RGB(ImageBMP[i][j], ImageBMP[i][j], ImageBMP[i][j]));
			pDC->SetPixel(j + 10, i + 10, RGB(ImageRAW[i][j], ImageRAW[i][j], ImageRAW[i][j]));
		}
	}
	pDC->TextOut(100, 280, "BMP图");
	pDC->TextOut(400, 280, "RAW图");
}

void CMy3190342067imageView::onGrayShow(CDC* pDC)
{
	int i, j;
	for (i = 0; i < RAW; i++)//显示图像
	{
		for (j = 0; j < LINE; j++)
		{
			pDC->SetPixel(j + 10, i + 10, RGB(ImageRAW[i][j],
				ImageRAW[i][j], ImageRAW[i][j]));
			pDC->SetPixel(j + 280, i + 10, RGB(ImageTran[i][j],
				ImageTran[i][j], ImageTran[i][j]));
		}
	}
	pDC->TextOut(100, 280, "原图");
	pDC->TextOut(400, 280, "转换后");
}


void CMy3190342067imageView::Onopencvopen()
{
	// TODO: 在此添加命令处理程序代码
	IplImage* pImg;
	Mat mat;
	State = 0;
	Invalidate(TRUE);
	CFileDialog file(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL, AfxGetMainWnd());
	if (IDOK == file.DoModal())    //若打开文件成功
	{
		m_strPath = file.GetPathName();
		mat = imread(m_strPath.GetBuffer(), 1);//CString转化String

		//namedWindow("实验一 opencv显示图片", 1);
		//cvShowImage("实验一 opencv显示图片", pImg);
		/////////////////////////
		//////////
		imshow("实验一 opencv显示图片", mat);
		////////////////////
		cvWaitKey(0);
		//cvReleaseImage(&pImg);
		cvDestroyWindow("实验一 opencv显示图片");
	}
}


void CMy3190342067imageView::Onbmptoraw()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog file(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"bmp Files (*.bmp)|*.bmp", AfxGetMainWnd());
	if (IDOK == file.DoModal())    //若打开文件成功
	{
		long		lOffset;
		m_strPath = file.GetPathName();
		FILE* fp;
		if ((fp = fopen(m_strPath, "rb")) != 0)
		{
			fseek(fp, 0xa, SEEK_SET);
			fread(&lOffset, 4, 1, fp);
			fseek(fp, lOffset, SEEK_SET);
			fread(ImageBMP, 1, RAW * LINE, fp);
			fclose(fp);
			////////////////////////////////
			int	nTemp = RAW;
			for (int i = 0; i < RAW; i++)
			{
				for (int j = 0; j < LINE; j++)
				{
					ImageRAW[i][j] = ImageBMP[nTemp - 1][j];
				}
				nTemp--;
			}
			/////////////////////////////////
			//存储的文件名
			m_strName = "liteng.raw";
			if ((fp = fopen(m_strName, "wb")) != 0)
			{
				fwrite(ImageRAW, 1, RAW * LINE, fp);
				fclose(fp);
			}
			else
			{
				MessageBox("不能打开文件用于存储!!!");
				return;
			}
		}
		else
		{
			MessageBox("不能打开文件用于读取!!!");
			return;
		}
		State = 1;	//设置显示状态
	}
	Invalidate(TRUE);
}


void CMy3190342067imageView::OnGray()
{
	// TODO: 在此添加命令处理程序代码
	GrayStretchDialog gsd;
	//BMPtoRAW
	FILE* fp;
	CFileDialog file(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp Files (*.bmp)|*.bmp", AfxGetMainWnd());

	if (IDOK == file.DoModal())    //若打开文件成功
	{
		long lOffset;
		m_strPath = file.GetPathName();
		if ((fp = fopen(m_strPath, "rb")) != 0)
		{
			fseek(fp, 10L, SEEK_SET);
			fread(&lOffset, 4, 1, fp);
			fseek(fp, lOffset, SEEK_SET);
			fread(ImageBMP, 1, RAW * LINE, fp);
			fclose(fp); int	nTemp = RAW;
			for (int i = 0; i < RAW; i++)
			{
				for (int j = 0; j < LINE; j++)
				{
					ImageRAW[i][j] = ImageBMP[nTemp - 1][j];
					ImageTran[i][j] = ImageBMP[nTemp - 1][j];
				}
				nTemp--;
			}
			m_strName = "我的图片.raw";//存储的文件名
			if ((fp = fopen(m_strName, "wb")) != 0)
			{
				fwrite(ImageRAW, 1, RAW * LINE, fp); fclose(fp);
			}
			else { MessageBox("不能打开文件用于存储!!!"); return; }
		}
		else
		{
			MessageBox("不能打开文件用于读取!!!");
			return;
		}
	}
	Invalidate(TRUE);
	int i, j;
	long X1, X2, Y1, Y2, a, b;
	float fAlfa, fBata, fGama;
	if (gsd.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		X1 = gsd.m_X1;
		Y1 = gsd.m_Y1;
		X2 = gsd.m_X2;
		Y2 = gsd.m_Y2;

		//判断所输入坐标是否满足在(0--255)范围内
		if (((X1 > 0) && (X1 < 255)) && ((X2 > 0) && (X2 < 255)) && ((Y1 > 0) && (Y1 < 255)) && ((Y2 > 0) && (Y2 < 255)) && (X1 <= X2))
		{
			fAlfa = float(Y1) / float(X1);
			if (X1 != X2)
			{
				fBata = float(Y2 - Y1) / float(X2 - X1);
			}
			else
			{
				fBata = 0;
			}
			fGama = float(255 - Y2) / float(255 - X2);
			a = X1;
			b = X2;

			//进行灰度拉伸
			for (i = 0; i < RAW; i++)
			{
				for (j = 0; j < LINE; j++)
				{
					if (ImageRAW[i][j] >= 0 && ImageRAW[i][j] < a)
					{
						ImageTran[i][j] = int(fAlfa * ImageRAW[i][j]);
					}
					else
					{
						if (ImageRAW[i][j] >= a && ImageRAW[i][j] < b)
						{
							ImageTran[i][j] = int(fBata * (ImageRAW[i][j] - a) + fAlfa * a);
						}
						else
						{
							if (ImageRAW[i][j] >= b && ImageRAW[i][j] < 256)
							{
								ImageTran[i][j] = int(fGama * (ImageRAW[i][j] - b) + (fBata * (b - a) + fAlfa * a));
							}
						}

					}
				}
			}
		}
	}
	State = 2;
	Invalidate(TRUE);
	m_strName = "我的图片.raw";
	if ((fp = fopen(m_strName, "wb")) != 0)
	{
		fwrite(ImageTran, 1, RAW * LINE, fp);
		fclose(fp);
	}
}
