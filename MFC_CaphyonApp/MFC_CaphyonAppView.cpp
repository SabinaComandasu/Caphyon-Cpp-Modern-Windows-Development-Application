
// MFC_CaphyonAppView.cpp : implementation of the CMFCCaphyonAppView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_CaphyonApp.h"
#endif

#include "MFC_CaphyonAppDoc.h"
#include "MFC_CaphyonAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCaphyonAppView

IMPLEMENT_DYNCREATE(CMFCCaphyonAppView, CView)

BEGIN_MESSAGE_MAP(CMFCCaphyonAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCCaphyonAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCCaphyonAppView construction/destruction

CMFCCaphyonAppView::CMFCCaphyonAppView() noexcept
{
	// TODO: add construction code here

}

CMFCCaphyonAppView::~CMFCCaphyonAppView()
{
}

BOOL CMFCCaphyonAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCCaphyonAppView drawing

void CMFCCaphyonAppView::OnDraw(CDC* /*pDC*/)
{
	CMFCCaphyonAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCCaphyonAppView printing


void CMFCCaphyonAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCCaphyonAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCCaphyonAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCCaphyonAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCCaphyonAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCCaphyonAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCCaphyonAppView diagnostics

#ifdef _DEBUG
void CMFCCaphyonAppView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCCaphyonAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCCaphyonAppDoc* CMFCCaphyonAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCCaphyonAppDoc)));
	return (CMFCCaphyonAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCCaphyonAppView message handlers
