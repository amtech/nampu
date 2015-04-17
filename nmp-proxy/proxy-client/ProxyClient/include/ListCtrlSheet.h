#pragma once


#define WM_LSTCTR_MSG			(WM_USER + 123)				//�Զ�����Ϣ(LPARAM-��ʾST_LSTCTR_MSG����)

//
#define WM_LSTCTR_CLICK			1							//������Ϣ
#define WM_LSTCTR_RCLICK		2							//�Ҽ���Ϣ

typedef struct
{
	UINT		uMsg;				//��Ϣ
	POINT		pt;					//���λ��
	int			nSelectItem;		//ѡ����
	LRESULT		lResult;			//�Ƿ���, 0-����, ����ֵ-������
}ST_LSTCTR_MSG, *PST_LSTCTR_MSG;

// CListCtrlSheet

class CListCtrlSheet : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlSheet)

public:
	CListCtrlSheet();
	virtual ~CListCtrlSheet();

public:
	BOOL Create(DWORD dwStyle, const RECT& rc, CWnd* pParent, UINT uID);
	BOOL AddItemText(int nItem, LPWSTR szText);
	BOOL AddItemIcon(int nItem, HICON hIcon);
	HWND SetOwnWnd(HWND hWnd);
	UINT SetOwnMsg(UINT uMsg);
	HICON GetItemIcon(int nItem);

protected:
	void InitList();
	void DrawGradientLine(CDC* pDC, COLORREF crLine, POINT ptStart, POINT ptEnd);
protected:
	CImageList			m_ImgList;
	COLORREF			m_crTextBKSelect;
	COLORREF			m_crSplitItem;
	CFont				m_ftList;

	HWND				m_hWndRecMsg;
	UINT				m_uMsg;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


