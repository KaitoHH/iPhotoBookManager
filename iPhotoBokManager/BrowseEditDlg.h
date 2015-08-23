//BrowseEditDlg.h
#pragma once
#include "MySubDlg.h"
#include "MyButton.h"
#include "iPhotoBook.h"
extern iPhotoBook album;

// CBrowseEditDlg 对话框

class CBrowseEditDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CBrowseEditDlg)

public:
	CBrowseEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBrowseEditDlg(CWnd* pParent ,CRect*,ImageInfo);
	virtual ~CBrowseEditDlg();
	void setimage(ImageInfo i){ item = i; }

// 对话框数据
	enum { IDD = IDD_BROWSE_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CRect *fa;
	CWnd *Parent;
	ImageInfo item;
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBack();
	void setedit(CEdit *m_edit, CFont *m_font);
	void init();
	CMyButton m_back;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
};
