
// iPhotoBookFrameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "iPhotoBookFrameDlg.h"
#include "afxdialogex.h"

#include <time.h>
#include <Windows.h>
#include <sstream>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult);
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


// CiPhotoBookFrameDlg �Ի���



CiPhotoBookFrameDlg::CiPhotoBookFrameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CiPhotoBookFrameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CiPhotoBookFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_browse);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_search);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_edit);
	DDX_Control(pDX, IDB_BITMAP_INSERT, m_insert);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_delete);
	DDX_Control(pDX, IDC_BUTTON_FOOTPRINT, m_footprint);
	DDX_Control(pDX, IDB_BITMAP_TIMETEST, m_timetest);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_setting);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_close);
	DDX_Control(pDX, IDC_BUTTON_ABOUT, m_about);
	DDX_Control(pDX, IDC_EDIT1, m_edit_search);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
	DDX_Control(pDX, IDC_M1, m_m1);
	DDX_Control(pDX, IDC_M2, m_m2);
	DDX_Control(pDX, IDC_NANS, m_nans);
	DDX_Control(pDX, IDC_TIME, m_time);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CiPhotoBookFrameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CiPhotoBookFrameDlg::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CiPhotoBookFrameDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CiPhotoBookFrameDlg::OnBnClickedButtonAbout)
	ON_EN_CHANGE(IDC_EDIT1, &CiPhotoBookFrameDlg::OnEnChangeEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, &CiPhotoBookFrameDlg::OnEnSetfocusEdit1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CiPhotoBookFrameDlg::OnBnClickedButtonSetting)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CiPhotoBookFrameDlg::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CiPhotoBookFrameDlg::OnBnClickedButtonBack)
	ON_STN_CLICKED(IDC_NANS, &CiPhotoBookFrameDlg::OnStnClickedNans)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CiPhotoBookFrameDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDB_BITMAP_INSERT, &CiPhotoBookFrameDlg::OnBnClickedBitmapInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CiPhotoBookFrameDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CiPhotoBookFrameDlg::OnBnClickedButtonEdit)
	ON_LBN_DBLCLK(IDC_LIST, &CiPhotoBookFrameDlg::OnLbnDblclkList)
	ON_BN_CLICKED(IDC_BUTTON_FOOTPRINT, &CiPhotoBookFrameDlg::OnBnClickedButtonFootprint)
	ON_BN_CLICKED(IDB_BITMAP_TIMETEST, &CiPhotoBookFrameDlg::OnBnClickedBitmapTimetest)
END_MESSAGE_MAP()


// CiPhotoBookFrameDlg ��Ϣ�������

