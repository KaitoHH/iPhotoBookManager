//InfoReadDlg.h
#pragma once
#include"file.h"
#include"iPhotoBook.h"

extern mysetting setting;
extern iPhotoBook album;
// CInfoReadDlg 对话框

class CInfoReadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoReadDlg)

public:
	CInfoReadDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInfoReadDlg();

// 对话框数据
	enum { IDD = IDD_INFOREAD};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool first;
};
