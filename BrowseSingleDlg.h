//BrowseSingleDlg.h
#pragma once
#include "MySubDlg.h"
#include "MyButton.h"
#include "iPhotoBook.h"
#include "file.h"
#include "afxwin.h"
#include "BrowseEditDlg.h"

extern iPhotoBook album;
extern mysetting setting;
// CBrowseSingleDlg 对话框

class CBrowseSingleDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CBrowseSingleDlg)
public:
	CBrowseSingleDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBrowseSingleDlg(CWnd* pParent , int *fileno,int cur,int all);
	virtual ~CBrowseSingleDlg();

// 对话框数据
	enum { IDD = IDD_BROWSE_SINGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	int *fileno;
	int all;
	int cur;
	bool play;
	ImageInfo item;
	CStatic m_pic;
	CMyButton m_back;
	CBrowseEditDlg *dlg;
public:
	afx_msg void OnPaint();
	void drawpic();
	void flush();
	int getcur(){ return cur; };
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonBack();

	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonPre();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButtonPlay();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();

	CMyButton m_change;
	CMyButton m_delete;
	CMyButton m_auto;
	CMyButton m_pre;
	CMyButton m_next;
};
