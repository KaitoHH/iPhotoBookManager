// BrowseSingleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "BrowseSingleDlg.h"
#include "afxdialogex.h"


// CBrowseSingleDlg �Ի���

IMPLEMENT_DYNAMIC(CBrowseSingleDlg, CDialogEx)

CBrowseSingleDlg::CBrowseSingleDlg(CWnd* pParent /*=NULL*/)
	: CMySubDlg(CBrowseSingleDlg::IDD, pParent)
{
	dlg = nullptr;
}

CBrowseSingleDlg::CBrowseSingleDlg(CWnd* pParent, int *fileno, int cur,int all)
	: CMySubDlg(CBrowseSingleDlg::IDD, pParent)
{
	dlg = nullptr;
	this->fileno = fileno;
	this->cur = cur;
	this->all = all;
	if (cur >= all)		this->cur = 0;
}

CBrowseSingleDlg::~CBrowseSingleDlg()
{

}

void CBrowseSingleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
	DDX_Control(pDX, IDC_MPIC, m_pic);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_change);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_delete);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_auto);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_pre);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_next);
}


BEGIN_MESSAGE_MAP(CBrowseSingleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CBrowseSingleDlg::OnBnClickedButtonBack)
	
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CBrowseSingleDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &CBrowseSingleDlg::OnBnClickedButtonPre)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CBrowseSingleDlg::OnBnClickedButtonPlay)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CBrowseSingleDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CBrowseSingleDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CBrowseSingleDlg ��Ϣ�������


void CBrowseSingleDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	SetTittle(_T("���"));
	paintbg(&dc);

	drawpic();
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMySubDlg::OnPaint()
}


BOOL CBrowseSingleDlg::OnInitDialog()
{
	CMySubDlg::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP_BACK, IDB_BITMAP_BACK_SELECT, IDB_BITMAP_BACK_FOCUS);
	m_change.SetBitmaps(IDB_BITMAP_S_EDIT, IDB_BITMAP_S_EDIT_SELECT, IDB_BITMAP_S_EDIT_FOCUS);
	m_delete.SetBitmaps(IDB_BITMAP_S_DELETE, IDB_BITMAP_S_DELETE_SELECT, IDB_BITMAP_S_DELETE_FOCUS);
	m_auto.SetBitmaps(IDB_BITMAP_S_PLAY, IDB_BITMAP_S_PLAY_SELECT, IDB_BITMAP_S_PLAY_FOCUS);
	m_pre.SetBitmaps(IDB_BITMAP_S_PRE, IDB_BITMAP_S_PRE_SELECT, IDB_BITMAP_S_PRE_FOCUS);
	m_next.SetBitmaps(IDB_BITMAP_S_NEXT, IDB_BITMAP_S_NEXT_SELECT, IDB_BITMAP_S_NEXT_FOCUS);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	play = false;
	if (all == 0){
		MessageBox(_T("û������������ͼƬ!"));
		OnOK();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CBrowseSingleDlg::OnBnClickedButtonBack()
{
	OnOK();
}

void CBrowseSingleDlg::drawpic()
{
	CRect rectPic;
	m_pic.GetClientRect(&rectPic);   //m_pictureΪPicture Control�ؼ���������ÿؼ����������
	CDC* pDC = m_pic.GetWindowDC();    //�����ʾ�ؼ���DC

	CImage *pImage = new CImage();		//װ��ͼ�����
	
	int n = all;
	if (cur< n){						//����ͼƬ������ʾ
		HRESULT ret;
		CString path = CString(setting.libpath.c_str())
			+ CString("\\") + CString(album.record(fileno[cur]).filename().c_str());
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
		delete pImage;
	}
	else{
		m_pic.ShowWindow(SW_HIDE);
	}
}

void CBrowseSingleDlg::flush()
{
	if (dlg != nullptr && dlg->IsWindowVisible()){
		dlg->setimage(album.record(fileno[cur]));
		dlg->init();
	}
	if (m_pic.IsWindowVisible() == false)
		m_pic.ShowWindow(SW_SHOW);
	CRect rc;
	m_pic.GetWindowRect(&rc);
	ScreenToClient(rc);
	InvalidateRect(&rc);
}

void CBrowseSingleDlg::OnBnClickedButtonNext()
{
	cur = (cur + 1) % all;
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	flush();
}


void CBrowseSingleDlg::OnBnClickedButtonPre()
{
	cur = (cur - 1 + all) % all;
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	flush();
}


BOOL CBrowseSingleDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0){
		OnBnClickedButtonPre();
	}
	else if (zDelta < 0){
		OnBnClickedButtonNext();
	}
	return CMySubDlg::OnMouseWheel(nFlags, zDelta, pt);
}


void CBrowseSingleDlg::OnBnClickedButtonPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!play){
		SetTimer(1001, 1000, NULL);
		play = true;
	}
	else{
		KillTimer(1001);
		play = false;
	}
}


void CBrowseSingleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnBnClickedButtonNext();
	CMySubDlg::OnTimer(nIDEvent);
}


void CBrowseSingleDlg::OnBnClickedButtonEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	item = album.record(fileno[cur]);
	CRect rct;
	GetWindowRect(&rct);
	dlg = new CBrowseEditDlg(this,&rct,item);
	SetWindowPos(&this->wndTop, rct.left, rct.top, rct.Width(), rct.Height(), SWP_SHOWWINDOW);

	dlg->Create(IDD_BROWSE_EDIT);
	dlg->ShowWindow(SW_NORMAL);

	this->SetFocus();

}


void CBrowseSingleDlg::OnBnClickedButtonDelete()
{
    err_code ret = album.del(album.record(fileno[cur]));
	if (ret != success){
		CString str;
		str.Format(_T("�����˴���! ������[%d]"), ret);
		MessageBox(str);
	}
	else{
		MessageBox(_T("ɾ���ɹ���"));
		OnCancel();
	}
}
