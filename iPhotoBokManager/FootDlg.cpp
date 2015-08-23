// FootDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "FootDlg.h"
#include "afxdialogex.h"
#include <list>


// CFootDlg 对话框

IMPLEMENT_DYNAMIC(CFootDlg, CDialogEx)

CFootDlg::CFootDlg(CWnd* pParent /*=NULL*/)
	: CMySubDlg(CFootDlg::IDD, pParent)
{

}

CFootDlg::~CFootDlg()
{
}

void CFootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SWITCH, m_switch);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
}


BEGIN_MESSAGE_MAP(CFootDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CFootDlg::OnBnClickedButtonSwitch)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CFootDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CFootDlg 消息处理程序


void CFootDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	if(!cur)	bmpBackground.LoadBitmap(IDB_BITMAP_ECNU);
	else		bmpBackground.LoadBitmap(IDB_BITMAP_CHINA);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	
	list<int>l;
	int nans=album.graph(cur).size();
	int t;
	album.foodPrint(map[cur], t, l);
	int x, y;
	for (int i = 0; i < nans; i++){
		GraphInfo g = album.graph(cur).at(i);
		if (cur == 1){
			x = (g.getX() - 25)*rate;
			y = (g.getY() - 20)*rate;
		}
		else{
			x = (g.getX() - 0)*rate;
			y = (g.getY() - 0)*rate;
		}
		CBrush brush;
		brush.CreateSolidBrush(RGB(86, 35, 144));
		dc.SelectObject(brush);

		dc.Ellipse(x - 5, y - 5, x + 5, y + 5);

		list<int>t;
		int npos;
		album.findByPosition(g.getName(), npos, t);
		CString size;
		size.Format(_T("%d"), npos);
		dc.SetBkColor(RGB(172, 222, 231));
		dc.SetTextColor(RGB(25, 40, 91));
		if (npos)	dc.TextOut(x, y + 3, size);
	}

}


BOOL CFootDlg::OnInitDialog()
{
	//CMySubDlg::OnInitDialog();
	dlg = NULL;
	map[0] = "中国";
	map[1] = "华师大";
	SetWindowText(CString("足迹") + _T(" - iPhotoBook"));
	init(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CFootDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	KillTimer(1001);
	//if (dlg != nullptr&&dlg->IsWindowVisible()){
	//	dlg->ShowWindow(SW_HIDE);
		//MessageBox(CString(_T("隐藏")));
	//}
	SetTimer(1001, 500, NULL);
	CMySubDlg::OnMouseMove(nFlags, point);
}


void CFootDlg::OnTimer(UINT_PTR nIDEvent)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	int min = -1;
	int nans = album.graph(cur).size();
	double dmin = 1e10;
	int x, y;
	for (int i = 0; i < nans; i++){
		GraphInfo g = album.graph(cur).at(i);
		if (cur == 1){
			x = (g.getX() - 25)*rate;
			y = (g.getY() - 20)*rate;
		}
		else{
			x = (g.getX() - 0)*rate;
			y = (g.getY() - 0)*rate;
		}
		double r = sqrt((x - point.x)*(x - point.x) + (y - point.y)*(y - point.y));
		if (r < dmin){
			dmin = r;
			min = i;
		}
	}
	if (dmin < 20){
		KillTimer(1001);
		ClientToScreen(&point);
		dlg = new CFootDetailDlg(NULL, point, cur, min);
		dlg->DoModal();
		SetTimer(1001, 500, NULL);
	}

	CMySubDlg::OnTimer(nIDEvent);
}

void CFootDlg::init(int k)
{
	cur = k;
	rate = 1;
	CRect   temprect;
	if (!cur)	temprect = CRect(48, 48, 788 * rate, 726 * rate);
	else		temprect = CRect(48, 48, 800 * rate, 667 * rate);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width()*rate, temprect.Height()*rate, SWP_NOZORDER | SWP_NOMOVE);
	ScreenToClient(&temprect);
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_BUTTON_SWITCH);
	pWnd->MoveWindow(temprect.Width()*rate - 50, temprect.Height()*rate - 50, 48, 48);
	
	pWnd = GetDlgItem(IDC_BUTTON_BACK);
	pWnd->MoveWindow(temprect.Width()*rate - 100, temprect.Height()*rate - 50, 48, 48);

	SetTimer(1001, 500, NULL);
}

void CFootDlg::OnBnClickedButtonSwitch()
{
	cur = !cur;
	init(cur);
	Invalidate();
}


void CFootDlg::OnBnClickedButtonBack()
{
	OnCancel();
}