BOOL CiPhotoBookFrameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//��������
	
	if (!readfile()){
		defaultfile();
		CWelcomeDlg dlg;
		if (dlg.DoModal() == IDOK){
			creatfile();
		}
		else{
			OnOK();
		}
	}
	CInfoReadDlg dlg;
	bool close = false;
	while (dlg.DoModal() != IDOK){
		CWelcomeDlg dlg;
		if (dlg.DoModal() == IDOK){
			creatfile();
		}
		else{
			close = true;
			break;
		}
	}
	if (close)	OnOK();

	SetWindowText(CString(setting.libname.c_str())+_T(" - iPhotoBook Manager"));
	first = true;
	//���ư�ť
	m_about.MoveWindow(1349 - 50, 50, 50, 50);
	m_browse.SetBitmaps(IDB_BITMAP_BROWSE, IDB_BITMAP_BROWSE_SELECT, IDB_BITMAP_BROWSE_FOCUS);
	m_search.SetBitmaps(IDB_BITMAP_SEARCH, IDB_BITMAP_SEARCH_SELECT, IDB_BITMAP_SEARCH_FOCUS);
	m_edit.SetBitmaps(IDB_BITMAP_EDIT, IDB_BITMAP_EDIT_SELECT, IDB_BITMAP_EDIT_FOCUS);
	m_insert.SetBitmaps(IDB_BITMAP_INSERT, IDB_BITMAP_INSERT_SELECT, IDB_BITMAP_INSERT_FOCUS);
	m_delete.SetBitmaps(IDB_BITMAP_DELETE, IDB_BITMAP_DELETE_SELECT, IDB_BITMAP_DELETE_FOCUS);
	m_footprint.SetBitmaps(IDB_BITMAP_FOOTPRINT, IDB_BITMAP_FOOTPRINT_SELECT, IDB_BITMAP_FOOTPRINT_FOCUS);
	m_timetest.SetBitmaps(IDB_BITMAP_TIMETEST, IDB_BITMAP_TIMETEST_SELECT, IDB_BITMAP_TIMETEST_FOCUS);
	m_setting.SetBitmaps(IDB_BITMAP_SETTING, IDB_BITMAP_SETTING_SELECT, IDB_BITMAP_SETTING_FOCUS);
	m_close.SetBitmaps(IDB_BITMAP_CLOSE, IDB_BITMAP_CLOSE_SELECT, IDB_BITMAP_CLOSE_FOCUS);
	m_about.SetBitmaps(IDB_BITMAP_ABOUT, IDB_BITMAP_ABOUT_SELECT, IDB_BITMAP_ABOUT_FOCUS);
	m_back.SetBitmaps(IDB_BITMAP_BACK, IDB_BITMAP_BACK_SELECT, IDB_BITMAP_BACK_FOCUS);

	//���������
	CRect rect;
	m_edit_search.GetWindowRect(rect);
	CFont *m_Font;
	m_Font = new CFont;
	m_Font->CreatePointFont(rect.Height() * 5.5, CString("΢���ź�"), NULL);
	m_edit_search.SetFont(m_Font, TRUE);
	SetDlgItemText(IDC_EDIT1, _T("�ڴ���������Ҫ��������Ƭ"));
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CiPhotoBookFrameDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CiPhotoBookFrameDlg::OnPaint()
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
		CPaintDC dc(this);
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
		
		//����
		CPen pen(PS_SOLID, 5, RGB(155, 203, 96));
		CPen *cOldPen = dc.SelectObject(&pen);
		dc.MoveTo(285, 115);
		dc.LineTo(1047, 115);
		dc.SelectObject(cOldPen);

		//�������ˢ��
		CEdit *m_edit = (CEdit*)GetDlgItem(IDC_M1);
		CFont *m_font = new CFont;
		m_font->CreatePointFont(300, CString("����"), NULL);
		m_edit->SetFont(m_font, TRUE);
		SetDlgItemText(IDC_M1, _T("���ҵ�"));

		m_edit = (CEdit*)GetDlgItem(IDC_M2);
		m_edit->SetFont(m_font, TRUE);
		SetDlgItemText(IDC_M2, _T("���������ʱԼ"));

		m_edit = (CEdit*)GetDlgItem(IDC_NANS);
		m_edit->SetFont(m_font, TRUE);

		m_edit = (CEdit*)GetDlgItem(IDC_TIME);
		m_edit->SetFont(m_font, TRUE);

		m_font = new CFont;
		m_font->CreatePointFont(130, CString("����"), NULL);
		m_list.SetFont(m_font, TRUE);
		
		CFont *m_Font2 = new CFont;
		m_Font2->CreatePointFont(200, CString("΢���ź�"), NULL);
		dc.SelectObject(m_Font2);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));
		dc.TextOut(1100, 20, CString("���,")+CString(setting.libname.c_str()));
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CiPhotoBookFrameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CiPhotoBookFrameDlg::OnBnClickedButtonBrowse()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (album.size() == 0){
		MessageBox(_T("ͼƬ��Ϊ��!"));
		return;
	}
	CBrowseDlg *dlg;
	dlg = new CBrowseDlg;
	dlg->DoModal();
	delete dlg;
}


void CiPhotoBookFrameDlg::OnBnClickedButtonClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}


void CiPhotoBookFrameDlg::OnBnClickedButtonAbout()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlg;
	dlg.DoModal();
}




void CiPhotoBookFrameDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CRect rect;
	m_edit_search.GetWindowRect(&rect);
	ScreenToClient(rect);
	InvalidateRect(&rect);
	m_list.ResetContent();

	album.set_fuzzy(setting.ssearch);
	if (!first){
		LARGE_INTEGER begin;
		LARGE_INTEGER end;
		LARGE_INTEGER frequ;
		int nans = 0;
		CString t;
		fileno.clear();

		switchTo();
		CString searchStr;
		GetDlgItemText(IDC_EDIT1, searchStr);
		string s = CStringA(searchStr);
		if (s == ""){
			switchBack();
			return;
		}
		else if (s.find(".") != -1){
			int x;

			QueryPerformanceFrequency(&frequ);
			QueryPerformanceCounter(&begin);
			//ʱ����Կ�ʼ
			err_code ret = album.findByFileName(s,x);
			//ʱ����Խ���
			QueryPerformanceCounter(&end);

			if (ret == success){
				
				fileno.push_front(x);
				nans = 1;
			}

		}else{

			QueryPerformanceFrequency(&frequ);
			QueryPerformanceCounter(&begin);
			//ʱ����Կ�ʼ
			if (hasCN(s)){//����
				album.findByPosition(s, nans, fileno);
			}
			else{//Ӣ��
				album.findByTittle(s, nans, fileno);
			}
			//ʱ����Խ���
			QueryPerformanceCounter(&end);


			}
		

		double timeCost = (end.QuadPart - begin.QuadPart) / (double)frequ.QuadPart;

		t.Format(_T("%.10fs"), timeCost);
		SetDlgItemText(IDC_TIME, t);
		SetDlgItemInt(IDC_NANS, nans);
		m_nans.GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);
		m_time.GetWindowRect(&rect);
		ScreenToClient(rect);
		InvalidateRect(&rect);
		UpdateWindow();

		list<int>::iterator it;
		int i = 0;
		for (it = fileno.begin(); it != fileno.end(); it++){
			ImageInfo r = album.record(*it);
			t.Format(genStr(i + 1, r.filename().c_str(), r.texten().c_str(), r.postion()));
			m_list.InsertString(i++, t);
		}

	}

}


