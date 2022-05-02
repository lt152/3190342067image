
// 3190342067imageView.h: CMy3190342067imageView 类的接口
//

#pragma once




class CMy3190342067imageView : public CView
{
protected: // 仅从序列化创建
	CMy3190342067imageView() noexcept;
	DECLARE_DYNCREATE(CMy3190342067imageView)

// 特性
public:
	CMy3190342067imageDoc* GetDocument() const;
	unsigned char	ImageRAW[RAW][LINE], ImageBMP[RAW][LINE], ImageTran[RAW][LINE];
	CString		m_strName;
	CString		m_strPath;
	void ShowName(CDC* pDC);	//显示姓名学号
	
	void OnBmpShow(CDC* pDC);	//显示bmp图像
	void onGrayShow(CDC* pDC);
	int State;	//状态标志

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMy3190342067imageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Onopencvopen();
	afx_msg void Onbmptoraw();
	afx_msg void OnGray();
};

#ifndef _DEBUG  // 3190342067imageView.cpp 中的调试版本
inline CMy3190342067imageDoc* CMy3190342067imageView::GetDocument() const
   { return reinterpret_cast<CMy3190342067imageDoc*>(m_pDocument); }
#endif

