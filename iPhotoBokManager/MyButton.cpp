// MyButton.cpp : implementation file
//

#include "stdafx.h"
//#include "jiemian.h"
#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
	m_bIsMouseMove=FALSE;
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)//自定义的消息处理
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

//DEL void CMyButton::OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	CButton::OnDeleteItem(nIDCtl, lpDeleteItemStruct);
//DEL }

//DEL void CMyButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 
//DEL 	
//DEL 	
//DEL 	CDC* pDC      = CDC::FromHandle(lpDrawItemStruct->hDC);
//DEL 	DWORD nState  = lpDrawItemStruct->itemState;
//DEL 	DWORD nAction = lpDrawItemStruct->itemAction; 
//DEL 	CRect rc	  = lpDrawItemStruct->rcItem;
//DEL 	UINT uStyle   = DFCS_BUTTONPUSH;
//DEL 	
//DEL 	pDC->SetBkMode(TRANSPARENT);
//DEL 	CString strText;
//DEL 	GetWindowText(strText);
//DEL 	
//DEL 	if (nState & ODS_SELECTED)//select
//DEL 	{
//DEL 		m_bIsMouseMove = FALSE;
//DEL 		
//DEL 		DrawSelectedState(rc, pDC);
//DEL 	}
//DEL 	else //Normal
//DEL 	{
//DEL 		DrawNormalState(rc, pDC);
//DEL 	}
//DEL 	
//DEL 	if (m_bIsMouseMove)//hover on the button
//DEL 	{
//DEL 		DrawFocusState(rc, pDC);
//DEL 	//	::PostMessage(GetParent()->GetSafeHwnd(), WM_MOUSEONBUTTON, 0, 0);
//DEL 		
//DEL 	}
//DEL 	
//DEL 	pDC->DrawText(strText, strText.GetLength(), 
//DEL 		&lpDrawItemStruct->rcItem, 
//DEL 		DT_SINGLELINE|DT_VCENTER|DT_CENTER);
//DEL }


void CMyButton::DrawNormalState(CRect rc, CDC *pDC)
{
	
	//DrawFrame(rc, pDC);
	//	DrawFace(rc, RGB(223, 233, 255), RGB(0, 128, 255), pDC);
	//	DrawFrame(rc, RGB(230, 230, 230), RGB(128, 128, 128), pDC);
	//	pDC->SetTextColor(RGB(255, 255, 255));
	
	pDC->DrawState(CPoint(0, 0), CSize(rc.Width(), rc.Height()),
					m_bmNormal, DSS_NORMAL);

}

void CMyButton::DrawSelectedState(CRect rc, CDC *pDC)
{
	pDC->DrawState(CPoint(0, 0), CSize(rc.Width(), rc.Height()),
					m_bmSelect, DSS_NORMAL);

}

void CMyButton::DrawFocusState(CRect rc, CDC *pDC)
{
	pDC->DrawState(CPoint(0, 0), CSize(rc.Width(), rc.Height()),
					m_bmFocuse, DSS_NORMAL);
}

void CMyButton::SetBitmaps(UINT nNormal, UINT nSelect, UINT nFocuse)
{
	m_bmNormal.LoadBitmap(nNormal);
	m_bmSelect.LoadBitmap(nSelect);
	m_bmFocuse.LoadBitmap(nFocuse);

}

void CMyButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	
	if( !m_bIsMouseMove )
	{
		m_bIsMouseMove = TRUE;
		Invalidate();//导致窗口重绘
		//UpdateWindow();
		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize = sizeof(trackmouseevent);
		trackmouseevent.dwFlags = TME_LEAVE ;//追踪鼠标离开的消息
		trackmouseevent.hwndTrack = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&trackmouseevent);//此函数能发送鼠标的相关消息，离开或是盘旋
	}
	CButton::OnMouseMove(nFlags, point);
}
LONG CMyButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)//这个函数解决的问题是“我的电脑”...在鼠标离开后的显示颜色
{
	m_bIsMouseMove = FALSE;
	//::PostMessage(GetParent()->GetSafeHwnd(), WM_MOUSEOFFBUTTON, 0, 0);
	Invalidate();
	
	return 0;
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC      = CDC::FromHandle(lpDrawItemStruct->hDC);
	DWORD nState  = lpDrawItemStruct->itemState;
	DWORD nAction = lpDrawItemStruct->itemAction; 
	CRect rc	  = lpDrawItemStruct->rcItem;
	UINT uStyle   = DFCS_BUTTONPUSH;
	
	pDC->SetBkMode(TRANSPARENT);
	CString strText;
	GetWindowText(strText);

	if (nState & ODS_SELECTED)//select
	{
		m_bIsMouseMove = FALSE;
		
		DrawSelectedState(rc, pDC);
	}
	else //Normal
	{
		DrawNormalState(rc, pDC);
	}
	
	if (m_bIsMouseMove)//hover on the button
	{
		DrawFocusState(rc, pDC);
		//	::PostMessage(GetParent()->GetSafeHwnd(), WM_MOUSEONBUTTON, 0, 0);
		
	}
	
	pDC->DrawText(strText, strText.GetLength(), 
		&lpDrawItemStruct->rcItem, 
		DT_SINGLELINE|DT_VCENTER|DT_CENTER);
}

//DEL BOOL CMyButton::OnInitDialog() 
//DEL {
//DEL 	CButton::OnInitDialog();
//DEL 	
//DEL 	// TODO: Add extra initialization here
//DEL 	
//DEL 
//DEL 	return TRUE;  // return TRUE unless you set the focus to a control
//DEL 	              // EXCEPTION: OCX Property Pages should return FALSE
//DEL }
