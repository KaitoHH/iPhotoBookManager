// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include <iostream>

// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CMySubDlg(CSettingDlg::IDD, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CSettingDlg::OnBnClickedButtonPath)
	ON_BN_CLICKED(IDC_BUTTON_DICT, &CSettingDlg::OnBnClickedButtonDict)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CSettingDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������


void CSettingDlg::OnPaint()
{
	CMySubDlg::SetTittle(CString("����"));
	CMySubDlg::OnPaint();
	
	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont *m_Font = new CFont;
	m_Font->CreatePointFont(175, CString("��������"), NULL);
	dc.SelectObject(m_Font);

	dc.TextOut(240, 155, CString("����ͼƬ������"));
	dc.TextOut(240, 312, CString("ͼƬ�����"));
	dc.TextOut(240, 460, CString("ͼƬ��·��"));
	dc.TextOut(240, 575, CString("�����ʽ"));
	dc.TextOut(240, 660, CString("������ʽ"));
	delete m_Font;

	m_Font = new CFont;
	m_Font->CreatePointFont(120, CString("��������"), NULL);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(457, 580, CString("2 * 2"));
	dc.TextOut(822, 580, CString("2 * 3"));
	dc.TextOut(457, 660, CString("����ģ������"));
	
	//ͼƬ�����
	CStatic *m_pic = (CStatic *)GetDlgItem(IDC_IMAGE);
	show_avator(CString(setting.avatorpath.c_str()), m_pic);
}




BOOL CSettingDlg::OnInitDialog()
{
	CMySubDlg::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP_BACK, IDB_BITMAP_BACK_SELECT, IDB_BITMAP_BACK_FOCUS);

	changed = false;
	// �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	CFont *m_Font;
	CEdit *m_edit;
	m_Font = new CFont;

	//ͼƬ������
	m_edit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	m_edit->SetLimitText(20);
	m_edit->GetWindowRect(rect);
	m_Font->CreatePointFont(rect.Height() * 5.7, CString("��������"), NULL);
	m_edit->SetFont(m_Font, TRUE);
	SetDlgItemText(IDC_EDIT_NAME, CString(setting.libname.c_str()));

	//ͼƬ��·��
	m_edit = (CEdit*)GetDlgItem(IDC_EDIT_DICT);
	m_edit->SetFont(m_Font, TRUE);
	SetDlgItemText(IDC_EDIT_DICT, CString(setting.libpath.c_str()));

	//�����ʽ����
	int d = setting.browse;
	CButton *radio;
	if (d == 0)		radio = (CButton*)GetDlgItem(IDC_RADIO1);
	else            radio = (CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(1);

	//������ʽ����
	radio = (CButton*)GetDlgItem(IDC_CHECK1);
	radio->SetCheck(setting.ssearch == 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CSettingDlg::OnBnClickedButtonPath()
{
	// �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("ͼƬ�ļ�(*.jpg;*.jpeg;*.bmp;*.png)|*.jpg;*.jpeg;*.bmp;*.png||");
	CFileDialog fileDlg(true, NULL, NULL, 0, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal()){
		strFilePath = fileDlg.GetPathName();
		CStatic *m_pic = (CStatic *)GetDlgItem(IDC_IMAGE);
		show_avator(strFilePath, m_pic);
		setting.avatorpath = CStringA(strFilePath);
	}
}


void CSettingDlg::OnBnClickedButtonDict()
{
	// �ڴ���ӿؼ�֪ͨ����������

	//ѡ�����·��  
	TCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;//��������������   
	bi.lpszTitle = _T("��ѡ��ͼƬ���ļ��У�"); //����  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//ʹ���µĽ���,��win7��Ч���Ϻ�//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);//�����Ի���   %s"), szDir);
	
	if (SHGetPathFromIDList(pidl, szDir)){
		SetDlgItemText(IDC_EDIT_DICT, szDir);
		changed = true;
	}
	else if (pidl != NULL)
		MessageBox(_T("ѡ�����")); 
	
	
}


HBRUSH CSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMySubDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// �ڴ˸��� DC ���κ�����

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_RADIO1:
		case IDC_RADIO2:
			CRect rc;
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			CDC* dc = GetDC();
			pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);       //�Ѹ����ڱ���ͼƬ�Ȼ�����ť��
			ReleaseDC(dc);
			return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	// ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void show_avator(CString strFilePath,CStatic *m_pic)
{
	CImage *pImage = new CImage();
	HRESULT ret = pImage->Load(strFilePath);
	if (FAILED(ret))		return;
	CRect rect;
	m_pic->GetWindowRect(rect);

	CDC* pDC = m_pic->GetWindowDC();
	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	pImage->StretchBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height());
	pImage->Draw(pDC->m_hDC, rect);
}

void CSettingDlg::OnBnClickedButtonBack()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if(changed)	MessageBox(_T("�����޸���ͼƬ��·����������һ������ʱ��Ч"));
	CString name, dict;
	GetDlgItemText(IDC_EDIT_NAME, name);
	GetDlgItemText(IDC_EDIT_DICT, dict);
	setting.libname = CStringA(name);
	setting.libpath = CStringA(dict);
	//TODO: ��ť����
	setting.browse = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) - IDC_RADIO1;
	setting.ssearch = (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1));
	creatfile();
	OnOK();
}
