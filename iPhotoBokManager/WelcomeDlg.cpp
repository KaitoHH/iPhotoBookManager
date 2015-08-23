// WelcomeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "WelcomeDlg.h"
#include "afxdialogex.h"


// CWelcomeDlg 对话框

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


// CWelcomeDlg 消息处理程序


void CWelcomeDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	TCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;//这个是输出缓冲区   
	bi.lpszTitle = _T("请选择图片库文件夹："); //标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//使用新的界面,在win7中效果较好//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);//弹出对话框   %s"), szDir);

	if (SHGetPathFromIDList(pidl, szDir)){
		SetDlgItemText(IDC_EDIT2, szDir);
	}
	else if (pidl != NULL)
		MessageBox(_T("选择错误！"));
}


void CWelcomeDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString s;
	GetDlgItemText(IDC_EDIT3, s);
	if (s == _T("")){
		MessageBox(_T("请填写您的图片库名称！"));
		return;
	}
	setting.libname = CStringA(s);

	GetDlgItemText(IDC_EDIT2, s);
	if (s == _T("")){
		MessageBox(_T("请选择您的图片库目录！"));
		return;
	}
	setting.libpath = CStringA(s);

	CDialogEx::OnOK();
}


BOOL CWelcomeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT3);
	m_edit->SetLimitText(20);
	SetDlgItemText(IDC_EDIT3, CString(setting.libname.c_str()));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