void CiPhotoBookFrameDlg::OnEnSetfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (first)	SetDlgItemText(IDC_EDIT1, CString(""));
	first = false;

}


HBRUSH CiPhotoBookFrameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	int id = pWnd->GetDlgCtrlID();

	CRect rc;
	switch (id){
		case IDC_EDIT1:
		case IDC_M1:
		case IDC_M2:
		case IDC_NANS:
		case IDC_TIME:
			pDC->SetBkMode(TRANSPARENT);
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			//CDC* dc = GetDC();
			pDC->BitBlt(0, 0, rc.Width(), rc.Height(), GetDC(), rc.left, rc.top, SRCCOPY);       //�Ѹ����ڱ���ͼƬ�Ȼ�����ť��
			//ReleaseDC(dc);
			if (first){
				pDC->SetTextColor(RGB(200, 200, 200));
			}
			else
				pDC->SetTextColor(RGB(76, 141, 197));
			if (id == IDC_NANS || id == IDC_TIME)
				pDC->SetTextColor(RGB(155, 203, 96));
			if (id == IDC_LIST)
				pDC->SetTextColor(RGB(155, 203, 96));
			return (HBRUSH) ::GetStockObject(NULL_BRUSH);
			break;
		case IDC_LIST:
			pDC->SetTextColor(RGB(0, 46, 95));
		default:
			break;
	}
	

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CiPhotoBookFrameDlg::OnBnClickedButtonSetting()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CSettingDlg dlg;
	dlg.DoModal();
	SetWindowText(CString(setting.libname.c_str()) + _T(" - iPhotoBook"));
}


void CiPhotoBookFrameDlg::OnEnKillfocusEdit1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	if (s == ""){
		first = true;
		SetDlgItemText(IDC_EDIT1, _T("�ڴ���������Ҫ��������Ƭ"));
	}
}


void CiPhotoBookFrameDlg::OnBnClickedButtonBack()
{
	first = true;
	SetDlgItemText(IDC_EDIT1, _T("�ڴ���������Ҫ��������Ƭ"));
	switchBack();
}

void CiPhotoBookFrameDlg::switchTo(){
	m_search.ShowWindow(SW_HIDE);
	m_edit.ShowWindow(SW_HIDE);
	m_insert.ShowWindow(SW_HIDE);
	m_delete.ShowWindow(SW_HIDE);
	m_footprint.ShowWindow(SW_HIDE);
	m_about.ShowWindow(SW_HIDE);
	m_close.ShowWindow(SW_HIDE);
	m_setting.ShowWindow(SW_HIDE);
	m_timetest.ShowWindow(SW_HIDE);
	m_browse.ShowWindow(SW_HIDE);
	m_back.ShowWindow(SW_SHOW);
	m_m1.ShowWindow(SW_SHOW);
	m_m2.ShowWindow(SW_SHOW);
	m_nans.ShowWindow(SW_SHOW);
	m_time.ShowWindow(SW_SHOW);
	m_list.ShowWindow(SW_SHOW);
}

void CiPhotoBookFrameDlg::switchBack(){
	m_search.ShowWindow(SW_SHOW);
	m_edit.ShowWindow(SW_SHOW);
	m_insert.ShowWindow(SW_SHOW);
	m_delete.ShowWindow(SW_SHOW);
	m_footprint.ShowWindow(SW_SHOW);
	m_about.ShowWindow(SW_SHOW);
	m_close.ShowWindow(SW_SHOW);
	m_setting.ShowWindow(SW_SHOW);
	m_timetest.ShowWindow(SW_SHOW);
	m_browse.ShowWindow(SW_SHOW);
	m_back.ShowWindow(SW_HIDE);
	m_m1.ShowWindow(SW_HIDE);
	m_m2.ShowWindow(SW_HIDE);
	m_nans.ShowWindow(SW_HIDE);
	m_time.ShowWindow(SW_HIDE);
	m_list.ShowWindow(SW_HIDE);
}

void CiPhotoBookFrameDlg::OnStnClickedNans()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CiPhotoBookFrameDlg::OnBnClickedButtonSearch()
{
	m_edit_search.SetFocus();
}

