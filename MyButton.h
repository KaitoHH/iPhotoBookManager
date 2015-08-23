#if !defined(AFX_MYBUTTON_H__E4B29920_109B_4D4E_9E9D_1FABA29C59A8__INCLUDED_)
#define AFX_MYBUTTON_H__E4B29920_109B_4D4E_9E9D_1FABA29C59A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton window

class CMyButton : public CButton
{
// Construction
public:
	CMyButton();
	
	BOOL	m_bIsMouseMove;
	CBitmap m_bmNormal;
	CBitmap m_bmSelect;
	CBitmap m_bmFocuse;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBitmaps(UINT nNormal, UINT nSelect, UINT nFocuse);
	void DrawFocusState(CRect rc, CDC *pDC);
	void DrawSelectedState(CRect rc, CDC *pDC);
	void DrawNormalState(CRect rc, CDC *pDC);
	virtual ~CMyButton();
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__E4B29920_109B_4D4E_9E9D_1FABA29C59A8__INCLUDED_)
