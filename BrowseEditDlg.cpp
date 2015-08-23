// BrowseEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "BrowseEditDlg.h"
#include "afxdialogex.h"


// CBrowseEditDlg 对话框

IMPLEMENT_DYNAMIC(CBrowseEditDlg, CDialogEx)

CBrowseEditDlg::CBrowseEditDlg(CWnd* pParent /*=NULL*/)
	: CMySubDlg(CBrowseEditDlg::IDD, pParent)
{

}

CBrowseEditDlg::CBrowseEditDlg(CWnd* pParent, CRect* r,ImageInfo i)
	: CMySubDlg(CBrowseEditDlg::IDD, pParent)
{
	Parent = pParent;
	fa = r;
	item = i;
}

CBrowseEditDlg::~CBrowseEditDlg()
{
}

void CBrowseEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
}


BEGIN_MESSAGE_MAP(CBrowseEditDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CBrowseEditDlg::OnBnClickedButtonBack)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CBrowseEditDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBrowseEditDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBrowseEditDlg 消息处理程序


void CBrowseEditDlg::OnPaint()
{	
	// device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CMySubDlg::OnPaint()
	CPaintDC dc(this); 

	//填充背景
	CRect rc;
	GetClientRect(&rc);// 获取客户区
	dc.FillSolidRect(&rc, RGB(42, 42, 42));   // 填充客户区颜色
	SetWindowPos(&this->wndTopMost, fa->left, fa->top, 360, fa->Height(), SWP_SHOWWINDOW);

	//填充标题
	CFont *m_Font3;
	m_Font3 = new CFont;
	m_Font3->CreatePointFont(400, CString("黑体"), NULL);
	dc.SelectObject(m_Font3);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(100, 40, _T("信息"));


	//设置EDIT控件
	CFont *m_font = new CFont;
	m_font->CreatePointFont(230, CString("微软雅黑"), NULL);
	setedit((CEdit *)GetDlgItem(IDC_EDIT1), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT2), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT3), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT4), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT5), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT6), m_font);
	setedit((CEdit *)GetDlgItem(IDC_EDIT7), m_font);

	//设置静态文本
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CFont *m_Font = new CFont;
	m_Font->CreatePointFont(150, CString("微软雅黑"), NULL);
	dc.SelectObject(m_Font);
	dc.TextOut(20, 150, CString("文件名"));
	dc.TextOut(20, 220, CString("长度"));
	dc.TextOut(20, 290, CString("宽度"));
	dc.TextOut(20, 355, CString("创建日期"));
	dc.TextOut(20, 425, CString("中文描述"));
	dc.TextOut(20, 495, CString("英文描述"));
	dc.TextOut(20, 560, CString("上传者"));
	dc.TextOut(20, 630, CString("所属地图"));

	CFont *m_Font2 = new CFont;
	m_Font2->CreatePointFont(100, CString("微软雅黑"), NULL);
	dc.SelectObject(m_Font2);
	dc.TextOut(128, 625, CString("中国"));
	dc.TextOut(250, 625, CString("华师大"));
	dc.TextOut(128, 655, CString("其他"));
}


BOOL CBrowseEditDlg::OnInitDialog()
{
	CMySubDlg::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP9, IDB_BITMAP7, IDB_BITMAP8);
	// TODO:  在此添加额外的初始化
	init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CBrowseEditDlg::OnBnClickedButtonBack()
{
	Parent->SetActiveWindow();
	OnOK();
}




HBRUSH CBrowseEditDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMySubDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID()){
		case IDC_EDIT1:
		case IDC_EDIT2:
		case IDC_EDIT3:
		case IDC_EDIT4:
		case IDC_EDIT5:
		case IDC_EDIT6:
		case IDC_EDIT7:
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(42, 42, 42));
			HBRUSH hBr = CreateSolidBrush(RGB(42, 42, 42)); // 背景色
			return (HBRUSH)hBr;
	}
	return hbr;
}

void CBrowseEditDlg::setedit(CEdit *m_edit, CFont *m_font)
{
	m_edit->SetLimitText(20);
	m_edit->SetFont(m_font, TRUE);
}

void CBrowseEditDlg::init()
{
	SetDlgItemText(IDC_EDIT1, CString(item.filename().c_str()));
	SetDlgItemInt(IDC_EDIT2, item.width());
	SetDlgItemInt(IDC_EDIT3, item.height());
	CTime time(item.time());
	SetDlgItemText(IDC_EDIT4, time.Format("%Y-%m-%d %H:%S"));
	SetDlgItemText(IDC_EDIT5, CString(item.textcn().c_str()));
	SetDlgItemText(IDC_EDIT6, CString(item.texten().c_str()));
	SetDlgItemText(IDC_EDIT7, CString(item.uper().c_str()));

	CButton* radio;
	radio = (CButton*)GetDlgItem(IDC_RADIO_1);
	radio->SetCheck(0);
	radio = (CButton*)GetDlgItem(IDC_RADIO_2);
	radio->SetCheck(0);
	radio = (CButton*)GetDlgItem(IDC_RADIO_3);
	radio->SetCheck(0);
	if (item.map().find("中国") != -1){
		radio = (CButton*)GetDlgItem(IDC_RADIO_1);
	}
	else if (item.map() == "华师大"){
		radio = (CButton*)GetDlgItem(IDC_RADIO_2);
	}
	else{
		radio = (CButton*)GetDlgItem(IDC_RADIO_3);
	}
	radio->SetCheck(1);
	
}

void CBrowseEditDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	ImageInfo newitem = item;
	CString cn, en;
	string m[] = { "中国", "华师大", "null" };
	GetDlgItemText(IDC_EDIT5, cn);
	GetDlgItemText(IDC_EDIT6, en);
	int radio = GetCheckedRadioButton(IDC_RADIO_1, IDC_RADIO_3) - IDC_RADIO_1;
	newitem.set_textcn(string(CStringA(cn)));
	newitem.set_texten(string(CStringA(en)));
	newitem.set_map(m[radio]);
	album.update(item, newitem);
	item = newitem;
	init();
	Parent->SetActiveWindow();
}


void CBrowseEditDlg::OnBnClickedButton2()
{
	init();
	Parent->SetActiveWindow();
}
