//FootDetailDlg.h
#pragma once
#include"iPhotoBook.h"
#include "afxwin.h"
#include "MyButton.h"
extern iPhotoBook album;
// CFootDetailDlg �Ի���

class CFootDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFootDetailDlg)

public:
	CFootDetailDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CFootDetailDlg(CWnd* pParent, CPoint point, int cur,int no);
	virtual ~CFootDetailDlg();

// �Ի�������
	enum { IDD = IDD_FOOTDETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CString tocs(int i, ImageInfo item);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CPoint fa;
	int cur;
	int no;
	CListBox m_list;
	afx_msg void OnBnClickedButtonBack();
	CMyButton m_back;
};
