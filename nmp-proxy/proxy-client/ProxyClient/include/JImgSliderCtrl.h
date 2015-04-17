#pragma once


// CImgSliderCtrl
class CJThumbButton;

class CJImgSliderCtrl : public CWnd
{
public:
	CJImgSliderCtrl();
	virtual ~CJImgSliderCtrl();
public:	
	//��������
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//����ͼƬ
	void SetImage(const char* szImgName);
	void SetImage(CImage* pImg);
	void SetThumbImage(const char* szImgNameNormal , const char* szImgNameSelect  = NULL, int nJpgLeft = 0 , int nJpgTop = 0);
	void SetThumbImage(CImage* pImgNormal, CImage* pImgSelect = NULL, int nJpgLeft = 0 , int nJpgTop = 0);
	void SetVert(BOOL bVERT = TRUE);
	void SetToolTip(CToolTipCtrl* pToolTip);
	void SetProBKColor(COLORREF crProcBK){m_crProBKColor = crProcBK;}
	//
	long GetImgWidth();
	long GetImgHeight();
	//�����ƶ����߽籣������
	void SetThumbRectMargin(long lPixel);
	void SetThumbImgMargin(long lPixel);
	//�����ƶ���Χ
	void SetRange(long lMin, long lMax);
	//��ȡ�ƶ���Χ
	void GetRange(long& lMin, long& lMax);
	//���õ�ǰλ��
	void SetPos(long lPos);
	//��ȡ��ǰλ��
	long GetPos();
	//���õ����ƶ���С
	long SetLineSize(long lSize);
	//�Ƿ����϶�״̬
	BOOL IsMovingPos();
	//�Ƿ����
	void EnableProcBK(BOOL bProcBK = TRUE){m_bEnableProcBK = bProcBK;}
protected:
	void UpdateThumbPlace();
	void OnThumbMove(const CPoint& ptPre, const CPoint& ptCur,BOOL bSendChangedMsg);
	void OnThumbRelease(const CPoint& ptPre, const CPoint& ptCur);	
	CImage* GetImage();
	void DrawProColor(CRect& rcProc);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PreSubclassWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnEnable(WPARAM,LPARAM);
	afx_msg void OnToolTipNotify(NMHDR * pNMHDR, LRESULT * pResult);
protected:
	BOOL			m_bVERT;
	CJThumbButton*	m_pbtThumb;
	CImage*			m_pImgOuter;
	CImage			m_image;
	long			m_lThumbMarginPixel;
	long			m_lMarginPixel;
	long			m_lRangeMin;
	long			m_lRangeMax;
	long			m_lCurPos;
	long			m_lLineSize;
	BOOL			m_bMoving;

	BOOL			m_bCreate;
	friend class CJThumbButton;
	CRect			m_rcCurPro;
	COLORREF		m_crProBKColor;
	BOOL			m_bEnableProcBK;
};


// CJThumbButton

class CJThumbButton : public CImgButton
{
protected:
	CJThumbButton(CJImgSliderCtrl* pSliderWnd);
	virtual ~CJThumbButton();

protected:
	CJImgSliderCtrl*	m_pSliderWnd;
	BOOL			m_bCapture;
	CPoint			m_ptLastCapture;

	void ShowToolTip();
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	friend class CJImgSliderCtrl;
};


