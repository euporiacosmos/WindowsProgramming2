
// OmokView.h : COmokView Ŭ������ �������̽�
//

#pragma once


class COmokView : public CView
{
protected: // serialization������ ��������ϴ�.
	COmokView();
	DECLARE_DYNCREATE(COmokView)

// Ư���Դϴ�.
public:
	COmokDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~COmokView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	bool m_sunseo;
	unsigned short m_row;
	unsigned short m_col;
};

#ifndef _DEBUG  // OmokView.cpp�� ����� ����
inline COmokDoc* COmokView::GetDocument() const
   { return reinterpret_cast<COmokDoc*>(m_pDocument); }
#endif

