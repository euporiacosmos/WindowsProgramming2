
// OmokView.cpp : COmokView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// COmokView 생성/소멸

COmokView::COmokView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_sunseo = true; // 흑돌 순서
	m_row = 0;
	m_col = 0;
}

COmokView::~COmokView()
{
}

BOOL COmokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COmokView 그리기

void COmokView::OnDraw(CDC* pDC)
{
	COmokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CBrush blbrush, whbrush, yelbrush, *pold;
	int row, col;
	int x, y, px, py, ex = 590, ey = 590;

	// 바둑판 시작 x 좌표, 시작 y 좌표, 너비, 끝 x 좌표, 끝 y 좌표
	const int start_x = 50, start_y = 50, width = 30;

	px = start_x, py = start_y;

	// 노랑, 검정, 흰색 브러쉬 생성
	yelbrush.CreateSolidBrush(RGB(255, 255, 0));
	blbrush.CreateSolidBrush(RGB(0, 0, 0));
	whbrush.CreateSolidBrush(RGB(255, 255, 255));

	// 노란색 바둑판 바탕 출력
	pold = pDC->SelectObject(&yelbrush);
	pDC->Rectangle(px, py, ex, ey);
	pDC->SelectObject(pold);

	// 바탕에 세로선 긋기
	for(x=0; x<18; x++) {
		px += width;
		ex = px;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	// 재 초기화/
	px = start_x, py = start_y;

	// 바탕에 가로선 긋기
	for(y=0; y<18; y++) {
		py += width;
		ey = py;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	// 바둑돌 출력 1이면 흑돌, -1이면 백돌을 원으로 그림
	for(row=0; row<19; row++) {
		for(col=0; col<19; col++) {
			if(pDoc->baduk[row][col] == 1) { // 검정
				px = start_x +width * col - width/2;
				py = start_y +width * col - width/2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blbrush);
				pDC-> Ellipse(px,py,ex,ey);
				pDC->SelectObject(pold);
			}
			if(pDoc->baduk[row][col] == -1) { // 검정
				px = start_x +width * col - width/2;
				py = start_y +width * col - width/2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blbrush);
				pDC-> Ellipse(px,py,ex,ey);
				pDC->SelectObject(pold);
			}
		}
		// 가비지 수집
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


// COmokView 진단

#ifdef _DEBUG
void COmokView::AssertValid() const
{
	CView::AssertValid();
}

void COmokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COmokDoc* COmokView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COmokDoc)));
	return (COmokDoc*)m_pDocument;
}
#endif //_DEBUG


// COmokView 메시지 처리기
