
// Rectangle.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRectangleApp: 
// �йش����ʵ�֣������ Rectangle.cpp
//

class CRectangleApp : public CWinApp
{
public:
	CRectangleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRectangleApp theApp;