#pragma once
#include "afxwin.h"

void ToKeyName(UINT nChar,CString *sName);

class CShortkeyEdit :
	public CEdit
{
public:
	CShortkeyEdit(void);
public:
	~CShortkeyEdit(void);
	char GetVirtualKey(void);
	void SetVirtualKey(UINT nChar);

protected:
	char m_VirtualKey;

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

};

