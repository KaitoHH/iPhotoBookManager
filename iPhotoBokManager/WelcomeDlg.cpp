// WelcomeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "WelcomeDlg.h"
#include "afxdialogex.h"


// CWelcomeDlg �Ի���

IMPLEMENT_DYNAMIC(CWelcomeDlg, CDialogEx)

CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelcomeDlg::IDD, pParent)
{

}

CWelcomeDlg::~CWelcomeDlg()
{
}

void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CWelcomeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CWelcomeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CWelcomeDlg ��Ϣ�������


void CWelcomeDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		SetDlgItemText(IDC_EDIT2, szDir);
	}
	else if (pidl != NULL)
		MessageBox(_T("ѡ�����"));
}


void CWelcomeDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	GetDlgItemText(IDC_EDIT3, s);
	if (s == _T("")){
		MessageBox(_T("����д����ͼƬ�����ƣ�"));
		return;
	}
	setting.libname = CStringA(s);

	GetDlgItemText(IDC_EDIT2, s);
	if (s == _T("")){
		MessageBox(_T("��ѡ������ͼƬ��Ŀ¼��"));
		return;
	}
	setting.libpath = CStringA(s);

	CDialogEx::OnOK();
}


BOOL CWelcomeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT3);
	m_edit->SetLimitText(20);
	SetDlgItemText(IDC_EDIT3, CString(setting.libname.c_str()));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
