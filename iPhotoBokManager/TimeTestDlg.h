//TimeTestDlg.h
#pragma once
#include "MySubDlg.h"
#include "Graph.h"
#include "GraphSeries.h"
#include "iPhotoBook.h"
#include "MyButton.h"
#include "afxwin.h"
extern iPhotoBook album;

// CTimeTestDlg 对话框

class CTimeTestDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CTimeTestDlg)

public:
	CTimeTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTimeTestDlg();

// 对话框数据
	enum { IDD = IDD_TIMETEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBack();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CMyButton m_back;
	CMyButton m_start;
	CMyButton m_clear;
	CListBox m_list;
	double time[5][2];
	int multi;
	CGraph* testGraph;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonAdd();
	void seqFind(string,int&,list<int>&);
	CGraph* init(CGraph*);
	afx_msg void OnCbnSelchangeCombo2();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_combo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
