
// MFC_CaphyonAppView.h : interface of the CMFCCaphyonAppView class
//

#pragma once


class CMFCCaphyonAppView : public CView
{
protected: // create from serialization only
	CMFCCaphyonAppView() noexcept;
	DECLARE_DYNCREATE(CMFCCaphyonAppView)

// Attributes
public:
	CMFCCaphyonAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCCaphyonAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFC_CaphyonAppView.cpp
inline CMFCCaphyonAppDoc* CMFCCaphyonAppView::GetDocument() const
   { return reinterpret_cast<CMFCCaphyonAppDoc*>(m_pDocument); }
#endif

