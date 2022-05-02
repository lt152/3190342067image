
// 3190342067image.h: 3190342067image 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号

///////////////////////////////////
#include "GrayStretchDialog.h"//////////////////////////////
//opencv库
#include<opencv2/opencv.hpp>
#include"highgui.hpp"
#include"opencv2/imgproc/imgproc_c.h"
#include <opencv2/highgui/highgui_c.h>

#define RAW 256                 
#define LINE 256

using namespace cv;

// CMy319342067imageApp:
// 有关此类的实现，请参阅 3190342067image.cpp
//

class CMy3190342067imageApp : public CWinApp
{
public:
	CMy3190342067imageApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3190342067imageApp theApp;
