#include "StdAfx.h"
#include "ShortkeyEdit.h"



void ToKeyName(UINT nChar,CString *sName)
{
	*sName = "";
	if ( (nChar>=0x30)&&(nChar<=0x39) 
		||(nChar>=0x41)&&(nChar<=0x5A) 
		) sName->AppendFormat(_T("VK_%c"),nChar); else
	if (VK_BACK==nChar)				sName->Append(_T("VK_BACKSPACE")); else
	if (VK_TAB==nChar)				sName->Append(_T("VK_TAB")); else
	if (VK_RETURN==nChar)			sName->Append(_T("VK_RETURN")); else
	if (VK_SHIFT==nChar)			sName->Append(_T("VK_SHIFT")); else
	if (VK_CONTROL==nChar)			sName->Append(_T("VK_CONTROL")); else
	if (VK_CAPITAL==nChar)			sName->Append(_T("VK_CAPITAL")) ;else
	if (VK_SPACE==nChar)				sName->Append(_T("VK_SPACE")); else
	if (VK_HOME==nChar)				sName->Append(_T("VK_HOME")) ;else
	if (VK_END==nChar)				sName->Append(_T("VK_END")); else
	if (VK_LEFT==nChar)			sName->Append(_T("VK_LEFT") );else
	if (VK_UP==nChar)			sName->Append(_T("VK_UP")); else
	if (VK_RIGHT==nChar)			sName->Append(_T("VK_RIGHT")); else
	if (VK_DOWN==nChar)			sName->Append(_T("VK_DOWN") );else
	if (VK_INSERT==nChar)			sName->Append(_T("VK_INSERT")); else
	if (VK_DELETE==nChar)			sName->Append(_T("VK_DELETE")); else
	if ( (nChar>=VK_NUMPAD0)&&(nChar<=VK_NUMPAD9) )
		sName->AppendFormat(_T("VK_NUMPAD%d"),nChar-VK_NUMPAD0); else
	if (VK_MULTIPLY==nChar)			sName->Append(_T("VK_MULTIPLY")); else
	if (VK_ADD==nChar)			sName->Append(_T("VK_ADD")) ;else
	if (VK_SEPARATOR==nChar)			sName->Append(_T("VK_SEPARATOR")); else
	if (VK_SUBTRACT==nChar)			sName->Append(_T("VK_SUBTRACT")); else
	if (VK_DECIMAL==nChar)			sName->Append(_T("VK_DECIMAL")) ;else
	if (VK_DIVIDE==nChar)			sName->Append(_T("VK_DIVIDE")) ;else
	if ( (nChar>=VK_F1)&&(nChar<=VK_F24) )
		sName->AppendFormat(_T("VK_F%d"),nChar-VK_F1+1);

	sName->AppendFormat(_T("(0x%x)"),nChar);
/*
*/
}

CShortkeyEdit::CShortkeyEdit(void)
{
	CEdit::CEdit();
}

CShortkeyEdit::~CShortkeyEdit(void)
{
}

void CShortkeyEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}
void CShortkeyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}
void CShortkeyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString txt;
	ToKeyName(nChar,&txt);
	CShortkeyEdit::SetWindowTextW(txt);
	m_VirtualKey = nChar;
	CEdit::OnKeyDown(nChar,nRepCnt,nFlags);
}


char CShortkeyEdit::GetVirtualKey(void)
{
	return m_VirtualKey;
}
void CShortkeyEdit::SetVirtualKey(UINT nChar)
{
	m_VirtualKey = nChar;
	CShortkeyEdit::OnKeyDown(nChar,0,0);
}

BEGIN_MESSAGE_MAP(CShortkeyEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
END_MESSAGE_MAP()


