// MySubDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "MySubDlg.h"
#include "afxdialogex.h"


// CMySubDlg �Ի���

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


// CMySubDlg ��Ϣ�������


void CMySubDlg::OnPaint()
{
	CClientDC dc(this); // device context for painting
	// �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	m_Font->CreatePointFont(400, CString("����"), NULL);
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
	// �ڴ����ר�ô����/����û���

	//TODO: ��ɺ�ȥע��
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	//����Return
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}




BOOL CMySubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	// TODO: ���Ʒ���ͼ��
	//CMyButton* b = (CMyButton*)GetDlgItem(IDC_BUTTON_BACK);
	//m_back.SetBitmaps(IDB_BITMAP_BROWSE, IDB_BITMAP_BROWSE_SELECT, IDB_BITMAP_BROWSE_FOCUS);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	m_Font->CreatePointFont(400, CString("����"), NULL);
	dc->SelectObject(m_Font);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(255, 255, 255));
	dc->TextOut(100, 40, tittle);
	delete m_Font;
	
}