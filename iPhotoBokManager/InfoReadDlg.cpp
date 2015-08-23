// InfoReadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "InfoReadDlg.h"
#include "afxdialogex.h"


// CInfoReadDlg 对话框

IMPLEMENT_DYNAMIC(CInfoReadDlg, CDialogEx)

CInfoReadDlg::CInfoReadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfoReadDlg::IDD, pParent)
{

}

CInfoReadDlg::~CInfoReadDlg()
{
}

void CInfoReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoReadDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CInfoReadDlg 消息处理程序


BOOL CInfoReadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	first = true;
	// TODO:  在此添加额外的初始化
	SetTimer(1001, 0, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CInfoReadDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (first){
		first = false;
		err_code result = album.intialize(setting.libpath);
		if (result != success){
			int id = int(result);
			CString str;
			if (result != open_info_file_error){
				str.Format(_T("发生了错误! 错误编号[%d]"),id);
				MessageBox(CString(str));
			}
			else{
				str = _T("找不到info.csv文件，请确认已将该文件放在图片库目录下!");
			}
			MessageBox(str);
			OnCancel();
		}
		else{
			OnOK();
		}
		CDialogEx::OnTimer(nIDEvent);

	}
}
