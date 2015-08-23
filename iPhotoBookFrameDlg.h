
// iPhotoBookFrameDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "BrowseDlg.h"
#include "SettingDlg.h"
#include "file.h"
#include "WelcomeDlg.h"
#include "InfoReadDlg.h"
#include "iPhotoBook.h"
#include "BrowseSingleDlg.h"
#include "InsertDlg.h"
#include "FootDlg.h"
#include "TimeTestDlg.h"
#include "Picture.h"
// CiPhotoBookFrameDlg 对话框

class CiPhotoBookFrameDlg : public CDialogEx
{
// 构造
public:
	CiPhotoBookFrameDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_IPHOTOBOOKFRAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	void switchTo();
	void switchBack();
	CString genStr(int,string,string,string);

	bool first;
	CMyButton m_browse;
	CMyButton m_search;
	CMyButton m_edit;
	CMyButton m_insert;
	CMyButton m_delete;
	CMyButton m_footprint;
	CMyButton m_timetest;
	CMyButton m_setting;
	CMyButton m_close;
	CMyButton m_about;
	CEdit m_edit_search;
	list<int>fileno;

	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonAbout();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnSetfocusEdit1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnEnKillfocusEdit1();
	CMyButton m_back;
	afx_msg void OnBnClickedButtonBack();
	CStatic m_m1;
	CStatic m_m2;
	CStatic m_nans;
	afx_msg void OnStnClickedNans();
	afx_msg void OnBnClickedButtonSearch();
	CStatic m_time;

	CListBox m_list;
	afx_msg void OnBnClickedBitmapInsert();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnLbnDblclkList();
	afx_msg void OnBnClickedButtonFootprint();
	afx_msg void OnBnClickedBitmapTimetest();


	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

bool hasCN(string s);