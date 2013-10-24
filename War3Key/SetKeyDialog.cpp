// SetKeyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "War3Key.h"
#include "SetKeyDialog.h"
#include "ShortkeyEdit.h"


// CSetKeyDialog dialog

IMPLEMENT_DYNAMIC(CSetKeyDialog, CDialog)

CSetKeyDialog::CSetKeyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetKeyDialog::IDD, pParent)
{
}

CSetKeyDialog::~CSetKeyDialog()
{
}

BOOL CSetKeyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_OriginalKey.SetVirtualKey(nOriginalKey);
	m_MappedKey.SetVirtualKey(nMappedKey);
	m_OriginalKey.SetFocus();
	return 0;
}

INT_PTR CSetKeyDialog::DoModal()
{
	INT_PTR rtn = CDialog::DoModal();
	nOriginalKey = m_OriginalKey.GetVirtualKey();
	nMappedKey = m_MappedKey.GetVirtualKey();
	return rtn;
}

void CSetKeyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITORIGINALKEY, m_OriginalKey);
	DDX_Control(pDX, IDC_EDITOBJECTKEY, m_MappedKey);
}


BEGIN_MESSAGE_MAP(CSetKeyDialog, CDialog)
END_MESSAGE_MAP()


// CSetKeyDialog message handlers
