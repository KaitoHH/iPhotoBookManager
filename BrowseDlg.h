//BrowseDlg.h
#pragma once
#include"MySubDlg.h"
#include "MyButton.h"
#include "afxwin.h"
#include "file.h"
#include "iPhotoBook.h"
#include "BrowseSingleDlg.h"
extern mysetting setting;
extern iPhotoBook album;

// CBrowseDlg 对话框

class CBrowseDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CBrowseDlg)

public:
	CBrowseDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBrowseDlg(CWnd* pParent ,int pos);
	virtual ~CBrowseDlg();

// 对话框数据
	enum { IDD = IDD_BROWSE22 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CMyButton m_back;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBack();
	void drawPicture(CStatic *m_Pic/*控件名称*/, int no/*控件编号0-count-1*/);
	int getpos(){ return pos; }
	void init();


	CStatic m_pic1;
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_pic4;

	int fileno[MAXN];
	bool first;
	int cur;
	int pos;
	int pages;
	int eachpage;
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnBnClickedButtonNxt();
	void flush();
	afx_msg void OnBnClickedButton3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CMyButton m_next;
	CMyButton m_pre;
	
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

