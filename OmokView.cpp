
// OmokView.cpp: COmokView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
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
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// COmokView 생성/소멸

COmokView::COmokView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	m_sunseo = true;
	m_row = 0;
	m_col = 0;
	a = 0;
	r = 0;
	c = 0;
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
	CBrush blbrush, whbrush, yelbrush, * pold;
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
	for (x = 0; x < 18; x++) {
		px += width;
		ex = px;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	// 재 초기화/
	px = start_x, py = start_y;

	// 바탕에 가로선 긋기
	for (y = 0; y < 18; y++) {
		py += width;
		ey = py;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	// 바둑돌 출력 1이면 흑돌, -1이면 백돌을 원으로 그림
	for (row = 0; row < 19; row++) {
		for (col = 0; col < 19; col++) {
			if (pDoc->baduk[row][col] == 1) { // 검정
				px = start_x + width * col - width / 2;
				py = start_y + width * col - width / 2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blbrush);
				pDC->Ellipse(px, py, ex, ey);
				pDC->SelectObject(pold);
			}
			if (pDoc->baduk[row][col] == -1) { // 검정
				px = start_x + width * col - width / 2;
				py = start_y + width * col - width / 2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blbrush);
				pDC->Ellipse(px, py, ex, ey);
				pDC->SelectObject(pold);
			}
		}
	}
	// 가비지 수집
	yelbrush.DeleteObject();
	blbrush.DeleteObject();
	whbrush.DeleteObject();
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


void COmokView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int sx, sy,/* 시작 좌표 */ ex, ey,/* 끝 좌표 */ col, row;
	double fx, fy;

	COmokDoc* pDoc = GetDocument();

	sx = 50, sy = 50;
	ex = sx + 540;
	ey = sy + 540;

	// 바둑판 밖을 좌클릭하면 가만히 있습니다
	if (point.x < sx || point.x > ex || point.y < sy || point.y > ey)
		return;

	col = (point.x - sx) / 30; // 알을 둔 위치의 x 좌표 (0~18)
	row = (point.y - sy) / 30; // 알을 둔 위치의 y 좌표 (0~18)

	// 반올림
	fx = double(point.x - sx) / 30.0;
	fy = double(point.y - sy) / 30.0;
	if (fx - col > 0.5) col++;
	if (fy - row > 0.5) row++;

	if (pDoc->baduk[row][col] == 0) {
		m_sunseo ? pDoc->baduk[row][col] = 1 : pDoc->baduk[row][col] = -1;
		m_sunseo ? m_sunseo = false : m_sunseo = true;
	}

	Invalidate(false);
	// 한 수 무르기를 위해 현재 돌 위치 저장
	m_row = row;
	m_col = col;

	CView::OnLButtonDown(nFlags, point);
}


//int COmokView::CheckVictory()
//{
	// TODO: 여기에 구현 코드 추가.
	
//	return 0;
//}


bool COmokView::CheckVictory()
{
	// TODO: 여기에 구현 코드 추가.
	// a=1이면 흑돌 오목 검사, a=-1이면 백돌 오목 검사
	// r, c는 현재 놓여진 돌의 row, col 위치
	COmokDoc* pDoc = GetDocument();
	int i;

	// 왼쪽에서 오른쪽 방향 검사
	int count = 0;
	for (i = 0; i < 19; i++) {
		if (pDoc->baduk[r][i] == a) count++;
		else count = 0;
		// 오목이면 1을 반환
		if (count == 5) return true;
	}

	// 위에서 아래 방향 검사
	count = 0;
	for (i = 0; i < 19; i++) {
		if (pDoc->baduk[i][c] == a) count++;
		else count = 0;
		// 오목이면 참 반환
		if (count == 5) return true;
	}

	// 왼쪽에서 오른쪽 방향 대각선 검사
	int srow, scol; // 왼쪽 위의 시작 위치
	int erow, ecol; // 오른쪽 아래의 끝 위치
	int tr, tc;
	tr = r; tc = c;

	while (tr != 0 && tc != 0) { // 왼쪽 위의 끝에 도달할 때까지 진행
		tr--;
		tc--;

	}
	// 왼쪽 위 끝을 검색 시작 위치로 지정
	srow = tr; scol = tc;
	
	tr = r; tc = c;
	while (tr != 18 && tc != 18) { // 왼쪽 위의 끝에 도달할 때까지 진행
		tr++;
		tc++;
	}
	
	// 오른쪽 아래의 끝을 검색 종료 위치로 지정
	erow = tr; ecol = tc;
	count = 0;

	// 지정한 시작 위치에서 종료 위치까지 오목을 검색
	while (scol <= ecol && srow <= erow) {
		if (pDoc->baduk[srow][scol] == a) count++;
		else count = 0;
		// 오목이면 참 반환
		if (count == 5) return true;
		srow++;
		scol++;
	}

	// 오른쪽에서 왼쪽 대각선 방향 검사
	tr = r; tc = c;

	while (tr != 0 && tc != 18) { // 오른쪽 위의 끝에 도달할 때까지 진행
		tr--;
		tc++;

	}
	// 오른쪽 위 끝을 검색 시작 위치로 지정
	srow = tr; scol = tc;
	
	tr = r; tc = c;
	while (tr != 18 && tc != 0) { // 왼쪽 위의 끝에 도달할 때까지 진행
		tr++;
		tc--;
	}
	
	// 왼쪽 아래의 끝을 검색 종료 위치로 지정
	erow = tr; ecol = tc;
	count = 0;

	// 지정한 시작 위치에서 종료 위치까지 오목을 검색
	while (scol <= ecol && srow <= erow) {
		if (pDoc->baduk[srow][scol] == a) count++;
		else count = 0;
		// 오목이면 참 반환
		if (count == 5) return true;
		srow++;
		scol++;
	}
	return false;
}
