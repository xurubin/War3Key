#pragma once
#include "shortkeyedit.h"


// CSetKeyDialog dialog

class CSetKeyDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetKeyDialog)

public:
	CSetKeyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetKeyDialog();

	BOOL OnInitDialog();
	UINT nOriginalKey,nMappedKey;
	INT_PTR DoModal();
// Dialog Data
	enum { IDD = IDD_SETKEYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CShortkeyEdit m_OriginalKey;
public:
	CShortkeyEdit m_MappedKey;
};
