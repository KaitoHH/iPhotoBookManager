// FootDetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "FootDetailDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <iomanip>

// CFootDetailDlg 对话框

IMPLEMENT_DYNAMIC(CFootDetailDlg, CDialogEx)

CFootDetailDlg::CFootDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFootDetailDlg::IDD, pParent)
{
	
}

CFootDetailDlg::CFootDetailDlg(CWnd* pParent /*=NULL*/,CPoint pt,int cur,int no)
	: CDialogEx(CFootDetailDlg::IDD, pParent)
{
	fa = pt;
	this->cur = cur;
	this->no = no;
}

CFootDetailDlg::~CFootDetailDlg()
{
}

void CFootDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
}


BEGIN_MESSAGE_MAP(CFootDetailDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CFootDetailDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CFootDetailDlg 消息处理程序


BOOL CFootDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_back.SetBitmaps(IDB_BITMAP9, IDB_BITMAP7, IDB_BITMAP8);
	int n;
	list<int>l;
	album.findByPosition(album.graph(cur).at(no).getName().c_str(), n, l);
	for (int i = 0; i < n; i++){
		m_list.InsertString(i, tocs(i+1, album.record(l.front())));
		l.pop_front();
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CFootDetailDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
	CRect rc;
	GetClientRect(&rc);// 获取客户区
	dc.FillSolidRect(&rc, RGB(42, 42, 42));   // 填充客户区颜色

	int da[] = { -1, 1, -1, 1 };
	int db[] = { -1, 0, -1, 0 };
	int dcc[] = { -1, -1, -1, 1 };
	int dd[] = { -1, -1, 0, 0 };
	int d = 20;
	int sx, sy;
	for (int i = 0; i < 4; i++){
		sx = fa.x + d * da[i] + rc.Width()*db[i];
		sy = fa.y + d * dcc[i] + rc.Height()*dd[i];
		if (sx > 20 && sy > 20)	break; 
	}
	SetWindowPos(NULL, sx, sy, rc.Width(), rc.Height(), SWP_SHOWWINDOW);

	CFont *m_Font3;
	m_Font3 = new CFont;
	m_Font3->CreatePointFont(400, CString("黑体"), NULL);
	dc.SelectObject(m_Font3);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(10, 10, CString(album.graph(cur).at(no).getName().c_str()));

	CFont *m_font = new CFont;
	m_font->CreatePointFont(230, CString("微软雅黑"), NULL);
	CEdit *m_edit = (CEdit *)GetDlgItem(IDC_DETAIL);
	m_edit->SetFont(m_font, TRUE);
	SetDlgItemText(IDC_DETAIL, CString(album.graph(cur).at(no).getDetail().c_str()));
	
	m_font = new CFont;
	m_font->CreatePointFont(100, CString("黑体"), NULL);
	m_list.SetFont(m_font, TRUE);

	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) ^ 0x80000);
	HINSTANCE hInst = LoadLibrary(CString("User32.DLL"));  //加载库文件
	if (hInst)
	{
		typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		MYFUNC func = NULL;	//函数指针
		//取得SetLayeredWindowAttributes函数指针 
		func = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		//使用SetLayeredWindowAttributes函数设定透明度
		if (func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 220, 0x2);
		FreeLibrary(hInst);
	}

}

CString CFootDetailDlg::tocs(int i, ImageInfo item)
{
	std::stringstream ss;
	ss << setiosflags(ios::left);

	ss << setw(5) << i;
	ss << setw(30) << item.filename().c_str();
	ss << setw(30) << item.texten().c_str();
	ss << setw(10) << item.postion().c_str();

	CString str(ss.str().c_str());
	//MessageBox(str);
	return str;
}

void CFootDetailDlg::OnBnClickedButtonBack()
{
	OnOK();
}
