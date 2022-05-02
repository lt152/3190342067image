#pragma once
#include "afxdialogex.h"


// GrayStretchDialog 对话框

class GrayStretchDialog : public CDialog
{
	DECLARE_DYNAMIC(GrayStretchDialog)

public:
	GrayStretchDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GrayStretchDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_X1;
	int m_X2;
	int m_Y1;
	int m_Y2;
	afx_msg void OnClickedRefresh();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
};
