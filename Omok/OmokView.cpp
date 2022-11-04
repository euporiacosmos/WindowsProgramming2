
// OmokView.cpp : COmokView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Omok.h"
#endif

#include "OmokDoc.h"
#include "OmokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COmokView

IMPLEMENT_DYNCREATE(COmokView, CView)

BEGIN_MESSAGE_MAP(COmokView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COmokView ����/�Ҹ�

COmokView::COmokView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_sunseo = true; // �浹 ����
	m_row = 0;
	m_col = 0;
}

COmokView::~COmokView()
{
}

BOOL COmokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// COmokView �׸���

void COmokView::OnDraw(CDC* pDC)
{
	COmokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CBrush blbrush, whbrush, yelbrush, *pold;
	int row, col;
	int x, y, px, py, ex = 590, ey = 590;

	// �ٵ��� ���� x ��ǥ, ���� y ��ǥ, �ʺ�, �� x ��ǥ, �� y ��ǥ
	const int start_x = 50, start_y = 50, width = 30;

	px = start_x, py = start_y;

	// ���, ����, ��� �귯�� ����
	yelbrush.CreateSolidBrush(RGB(255, 255, 0));
	blbrush.CreateSolidBrush(RGB(0, 0, 0));
	whbrush.CreateSolidBrush(RGB(255, 255, 255));

	// ����� �ٵ��� ���� ���
	pold = pDC->SelectObject(&yelbrush);
	pDC->Rectangle(px, py, ex, ey);
	pDC->SelectObject(pold);

	// ������ ���μ� �߱�
	for(x=0; x<18; x++) {
		px += width;
		ex = px;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	// �� �ʱ�ȭ/
	px = start_x, py = start_y;

	// ������ ���μ� �߱�
	for(y=0; y<18; y++) {
		py += width;
		ey = py;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	// �ٵϵ� ��� 1�̸� �浹, -1�̸� �鵹�� ������ �׸�
	for(row=0; row<19; row++) {
		for(col=0; col<19; col++) {
			if(pDoc->baduk[row][col] == 1) { // ����
				px = start_x +width * col - width/2;
				py = start_y +width * col - width/2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blbrush);
				pDC-> Ellipse(px,py,ex,ey);
				pDC->SelectObject(pold);
			}
			if(pDoc->baduk[row][col] == -1) { // ����
				px = start_x +width * col - width/2;
				py = start_y +width * col - width/2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blbrush);
				pDC-> Ellipse(px,py,ex,ey);
				pDC->SelectObject(pold);
			}
		}
		// ������ ����
		yelbrush.DeleteObject();
		blbrush.DeleteObject();
		whbrush.DeleteObject();
}

void COmokView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COmokView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COmokView ����

#ifdef _DEBUG
void COmokView::AssertValid() const
{
	CView::AssertValid();
}

void COmokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COmokDoc* COmokView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COmokDoc)));
	return (COmokDoc*)m_pDocument;
}
#endif //_DEBUG


// COmokView �޽��� ó����
