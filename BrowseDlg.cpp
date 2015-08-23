// BrowseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "BrowseDlg.h"
#include "afxdialogex.h"
#include "math.h"

// CBrowseDlg �Ի���

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


// CBrowseDlg ��Ϣ�������


void CBrowseDlg::OnPaint()
{
	CPaintDC dc(this);
	CMySubDlg::SetTittle(CString("���"));
	paintbg(&dc);

	//��ǰҳˢ��
	CFont *m_font = new CFont;
	CRect rect;
	CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT_PAGE);
	m_edit->SetLimitText(3);
	m_edit->GetWindowRect(rect);
	m_font->CreatePointFont(300, CString("����"), NULL);
	m_edit->SetFont(m_font, TRUE);

	//��ҳ��ˢ��
	CStatic *m_static = (CStatic*)GetDlgItem(IDC_STATIC_ALL);
	m_static->GetWindowRect(rect);
	m_static->SetFont(m_font, TRUE);
	SetDlgItemInt(IDC_STATIC_ALL, pages);

	//ͼ��ؼ�ˢ��
	drawPicture(&m_pic1, 0);
	drawPicture(&m_pic2, 1);
	drawPicture(&m_pic3, 2);
	drawPicture(&m_pic4, 3);
	
	//��̬����
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont *m_Font = new CFont;
	m_Font->CreatePointFont(175, CString("΢���ź�"), NULL);
	dc.SelectObject(m_Font);
	dc.TextOut(1200, 550, CString("��ǰ"));
	dc.TextOut(1200, 592, CString("�ܹ�"));

	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	ReleaseDC(&dc);
	//CPaintDC dc(this); // device context for painting
	// �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMySubDlg::OnPaint()
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CBrowseDlg::OnBnClickedButtonBack()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CBrowseDlg::drawPicture(CStatic* m_Pic/*�ؼ�����*/, int no/*�ؼ����0-n-1*/)
{
	CRect rectPic;
	(*m_Pic).GetClientRect(&rectPic);   //m_pictureΪPicture Control�ؼ���������ÿؼ����������
	CDC* pDC = m_Pic->GetWindowDC();    //�����ʾ�ؼ���DC

	CImage *pImage = new CImage();		//װ��ͼ�����

	int n = album.size();
	pos = cur*eachpage + no;

	if (pos< n){						//����ͼƬ������ʾ
		HRESULT ret;
		CString path = CString(setting.libpath.c_str())
			+ CString("\\") + CString(album.record(fileno[pos]).filename().c_str());

		ret = pImage->Load(path);//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
		if (FAILED(ret)){
			MessageBox(path + _T("������!"));
			return;
		}
		
		int width = rectPic.Width();	//��ʾ����Ŀ�͸�
		int height = rectPic.Height();

		int picW = pImage->GetWidth();	//ͼƬ�Ŀ�͸�
		int picH = pImage->GetHeight();

		//�������ű�
		double r1 = double(picW) / double(width);
		double r2 = double(picH) / double(height);

		//rΪ�������ű���
		double r = (r1 >= r2 ? r1 : r2);

		int w = picW / r;
		int h = picH / r;
		int sw = (width - w) / 2;
		int sh = (height - h) / 2;
		//��ֹ���ź�ʧ��
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		//SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
		pImage->StretchBlt(pDC->m_hDC, sw, sh, w, h);

		//��ʾͼƬ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString page;
	GetDlgItemText(IDC_EDIT_PAGE, page);
	int d = _ttoi(page);
	if (d > pages || d == 0){
		MessageBox(_T("ҳ������!"));
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
	// TODO:  �ڴ����ר�ô����/����û���

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
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);       //�Ѹ����ڱ���ͼƬ�Ȼ�����ť��
		ReleaseDC(dc);
		pDC->SetTextColor(RGB(200, 200, 200));
		return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
