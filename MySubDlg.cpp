// MySubDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "MySubDlg.h"
#include "afxdialogex.h"


// CMySubDlg 对话框

IMPLEMENT_DYNAMIC(CMySubDlg, CDialogEx)

CMySubDlg::CMySubDlg(UINT nIDTemplate , CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{

}

CMySubDlg::~CMySubDlg()
{
}

void CMySubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
}


BEGIN_MESSAGE_MAP(CMySubDlg, CDialogEx)
//	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CMySubDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CMySubDlg 消息处理程序


void CMySubDlg::OnPaint()
{
	CClientDC dc(this); // device context for painting
	// 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_MAINBG);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	CFont *m_Font;
	m_Font = new CFont;
	m_Font->CreatePointFont(400, CString("黑体"), NULL);
	dc.SelectObject(m_Font);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(100, 40, tittle);
	delete m_Font;
	DeleteDC(dc);
}

void CMySubDlg::SetTittle(CString t)
{
	tittle = t;
}

BOOL CMySubDlg::PreTranslateMessage(MSG* pMsg)
{
	// 在此添加专用代码和/或调用基类

	//TODO: 完成后去注释
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	//屏蔽Return
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}




BOOL CMySubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	// TODO: 绘制返回图标
	//CMyButton* b = (CMyButton*)GetDlgItem(IDC_BUTTON_BACK);
	//m_back.SetBitmaps(IDB_BITMAP_BROWSE, IDB_BITMAP_BROWSE_SELECT, IDB_BITMAP_BROWSE_FOCUS);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CMySubDlg::OnBnClickedButtonBack()
{
	OnOK();
}

void CMySubDlg::paintbg(CPaintDC *dc){
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	dcMem.CreateCompatibleDC(dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_MAINBG);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc->SetStretchBltMode(COLORONCOLOR);
	dc->StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	CFont *m_Font;
	m_Font = new CFont;
	m_Font->CreatePointFont(400, CString("黑体"), NULL);
	dc->SelectObject(m_Font);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(255, 255, 255));
	dc->TextOut(100, 40, tittle);
	delete m_Font;
	
}