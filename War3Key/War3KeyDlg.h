// War3KeyDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "shortkeyedit.h"


// CWar3KeyDlg 对话框
class CWar3KeyDlg : public CDialog
{
// 构造
public:
	CWar3KeyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WAR3KEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void UpdateListControl(void);
	KeyMappingInformation *lpMapping;
	CListCtrl mKeyList;
public:
	afx_msg void OnBnClickedButtonhook();
public:
	CButton mBtnHook;
public:
	CButton mBtnUnhook;
public:
	afx_msg void OnBnClickedButtonlistdelete();
public:
	afx_msg void OnBnClickedButtonunhook();
public:
	afx_msg void OnLvnItemActivateKeylist(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedButtonlistadd();
};
