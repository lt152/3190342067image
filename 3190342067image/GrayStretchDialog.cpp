// GrayStretchDialog.cpp: 实现文件
//

#include "pch.h"
#include "3190342067image.h"
#include "afxdialogex.h"
#include "GrayStretchDialog.h"


// GrayStretchDialog 对话框

IMPLEMENT_DYNAMIC(GrayStretchDialog, CDialog)

GrayStretchDialog::GrayStretchDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_X1(0)
	, m_X2(0)
	, m_Y1(0)
	, m_Y2(0)
{

}

GrayStretchDialog::~GrayStretchDialog()
{
}

void GrayStretchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_X1);
	DDV_MinMaxInt(pDX, m_X1, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, m_X2);
	DDV_MinMaxInt(pDX, m_X2, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, m_Y1);
	DDV_MinMaxInt(pDX, m_Y1, 0, 255);
	DDX_Text(pDX, IDC_EDIT4, m_Y2);
	DDV_MinMaxInt(pDX, m_Y2, 0, 255);
}


BEGIN_MESSAGE_MAP(GrayStretchDialog, CDialog)
	ON_BN_CLICKED(IDC_refresh, &GrayStretchDialog::OnClickedRefresh)
	ON_BN_CLICKED(IDOK, &GrayStretchDialog::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// GrayStretchDialog 消息处理程序


void GrayStretchDialog::OnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	//2022/4/29刷新视口
	UpdateData(TRUE);
	if (m_X1 > 255 || m_X1 < 0 || m_Y1>255 || m_Y1 < 0 || m_X2>255 || m_X2 < 0 || m_Y2>255 || m_Y2 < 0) {
		MessageBox("所输入的坐标超出(0,255)，请重新输入！");
	}
	else {
		Invalidate(TRUE);
	}
}


void GrayStretchDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void GrayStretchDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()

	CString str;

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_paint);

	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 320, 300);

	// 创建画笔对象
	CPen* pPenRed = new CPen;

	// 红色画笔
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	// 创建画笔对象
	CPen* pPenBlue = new CPen;

	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10, 10);

	// 垂直轴
	pDC->LineTo(10, 280);

	// 水平轴
	pDC->LineTo(320, 280);

	// 写坐标
	str.Format("0");
	pDC->TextOut(10, 281, str);

	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);

	// 绘制X轴箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);

	// 绘制X轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 绘制坐标值
	str.Format("(%d, %d)", m_X1, m_Y1);
	pDC->TextOut(m_X1 + 10, 281 - m_Y1, str);
	str.Format("(%d, %d)", m_X2, m_Y2);
	pDC->TextOut(m_X2 + 10, 281 - m_Y2, str);

	// 绘制用户指定的变换直线
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_X1 + 10, 280 - m_Y1);
	pDC->LineTo(m_X2 + 10, 280 - m_Y2);
	pDC->LineTo(265, 25);

	// 绘制点边缘的小矩形
	CBrush  brush;
	brush.CreateSolidBrush(RGB(0, 255, 0));

	// 选中刷子
	CGdiObject* pOldBrush = pDC->SelectObject(&brush);

	// 绘制小矩形
	pDC->Rectangle(m_X1 + 10 - 2, 280 - m_Y1 - 2, m_X1 + 12, 280 - m_Y1 + 2);
	pDC->Rectangle(m_X2 + 10 - 2, 280 - m_Y2 - 2, m_X2 + 12, 280 - m_Y2 + 2);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
}
