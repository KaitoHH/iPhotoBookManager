#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CMySubDlg �Ի���

class CMySubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySubDlg)

public:
	//CMySubDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CMySubDlg(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CMySubDlg();
	void SetTittle(CString t);
// �Ի�������
	enum { IDD = IDD_MYSUBDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CString tittle;
public:
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBack();
	CMyButton m_back;
	void paintbg(CPaintDC*);
};
