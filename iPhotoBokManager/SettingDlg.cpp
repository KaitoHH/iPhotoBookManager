// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include <iostream>

// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CMySubDlg(CSettingDlg::IDD, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CSettingDlg::OnBnClickedButtonPath)
	ON_BN_CLICKED(IDC_BUTTON_DICT, &CSettingDlg::OnBnClickedButtonDict)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CSettingDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnPaint()
{
	CMySubDlg::SetTittle(CString("设置"));
	CMySubDlg::OnPaint();
	
	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont *m_Font = new CFont;
	m_Font->CreatePointFont(175, CString("华文中宋"), NULL);
	dc.SelectObject(m_Font);

	dc.TextOut(240, 155, CString("您的图片库名称"));
	dc.TextOut(240, 312, CString("图片库封面"));
	dc.TextOut(240, 460, CString("图片库路径"));
	dc.TextOut(240, 575, CString("浏览方式"));
	dc.TextOut(240, 660, CString("搜索方式"));
	delete m_Font;

	m_Font = new CFont;
	m_Font->CreatePointFont(120, CString("华文中宋"), NULL);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(457, 580, CString("2 * 2"));
	dc.TextOut(822, 580, CString("2 * 3"));
	dc.TextOut(457, 660, CString("智能模糊搜索"));
	
	//图片库封面
	CStatic *m_pic = (CStatic *)GetDlgItem(IDC_IMAGE);
	show_avator(CString(setting.avatorpath.c_str()), m_pic);
}




BOOL CSettingDlg::OnInitDialog()
{
	CMySubDlg::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP_BACK, IDB_BITMAP_BACK_SELECT, IDB_BITMAP_BACK_FOCUS);

	changed = false;
	// 在此添加额外的初始化
	CRect rect;
	CFont *m_Font;
	CEdit *m_edit;
	m_Font = new CFont;

	//图片库名称
	m_edit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	m_edit->SetLimitText(20);
	m_edit->GetWindowRect(rect);
	m_Font->CreatePointFont(rect.Height() * 5.7, CString("华文中宋"), NULL);
	m_edit->SetFont(m_Font, TRUE);
	SetDlgItemText(IDC_EDIT_NAME, CString(setting.libname.c_str()));

	//图片库路径
	m_edit = (CEdit*)GetDlgItem(IDC_EDIT_DICT);
	m_edit->SetFont(m_Font, TRUE);
	SetDlgItemText(IDC_EDIT_DICT, CString(setting.libpath.c_str()));

	//浏览方式处理
	int d = setting.browse;
	CButton *radio;
	if (d == 0)		radio = (CButton*)GetDlgItem(IDC_RADIO1);
	else            radio = (CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(1);

	//搜索方式处理
	radio = (CButton*)GetDlgItem(IDC_CHECK1);
	radio->SetCheck(setting.ssearch == 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSettingDlg::OnBnClickedButtonPath()
{
	// 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("图片文件(*.jpg;*.jpeg;*.bmp;*.png)|*.jpg;*.jpeg;*.bmp;*.png||");
	CFileDialog fileDlg(true, NULL, NULL, 0, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal()){
		strFilePath = fileDlg.GetPathName();
		CStatic *m_pic = (CStatic *)GetDlgItem(IDC_IMAGE);
		show_avator(strFilePath, m_pic);
		setting.avatorpath = CStringA(strFilePath);
	}
}


void CSettingDlg::OnBnClickedButtonDict()
{
	// 在此添加控件通知处理程序代码

	//选择输出路径  
	TCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;//这个是输出缓冲区   
	bi.lpszTitle = _T("请选择图片库文件夹："); //标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//使用新的界面,在win7中效果较好//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);//弹出对话框   %s"), szDir);
	
	if (SHGetPathFromIDList(pidl, szDir)){
		SetDlgItemText(IDC_EDIT_DICT, szDir);
		changed = true;
	}
	else if (pidl != NULL)
		MessageBox(_T("选择错误！")); 
	
	
}


HBRUSH CSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMySubDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// 在此更改 DC 的任何特性

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_RADIO1:
		case IDC_RADIO2:
			CRect rc;
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			CDC* dc = GetDC();
			pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);       //把父窗口背景图片先画到按钮上
			ReleaseDC(dc);
			return (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}
	// 如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void show_avator(CString strFilePath,CStatic *m_pic)
{
	CImage *pImage = new CImage();
	HRESULT ret = pImage->Load(strFilePath);
	if (FAILED(ret))		return;
	CRect rect;
	m_pic->GetWindowRect(rect);

	CDC* pDC = m_pic->GetWindowDC();
	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	pImage->StretchBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height());
	pImage->Draw(pDC->m_hDC, rect);
}

void CSettingDlg::OnBnClickedButtonBack()
{
	// TODO:  在此添加控件通知处理程序代码
	if(changed)	MessageBox(_T("若您修改了图片库路径，则将在下一次启动时生效"));
	CString name, dict;
	GetDlgItemText(IDC_EDIT_NAME, name);
	GetDlgItemText(IDC_EDIT_DICT, dict);
	setting.libname = CStringA(name);
	setting.libpath = CStringA(dict);
	//TODO: 按钮处理
	setting.browse = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) - IDC_RADIO1;
	setting.ssearch = (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1));
	creatfile();
	OnOK();
}
