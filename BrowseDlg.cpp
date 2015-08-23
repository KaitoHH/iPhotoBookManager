// BrowseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "BrowseDlg.h"
#include "afxdialogex.h"
#include "math.h"

// CBrowseDlg 对话框

IMPLEMENT_DYNAMIC(CBrowseDlg, CDialogEx)

CBrowseDlg::CBrowseDlg(CWnd* pParent /*=NULL*/)
	: CMySubDlg(CBrowseDlg::IDD, pParent)
{
	pos = 0;
}

CBrowseDlg::CBrowseDlg(CWnd* pParent /*=NULL*/,int pos)
	: CMySubDlg(CBrowseDlg::IDD, pParent)
{
	this->pos = pos;
}

CBrowseDlg::~CBrowseDlg()
{
}

void CBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
	DDX_Control(pDX, IDC_PIC1, m_pic1);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Control(pDX, ID_PIC3, m_pic3);
	DDX_Control(pDX, ID_PIC4, m_pic4);
	DDX_Control(pDX, IDC_BUTTON_NXT, m_next);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_pre);
}


BEGIN_MESSAGE_MAP(CBrowseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CBrowseDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &CBrowseDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_NXT, &CBrowseDlg::OnBnClickedButtonNxt)
	ON_BN_CLICKED(IDC_BUTTON3, &CBrowseDlg::OnBnClickedButton3)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CBrowseDlg 消息处理程序


void CBrowseDlg::OnPaint()
{
	CPaintDC dc(this);
	CMySubDlg::SetTittle(CString("浏览"));
	paintbg(&dc);

	//当前页刷新
	CFont *m_font = new CFont;
	CRect rect;
	CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT_PAGE);
	m_edit->SetLimitText(3);
	m_edit->GetWindowRect(rect);
	m_font->CreatePointFont(300, CString("黑体"), NULL);
	m_edit->SetFont(m_font, TRUE);

	//总页数刷新
	CStatic *m_static = (CStatic*)GetDlgItem(IDC_STATIC_ALL);
	m_static->GetWindowRect(rect);
	m_static->SetFont(m_font, TRUE);
	SetDlgItemInt(IDC_STATIC_ALL, pages);

	//图像控件刷新
	drawPicture(&m_pic1, 0);
	drawPicture(&m_pic2, 1);
	drawPicture(&m_pic3, 2);
	drawPicture(&m_pic4, 3);
	
	//静态文字
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont *m_Font = new CFont;
	m_Font->CreatePointFont(175, CString("微软雅黑"), NULL);
	dc.SelectObject(m_Font);
	dc.TextOut(1200, 550, CString("当前"));
	dc.TextOut(1200, 592, CString("总共"));

	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	ReleaseDC(&dc);
	//CPaintDC dc(this); // device context for painting
	// 在此处添加消息处理程序代码
	// 不为绘图消息调用 CMySubDlg::OnPaint()
}

void CBrowseDlg::init(){
	first = true;
	eachpage = 4;
	cur = pos / eachpage;
	int n = album.size();
	pages = ceil(double(n) / eachpage);
	int d = -1;
	for (int i = 0; i < n; i++){
		d = album.next(d);
		fileno[i] = d;
	}
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
}

BOOL CBrowseDlg::OnInitDialog()
{
	//ShowWindow(SW_SHOWMAXIMIZED);
	CDialogEx::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP_BACK, IDB_BITMAP_BACK_SELECT, IDB_BITMAP_BACK_FOCUS);
	m_pre.SetBitmaps(IDB_BITMAP_PRE, IDB_BITMAP_PRE_SELECT, IDB_BITMAP_PRE_FOCUS);
	m_next.SetBitmaps(IDB_BITMAP_NEXT, IDB_BITMAP_NEXT_FOCUS, IDB_BITMAP_NEXT_SELECT);
	// TODO:  在此添加额外的初始化
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 1);
	/*first = true;
	eachpage = 4;
	cur = pos / eachpage;
	int n = album.size();
	pages = ceil(double(n) / eachpage);
	int d = -1;
	for (int i = 0; i < n; i++){
		d = album.next(d);
		fileno[i] = d;
	}*/
	init();
	//SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CBrowseDlg::OnBnClickedButtonBack()
{
	// TODO:  在此添加控件通知处理程序代码
	OnOK();
}

void CBrowseDlg::drawPicture(CStatic* m_Pic/*控件名称*/, int no/*控件编号0-n-1*/)
{
	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);   //m_picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_Pic->GetWindowDC();    //获得显示控件的DC

	CImage *pImage = new CImage();		//装载图像的类

	int n = album.size();
	pos = cur*eachpage + no;

	if (pos< n){						//还有图片可以显示
		HRESULT ret;
		CString path = CString(setting.libpath.c_str())
			+ CString("\\") + CString(album.record(fileno[pos]).filename().c_str());

		ret = pImage->Load(path);//从磁盘装载图片,根据页面计算得到的图片下标
		if (FAILED(ret)){
			MessageBox(path + _T("不存在!"));
			return;
		}
		
		int width = rectPic.Width();	//显示区域的宽和高
		int height = rectPic.Height();

		int picW = pImage->GetWidth();	//图片的宽和高
		int picH = pImage->GetHeight();

		//计算缩放比
		double r1 = double(picW) / double(width);
		double r2 = double(picH) / double(height);

		//r为最优缩放比例
		double r = (r1 >= r2 ? r1 : r2);

		int w = picW / r;
		int h = picH / r;
		int sw = (width - w) / 2;
		int sh = (height - h) / 2;
		//防止缩放后失真
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		//SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
		pImage->StretchBlt(pDC->m_hDC, sw, sh, w, h);

		//显示图片
		pImage->Draw(pDC->m_hDC, sw, sh, w, h);

		ReleaseDC(pDC);
		SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
		delete pImage;
	}
	else{
		m_Pic->ShowWindow(SW_HIDE);
	}
}


