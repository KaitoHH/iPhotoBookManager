#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CMySubDlg 对话框

class CMySubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySubDlg)

public:
	//CMySubDlg(CWnd* pParent = NULL);   // 标准构造函数
	CMySubDlg(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CMySubDlg();
	void SetTittle(CString t);
// 对话框数据
	enum { IDD = IDD_MYSUBDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
