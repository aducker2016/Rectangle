
// RectangleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Rectangle.h"
#include "RectangleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRectangleDlg 对话框



CRectangleDlg::CRectangleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRectangleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRectangleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRectangleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CRectangleDlg::OnBnClickedButtonGenerate)
END_MESSAGE_MAP()


// CRectangleDlg 消息处理程序

BOOL CRectangleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CRect rcW;
	GetWindowRect(&rcW);
	CRect rcC;
	GetClientRect(&rcC);
	MoveWindow(0, 0, 800 + rcW.Width() - rcC.Width(), 800 + 30 + rcW.Height() - rcC.Height());

	ModifyStyle(0, WS_CLIPCHILDREN);

	m_draw.Create(IDD_DIALOG_DRAW);
	m_draw.MoveWindow(0, 30, 800, 800);

	GetDlgItem(IDC_STATIC_1)->MoveWindow(238, 6, 60, 22);
	GetDlgItem(IDC_EDIT_X)->MoveWindow(300, 4, 50, 22);
	GetDlgItem(IDC_STATIC_2)->MoveWindow(365, 6, 15, 22);
	GetDlgItem(IDC_EDIT_Y)->MoveWindow(380, 4, 50, 22);
	GetDlgItem(IDC_STATIC_3)->MoveWindow(445, 6, 15, 22);
	GetDlgItem(IDC_EDIT_HEIGHT)->MoveWindow(460, 4, 50, 22);
	GetDlgItem(IDC_STATIC_4)->MoveWindow(525, 6, 15, 22);
	GetDlgItem(IDC_EDIT_WIDTH)->MoveWindow(540, 4, 50, 22);
	GetDlgItem(IDC_BUTTON_GENERATE)->MoveWindow(600, 2, 198, 26);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRectangleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRectangleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRectangleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRectangleDlg::OnBnClickedButtonGenerate()
{
	// TODO:  在此添加控件通知处理程序代码
	int MAX_X = 80, MAX_Y = 80;
	std::vector<std::vector<int> >& nodes = m_draw.m_nodes;
	nodes.resize(MAX_X);
	for (int x = 0; x < MAX_X; x++)
	{
		nodes[x].resize(MAX_Y);
	}

	//已知点
	CString str;
	GetDlgItem(IDC_EDIT_X)->GetWindowText(str);
	double targetX = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(str);
	double targetY = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_HEIGHT)->GetWindowText(str);
	double height = _ttoi(str.GetBuffer());
	GetDlgItem(IDC_EDIT_WIDTH)->GetWindowText(str);
	double width = _ttoi(str.GetBuffer());

	if ((targetX == 0 && targetY == 0) || height <= 0 || width <= 0)
	{
		return;
	}

	//判断点是否在矩形内部（数组中的所有点，每个都判断）
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			//判断点
			double checkX = x - MAX_X / 2;
			double checkY = -y + MAX_Y / 2;

			//判断点在中轴线上的投影
			double temp = (checkX * targetX + checkY * targetY) / (pow(targetX, 2) + pow(targetY, 2));
			double shadowX = temp * targetX;
			double shadowY = temp * targetY;

			//判断点到中轴线的距离
			double disX = checkX - shadowX;
			double disY = checkY - shadowY;

			if (temp >= 0 &&
				pow(shadowX, 2) + pow(shadowY, 2) <= pow(height, 2) &&
				pow(disX, 2) + pow(disY, 2) <= pow(width, 2))
			{
				//矩形内
				nodes[x][y] = 1;
			}
			else
			{
				//矩形外
				nodes[x][y] = 0;
			}

			if (checkX == 0 && checkY == 0)
			{
				//原点
				nodes[x][y] = 2;
			}
			else if (checkX == targetX && checkY == targetY)
			{
				//目标点
				nodes[x][y] = 3;
			}
		}
	}

	m_draw.Invalidate();
}