void CBrowseDlg::OnBnClickedButtonPre()
{
	cur = (cur - 1 + pages) % pages;
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	flush();
}


void CBrowseDlg::OnBnClickedButtonNxt()
{
	cur = (cur + 1) % pages;
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	flush();
}

void CBrowseDlg::flush(){
	if (m_pic1.IsWindowVisible() == false)
		m_pic1.ShowWindow(SW_SHOW);
	if (m_pic2.IsWindowVisible() == false)
		m_pic2.ShowWindow(SW_SHOW);
	if (m_pic3.IsWindowVisible() == false)
		m_pic3.ShowWindow(SW_SHOW);
	if (m_pic4.IsWindowVisible() == false)
		m_pic4.ShowWindow(SW_SHOW);
	CRect rc;
	m_pic1.GetWindowRect(&rc);
	ScreenToClient(rc);
	InvalidateRect(&rc);
	m_pic2.GetWindowRect(&rc);
	ScreenToClient(rc);
	InvalidateRect(&rc);
	m_pic3.GetWindowRect(&rc);
	ScreenToClient(rc);
	InvalidateRect(&rc);
	m_pic4.GetWindowRect(&rc);
	ScreenToClient(rc);
	InvalidateRect(&rc);
}

void CBrowseDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CString page;
	GetDlgItemText(IDC_EDIT_PAGE, page);
	int d = _ttoi(page);
	if (d > pages || d == 0){
		MessageBox(_T("页数错误!"));
		//SetDlgItemText();
		SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	}
	else{
		cur = d - 1;
	}
	flush();
}


BOOL CBrowseDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CBrowseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMySubDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID()){
	//case IDC_EDIT_PAGE:
	case IDC_STATIC_ALL:
		pDC->SetBkMode(TRANSPARENT);
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		CDC* dc = GetDC();
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);       //把父窗口背景图片先画到按钮上
		ReleaseDC(dc);
		pDC->SetTextColor(RGB(200, 200, 200));
		return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}





BOOL CBrowseDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0){
		//cur = (cur - 1 + pages) % pages;
		//SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
		//flush();
		OnBnClickedButtonPre();
	}
	else if (zDelta < 0){
		//cur = (cur + 1) % pages;
		//SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
		//flush();
		OnBnClickedButtonNxt();
	}
	return CMySubDlg::OnMouseWheel(nFlags, zDelta, pt);
}


void CBrowseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect r;
	m_pic1.GetWindowRect(&r);
	ScreenToClient(r);
	int id = -1;
	if (r.PtInRect(point)){
		id = 1;
	}
	m_pic2.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		id = 2;
	}
	m_pic3.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		id = 3;
	}
	m_pic4.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		id = 4;
	}
	if (~id){
		CBrowseSingleDlg *dlg = new CBrowseSingleDlg(NULL, fileno, pos - 4 + id, album.size());
		while (dlg->DoModal() == IDCANCEL){
			//pos = dlg->getcur() + 4 - id;
			delete dlg;
			init();
			dlg = new CBrowseSingleDlg(NULL, fileno, pos - 4 + id, album.size());
		}
		cur = dlg->getcur() / eachpage;
		
		SetDlgItemInt(IDC_STATIC_ALL, pages);
		CRect rc;
		((CStatic*)GetDlgItem(IDC_STATIC_ALL))->GetWindowRect(rc);
		ScreenToClient(rc);
		InvalidateRect(&rc);
		flush();
		//Invalidate();UpdateWindow();
		//Invalidate();UpdateWindow();
		//pos = dlg->getcur() + 4 - id;
		//OnCancel();
	}
	CMySubDlg::OnLButtonDown(nFlags, point);
}


void CBrowseDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect r;
	m_pic1.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		HCURSOR hCur = LoadCursor(NULL, IDC_HAND);
		SetCursor(hCur);
	}

	m_pic2.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		HCURSOR hCur = LoadCursor(NULL, IDC_HAND);
		SetCursor(hCur);
	}

	m_pic3.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		HCURSOR hCur = LoadCursor(NULL, IDC_HAND);
		SetCursor(hCur);
	}

	m_pic4.GetWindowRect(&r);
	ScreenToClient(r);
	if (r.PtInRect(point)){
		HCURSOR hCur = LoadCursor(NULL, IDC_HAND);
		SetCursor(hCur);
	}

	CMySubDlg::OnMouseMove(nFlags, point);
}
