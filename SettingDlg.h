//SettingDlg.h
#pragma once
#include "MySubDlg.h"
#include "MyButton.h"
#include "file.h"
extern mysetting setting;
// CSettingDlg �Ի���

class CSettingDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();

// �Ի�������
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPath();
	afx_msg void OnBnClickedButtonDict();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonBack();
	CMyButton m_back;
	bool changed;
};

void show_avator(CString strFilePath, CStatic *);