CString CiPhotoBookFrameDlg::genStr(int d,string a,string b,string c)
{
	std::stringstream ss;
	ss << setiosflags(ios::left);

	ss << setw(10) << d;
	ss << setw(50) << a;
	ss << setw(50) << b;
	ss << setw(10) << c;

	CString str(ss.str().c_str());
	//MessageBox(str);
	return str;
}

void CiPhotoBookFrameDlg::OnBnClickedBitmapInsert()
{
	int nfile = 0;
	int no[MAXN];
	CFileDialog openDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, _T("jpg�ļ�(*.jpg)|*.jpg||"));

	const int nMaxFiles = 1000;
	const int nMaxPathBuffer = (nMaxFiles * (MAX_PATH + 1)) + 1;
	LPWSTR pc = (LPWSTR)malloc(nMaxPathBuffer * sizeof(WCHAR));
	if (pc)
	{
		openDlg.GetOFN().lpstrFile = pc;
		openDlg.GetOFN().lpstrFile[0] = NULL;
		openDlg.m_ofn.nMaxFile = nMaxPathBuffer;
		if (openDlg.DoModal() == IDOK)
		{
			POSITION posStart = openDlg.GetStartPosition();
			while (posStart)
			{
				
				CString name = openDlg.GetNextPathName(posStart);
				string filename = CStringA(name);
				ImageInfo i;
				
				CPicture pic;
				pic.LoadPictureFromFile(name.GetBuffer());
				name.ReleaseBuffer();

				
				CSize size = pic.GetSize();
				i.set_width(size.cx);
				i.set_height(size.cy);
				

				CFileStatus  status;
				CFile::GetStatus(CString(filename.c_str()), status);
				i.set_time(status.m_mtime.GetTime());
				i.set_size(status.m_size);

				string path = filename.substr(filename.rfind("\\") + 1, -1);
				i.set_filename(path);

				err_code ret = album.add(i);
				if (ret != success){
					CString s;
					s.Format(_T("�����˴���! ������[%d]"), ret);
					MessageBox(s);
					continue;
				}
				int x;
				album.findByFileName(path, x);
				no[nfile++] = x;

				CString s1 = CString(filename.c_str());
				CString s2 = CString((setting.libpath + "\\" + path).c_str());
				LPCWSTR src = s1.GetBuffer();
				LPCWSTR dst = s2.GetBuffer();
				int d = CopyFile(src, dst, TRUE);
				s1.ReleaseBuffer();
				s2.ReleaseBuffer();

				if (!d){
					CString *msg = new CString;
					msg->Format(_T("����ʧ�ܣ���ȷ���ļ�[%S]�Ƿ��Ѵ��ڣ�"), path.c_str());
					MessageBox(*msg);
					delete msg;
				}


			}
			if (nfile){
				CInsertDlg dlg(NULL, no, 0, nfile);
				dlg.DoModal();
			}
			
		}
		free(pc);
	}

}


void CiPhotoBookFrameDlg::OnBnClickedButtonDelete()
{
	OnBnClickedButtonSearch();
}


void CiPhotoBookFrameDlg::OnBnClickedButtonEdit()
{
	OnBnClickedButtonSearch();
}


void CiPhotoBookFrameDlg::OnLbnDblclkList()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int *no = new int[MAXN];
	if (no == nullptr){
		MessageBox(_T("�����ڴ�ʧ��"));
	}
	list<int>::iterator it;
	int i = 0;
	for (it = fileno.begin(); it != fileno.end(); it++){
		no[i++] = *it;
	}

	int d = m_list.GetCurSel();
	if (d < 0)	d = 0;
	CBrowseSingleDlg *dlg = new CBrowseSingleDlg(NULL, no, d , fileno.size());
	while (dlg->DoModal() == IDCANCEL){
		d = dlg->getcur();
		delete dlg;
		OnEnChangeEdit1();
		i = 0;
		for (it = fileno.begin(); it != fileno.end(); it++){
			no[i++] = *it;
		}
		dlg = new CBrowseSingleDlg(NULL, no, d, fileno.size());
	}
	OnEnChangeEdit1();
	m_list.SetCurSel(dlg->getcur());
	
	delete[] no;
	delete dlg;
}





void CiPhotoBookFrameDlg::OnBnClickedButtonFootprint()
{
	ShowWindow(SW_HIDE);
	CFootDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CiPhotoBookFrameDlg::OnBnClickedBitmapTimetest()
{
	CTimeTestDlg dlg;
	dlg.DoModal();
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t) *(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

BOOL CiPhotoBookFrameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	//����Return
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

bool hasCN(string s)
{
	int len = s.length();
	for (int i = 0; i < len; i++){
		if (s[i] < 0)	return true;
	}
	return false;
}

