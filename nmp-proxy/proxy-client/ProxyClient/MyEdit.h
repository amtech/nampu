/*
 * @Author: XiaoHe
 * @Date  : 2003-03-04 
 * @Detail: ����һ���м��࣬���ڶ�CEdit �ķ�װ��Ӧ���ڡ���½���Ի����У����롰�û����������롱�ȵ�����ؼ���
 *          ��ɫ��3DЧ���������
 *			
 */

#pragma once


// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
	COLORREF m_Colour;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnNcPaint();
};


