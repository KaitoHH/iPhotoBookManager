// InfoReadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "InfoReadDlg.h"
#include "afxdialogex.h"


// CInfoReadDlg �Ի���

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


// CInfoReadDlg ��Ϣ�������


BOOL CInfoReadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	first = true;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTimer(1001, 0, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



void CInfoReadDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (first){
		first = false;
		err_code result = album.intialize(setting.libpath);
		if (result != success){
			int id = int(result);
			CString str;
			if (result != open_info_file_error){
				str.Format(_T("�����˴���! ������[%d]"),id);
				MessageBox(CString(str));
			}
			else{
				str = _T("�Ҳ���info.csv�ļ�����ȷ���ѽ����ļ�����ͼƬ��Ŀ¼��!");
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
