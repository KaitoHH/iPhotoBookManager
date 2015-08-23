//FootDlg.h
#pragma once
#include "MySubDlg.h"
#include "iPhotoBook.h"
#include "FootDetailDlg.h"
#include "MyButton.h"
extern iPhotoBook album;
// CFootDlg �Ի���

class CFootDlg : public CMySubDlg
{
	DECLARE_DYNAMIC(CFootDlg)

public:
	CFootDlg(CWnd* pParent = NULL);   // ��׼���캯��

	virtual ~CFootDlg();

// �Ի�������
	enum { IDD = IDD_FOOTPRINT };
	double rate;
	string map[MAX_MAP];
	int cur;
	CFootDetailDlg *dlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void init(int k);
	afx_msg void OnBnClickedButtonSwitch();
	CMyButton m_switch;
	CMyButton m_back;
	afx_msg void OnBnClickedButtonBack();
};
