
// MouseEventDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MouseEvent.h"
#include "MouseEventDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMouseEventDlg �Ի���



CMouseEventDlg::CMouseEventDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOUSEEVENT_DIALOG, pParent)
	, m_StartDraw(false)
	, m_PrevPoint(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMouseEventDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMouseEventDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMouseEventDlg ��Ϣ��������

BOOL CMouseEventDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMouseEventDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMouseEventDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMouseEventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseEventDlg::OnBnClickedButton1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CWnd *pCanvasWnd = GetDlgItem(IDC_CANVAS);
	CDC *pDC = pCanvasWnd->GetDC();
	CRect rect; 
	pCanvasWnd->GetClientRect(&rect);
	rect.left += 1;
	rect.right -= 1;
	rect.top += 1;
	rect.bottom -= 1;
	CBrush brush;
	auto bkColor = pDC->GetBkColor();
	auto r = GetRValue(bkColor);
	auto g = GetGValue(bkColor);
	auto b = GetBValue(bkColor);
	auto color = RGB(r, g, b);
	brush.CreateSolidBrush(RGB(r, g, b));
	pDC->FillRect(&rect, &brush);
}


void CMouseEventDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	CWnd *pCanvasWnd = GetDlgItem(IDC_CANVAS);
	CRect rect;
	pCanvasWnd->GetWindowRect(&rect);
	ScreenToClient(rect);
	CPoint p(rect.left, rect.top);
	m_PrevPoint = point - p;
	m_StartDraw = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMouseEventDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	m_StartDraw = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMouseEventDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (m_StartDraw == true)
	{
		CWnd *pCanvasWnd = GetDlgItem(IDC_CANVAS);
		CDC *pDC = pCanvasWnd->GetDC();
		CRect rect;
		pCanvasWnd->GetClientRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		pCanvasWnd->GetWindowRect(&rect);
		ScreenToClient(rect);
		CPoint p(rect.left, rect.top);

		CPoint prevPoint, currPoint;
		prevPoint = m_PrevPoint;
		currPoint = point - p;
		if ((prevPoint.x > 0) && (prevPoint.x < width) &&
			(prevPoint.y > 0) && (prevPoint.y < height) &&
			(currPoint.x > 0) && (currPoint.x < width) &&
			(currPoint.y > 0) && (currPoint.y < height))
		{
			pDC->MoveTo(prevPoint);
			pDC->LineTo(currPoint);
		}
		//ReleaseDC(pDC);
		pDC->Detach();
		pCanvasWnd->Detach();
		m_PrevPoint = currPoint;
	}
	CDialogEx::OnMouseMove(nFlags, point);
}