//InsertDlg.h
#pragma once
#include"MySubDlg.h"
#include<list>
#include "afxwin.h"
#include "file.h"
#include "iPhotoBook.h"
#include "MyButton.h"
extern mysetting setting;
extern iPhotoBook album;

using namespace std;
// CInsertDlg 对话框

class CInsertDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CInsertDlg)

public:
	CInsertDlg(CWnd* pParent = NULL);   // 标准构造函数
	CInsertDlg(CWnd* pParent, int *fileno, int cur, int all);
	virtual ~CInsertDlg();

// 对话框数据
	enum { IDD = IDD_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void drawpic();
	void setedit(CEdit *m_edit, CFont *m_font);
	void flush();
	void init();
	void save();
public:
	afx_msg void OnPaint();

	list<int> *lib;
	int *fileno;
	int all;
	int cur;
	CStatic m_pic;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonBack();

	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CMyButton m_pre;
	CMyButton m_back;
	CMyButton m_next;
};

LPCWSTR stringToLPCWSTR(string);