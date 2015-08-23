// InsertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "InsertDlg.h"
#include "afxdialogex.h"


// CInsertDlg �Ի���

IMPLEMENT_DYNAMIC(CInsertDlg, CDialogEx)

CInsertDlg::CInsertDlg(CWnd* pParent )
	: CMySubDlg(CInsertDlg::IDD, pParent)
{

}

CInsertDlg::CInsertDlg(CWnd* pParent, int *fileno, int cur, int all)
	: CMySubDlg(CInsertDlg::IDD, pParent)
{
	this->fileno = fileno;
	this->cur = cur;
	this->all = all;
}

CInsertDlg:: ~CInsertDlg()
{

}

void CInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MPIC, m_pic);
	DDX_Control(pDX, IDC_MPIC, m_pic);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_pre);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_next);
}


BEGIN_MESSAGE_MAP(CInsertDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_PRE, &CInsertDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CInsertDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CInsertDlg::OnBnClickedButtonBack)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CInsertDlg ��Ϣ�������


void CInsertDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMySubDlg::OnPaint()
	SetTittle(_T(""));
	paintbg(&dc);
	CRect rc;
	GetClientRect(&rc);// ��ȡ�ͻ���
	dc.FillSolidRect(&rc, RGB(42, 42, 42));   // ���ͻ�����ɫ

	//������
	CFont *m_Font3;
	m_Font3 = new CFont;
	m_Font3->CreatePointFont(400, CString("����"), NULL);
	dc.SelectObject(m_Font3);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(1220, 40, _T("��Ϣ"));

	//����EDIT�ؼ�
	CFont *m_font = new CFont;
	m_font->CreatePointFont(230, CString("΢���ź�"), NULL);
	setedit((CEdit *)GetDlgItem(IDC_EDIT1), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT2), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT3), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT4), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT5), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT6), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT7), m_font);

	//���þ�̬�ı�
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont *m_Font = new CFont;
	m_Font->CreatePointFont(120, CString("΢���ź�"), NULL);
	dc.SelectObject(m_Font);
	dc.TextOut(1010, 130, CString("�ļ���"));
	dc.TextOut(1010, 195, CString("��������"));
	dc.TextOut(1010, 260, CString("Ӣ������"));
	dc.TextOut(1010, 330, CString("�ص�"));
	dc.TextOut(1010, 400, CString("�ϼ��ص�"));
	dc.TextOut(1010, 465, CString("�ϼ���ͼ"));
	dc.TextOut(1010, 530, CString("�ϴ���"));
	dc.TextOut(1010, 605, CString("������ͼ"));

	CFont *m_Font2 = new CFont;
	m_Font2->CreatePointFont(100, CString("΢���ź�"), NULL);
	dc.SelectObject(m_Font2);
	dc.TextOut(1100, 600, CString("�й�"));
	dc.TextOut(1225, 600, CString("��ʦ��"));
	dc.TextOut(1100, 630, CString("����"));

	drawpic();

}

void CInsertDlg::drawpic()
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

void CInsertDlg::setedit(CEdit *m_edit, CFont *m_font)
{
	m_edit->SetLimitText(20);
	m_edit->SetFont(m_font, TRUE);
}

HBRUSH CInsertDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMySubDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID()){
	case IDC_EDIT1:
	case IDC_EDIT2:
	case IDC_EDIT3:
	case IDC_EDIT4:
	case IDC_EDIT5:
	case IDC_EDIT6:
	case IDC_EDIT7:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(42, 42, 42));
		HBRUSH hBr = CreateSolidBrush(RGB(42, 42, 42)); // ����ɫ
		return (HBRUSH)hBr;
	}

	return hbr;
}


void CInsertDlg::OnBnClickedButtonPre()
{
	save();
	cur = (cur - 1 + all) % all;
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	flush();
	init();
}



void CInsertDlg::OnBnClickedButtonNext()
{
	save();
	cur = (cur + 1) % all;
	SetDlgItemInt(IDC_EDIT_PAGE, cur + 1);
	flush();
	init();
}

void CInsertDlg::flush()
{
	CRect rc;
	m_pic.GetWindowRect(&rc);
	ScreenToClient(rc);
	InvalidateRect(&rc);
}

void CInsertDlg::OnBnClickedButtonBack()
{
	save();
	OnOK();
}

void CInsertDlg::init()
{
	ImageInfo item = album.record(fileno[cur]);
	SetDlgItemText(IDC_EDIT1, CString(item.filename().c_str()));
	SetDlgItemText(IDC_EDIT2, CString(item.textcn().c_str()));
	SetDlgItemText(IDC_EDIT3, CString(item.texten().c_str()));
	SetDlgItemText(IDC_EDIT4, CString(item.postion().c_str()));
	SetDlgItemText(IDC_EDIT5, CString(item.posl().c_str()));
	SetDlgItemText(IDC_EDIT6, CString(item.lname().c_str()));
	SetDlgItemText(IDC_EDIT7, CString(item.uper().c_str()));

	CButton* radio;
	radio = (CButton*)GetDlgItem(IDC_RADIO_1);
	radio->SetCheck(0);
	radio = (CButton*)GetDlgItem(IDC_RADIO_2);
	radio->SetCheck(0);
	radio = (CButton*)GetDlgItem(IDC_RADIO_3);
	radio->SetCheck(0);
	if (item.map().find("�й�") != -1){
		radio = (CButton*)GetDlgItem(IDC_RADIO_1);
	}
	else if (item.map() == "��ʦ��"){
		radio = (CButton*)GetDlgItem(IDC_RADIO_2);
	}
	else{
		radio = (CButton*)GetDlgItem(IDC_RADIO_3);
	}
	radio->SetCheck(1);

}

BOOL CInsertDlg::OnInitDialog()
{
	CMySubDlg::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP9, IDB_BITMAP7, IDB_BITMAP8);
	m_pre.SetBitmaps(IDB_BITMAP_PRE_BLACK, IDB_BITMAP_PRE_BLACK_FOCUS, IDB_BITMAP_PRE_BLACK_SELECT);
	m_next.SetBitmaps(IDB_BITMAP_NEXT_BLACK, IDB_BITMAP_NEXT_BLACK_FOCUS, IDB_BITMAP_NEXT_BLACK_SELECT);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CInsertDlg::save()
{
	ImageInfo item = album.record(fileno[cur]);
	ImageInfo newitem = item;
	string m[] = { "�й�", "��ʦ��", "null" };
	CString s;
	GetDlgItemText(IDC_EDIT2, s);
	newitem.set_textcn(string(CStringA(s)));
	GetDlgItemText(IDC_EDIT3, s);
	newitem.set_texten(string(CStringA(s)));
	GetDlgItemText(IDC_EDIT4, s);
	newitem.set_postion(string(CStringA(s)));
	GetDlgItemText(IDC_EDIT5, s);
	newitem.set_posl(string(CStringA(s)));
	GetDlgItemText(IDC_EDIT6, s);
	newitem.set_lname(string(CStringA(s)));
	GetDlgItemText(IDC_EDIT7, s);
	newitem.set_uper(string(CStringA(s)));

	int radio = GetCheckedRadioButton(IDC_RADIO_1, IDC_RADIO_3) - IDC_RADIO_1;
	newitem.set_map(m[radio]);
	item = newitem;
	album.update(item, newitem);
	init();
}

BOOL CInsertDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (zDelta > 0){
		OnBnClickedButtonPre();
	}
	else{
		OnBnClickedButtonNext();
	}
	return CMySubDlg::OnMouseWheel(nFlags, zDelta, pt);
}
