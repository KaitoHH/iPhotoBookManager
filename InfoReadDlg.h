//InfoReadDlg.h
#pragma once
#include"file.h"
#include"iPhotoBook.h"

extern mysetting setting;
extern iPhotoBook album;
// CInfoReadDlg �Ի���

class CInfoReadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoReadDlg)

public:
	CInfoReadDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfoReadDlg();

// �Ի�������
	enum { IDD = IDD_INFOREAD};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool first;
};
