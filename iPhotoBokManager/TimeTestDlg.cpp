// TimeTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iPhotoBookFrame.h"
#include "TimeTestDlg.h"
#include "afxdialogex.h"
#include <time.h>
#include <Windows.h>


// CTimeTestDlg 对话框

IMPLEMENT_DYNAMIC(CTimeTestDlg, CDialogEx)

CTimeTestDlg::CTimeTestDlg(CWnd* pParent /*=NULL*/)
: CMySubDlg(CTimeTestDlg::IDD, pParent)
{

}

CTimeTestDlg::~CTimeTestDlg()
{
	delete testGraph;
}

void CTimeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
	DDX_Control(pDX, IDC_BUTTON_START, m_start);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_clear);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO2, m_combo);
}


BEGIN_MESSAGE_MAP(CTimeTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CTimeTestDlg::OnBnClickedButtonBack)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTimeTestDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CTimeTestDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CTimeTestDlg::OnBnClickedButtonAdd)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTimeTestDlg::OnCbnSelchangeCombo2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTimeTestDlg 消息处理程序


void CTimeTestDlg::OnBnClickedButtonBack()
{
	OnOK();
}


BOOL CTimeTestDlg::OnInitDialog()
{
	CMySubDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_back.SetBitmaps(IDB_BITMAP9, IDB_BITMAP7, IDB_BITMAP8);
	m_start.SetBitmaps(IDB_BITMAP6, IDB_BITMAP4, IDB_BITMAP5);
	m_clear.SetBitmaps(IDB_BITMAP3, IDB_BITMAP1, IDB_BITMAP2);
	multi = 100000;
	m_combo.SetCurSel(1);

	testGraph = new CGraph();
	init(testGraph);
	CGraphSeries* series = new CGraphSeries;
	testGraph->AddSeries(series);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTimeTestDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CMySubDlg::OnPaint()
	SetTittle(_T("时间测试"));
	paintbg(&dc);

	CRect rc;
	GetClientRect(&rc);// 获取客户区
	dc.FillSolidRect(&rc, RGB(42, 42, 42));   // 填充客户区颜色

	//填充标题
	CFont *m_Font3;
	m_Font3 = new CFont;
	m_Font3->CreatePointFont(400, CString("黑体"), NULL);
	dc.SelectObject(m_Font3);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOut(100, 40, _T("时间测试"));

	//设置EDIT控件
	CFont *m_font = new CFont;
	m_font->CreatePointFont(230, CString("微软雅黑"), NULL);
	CEdit* m_edit = (CEdit *)GetDlgItem(IDC_EDIT_INPUT);
	m_edit->SetLimitText(20);
	m_edit->SetFont(m_font, TRUE);
	m_edit = (CEdit *)GetDlgItem(IDC_LIST1);
	m_edit->SetFont(m_font, TRUE);
	
	CFont *m_Font2 = new CFont;
	m_Font2->CreatePointFont(120, CString("微软雅黑"), NULL);
	dc.SelectObject(m_Font2);
	dc.TextOut(36, 532, CString("在上方输入英文描述并按回车添加"));

	CWnd* graphFrame = (CWnd*)GetDlgItem(IDC_TIMETEST);
	CDC* pDC = graphFrame->GetDC();
	testGraph->DrawGraph(pDC);
	ReleaseDC(pDC);

}


void CTimeTestDlg::OnBnClickedButtonStart()
{
	LARGE_INTEGER begin;
	LARGE_INTEGER end;
	LARGE_INTEGER frequ;
	CGraphSeries* series[5];
	int count = m_list.GetCount();
	if (!count)	return;
	album.set_fuzzy(false);
	delete testGraph;
	testGraph = new CGraph();
	testGraph = init(testGraph);
	double rate = multi;
	for (int i = 0; i < count; i++){
		series[i] = new CGraphSeries;
		CString str;
		m_list.GetText(i, str);
		string key = CStringA(str);
		int n;
		list<int>l;

		series[i]->SetLabel(str);
		QueryPerformanceFrequency(&frequ);
		QueryPerformanceCounter(&begin);
		album.findByTittle(key, n, l);
		QueryPerformanceCounter(&end);
		time[i][0] = (end.QuadPart - begin.QuadPart) / (double)frequ.QuadPart;
		l.clear();

		

		QueryPerformanceFrequency(&frequ);
		QueryPerformanceCounter(&begin);
		seqFind(key, n, l);
		QueryPerformanceCounter(&end);
		time[i][1] = (end.QuadPart - begin.QuadPart) / (double)frequ.QuadPart;
		l.clear();

		if (i == 0){
			rate = multi*0.95 * 10 / time[i][1];
			//init(testGraph);
		}
		series[i]->SetData(0, time[i][0] * rate);
		series[i]->SetData(1, time[i][1] * rate);

		testGraph->AddSeries(series[i]);
	}
	testGraph->SetLegend(0, _T("Trie"));
	testGraph->SetLegend(1, _T("Sequence"));
	testGraph->SetColor(0, RGB(255, 0, 0));
	testGraph->SetColor(1, RGB(0,255, 0));

	CRect r;
	CStatic *m_static = (CStatic*)GetDlgItem(IDC_TIMETEST);
	m_static->GetWindowRect(&r);
	ScreenToClient(r);
	InvalidateRect(&r);

}


void CTimeTestDlg::OnBnClickedButtonClear()
{
	m_list.ResetContent();
}


void CTimeTestDlg::OnBnClickedButtonAdd()
{
	int count = m_list.GetCount();
	CString str;
	GetDlgItemText(IDC_EDIT_INPUT, str);
	if (str.GetLength())	{
		if (count >= 5){
			MessageBox(_T("您最多只能添加5个词条！"));
			return;
		}
		m_list.AddString(str);
	}
	SetDlgItemText(IDC_EDIT_INPUT, CString(""));
}

void CTimeTestDlg::seqFind(string key,int &n,list<int> &l)
{
	n = 0;
	l.clear();
	int d = -1;
	int size = album.size();
	for (int i = 0; i < size; i++){
		d = album.next(d);
		if (album.record(d).texten() == key){
			l.push_back(d);
			n++;
		}
	}
}

CGraph* CTimeTestDlg::init(CGraph* g)
{
	g->SetGraphTitle(CString("时间测试结果"));
	g->SetTickRange(10 * multi);
	g->SetTickSpace(1 * multi);
	g->SetXAxisAlignment(0);
	g->SetXAxisLabel(_T("搜索词条"));
	g->SetYAxisLabel(_T("用时"));
	return g;
}

void CTimeTestDlg::OnCbnSelchangeCombo2()
{
	int id = m_combo.GetCurSel();
	testGraph->SetGraphType(!id);
	CRect r;
	CStatic *m_static = (CStatic*)GetDlgItem(IDC_TIMETEST);
	m_static->GetWindowRect(&r);
	ScreenToClient(r);
	InvalidateRect(&r);
}


BOOL CTimeTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CTimeTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMySubDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(42, 42, 42));
	HBRUSH hBr = CreateSolidBrush(RGB(42, 42, 42)); // 背景色
	return (HBRUSH)hBr;
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;
}
