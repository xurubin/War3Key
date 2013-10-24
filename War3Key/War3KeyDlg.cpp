// War3KeyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "War3Key.h"
#include "War3KeyDlg.h"
#include "SetKeyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWar3KeyDlg 对话框




CWar3KeyDlg::CWar3KeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWar3KeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWar3KeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KEYLIST, mKeyList);
	DDX_Control(pDX, IDC_BUTTONHOOK, mBtnHook);
	DDX_Control(pDX, IDBUTTONUNHOOK, mBtnUnhook);
}

BEGIN_MESSAGE_MAP(CWar3KeyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTONHOOK, &CWar3KeyDlg::OnBnClickedButtonhook)
	ON_BN_CLICKED(IDC_BUTTONLISTDELETE, &CWar3KeyDlg::OnBnClickedButtonlistdelete)
	ON_BN_CLICKED(IDBUTTONUNHOOK, &CWar3KeyDlg::OnBnClickedButtonunhook)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_KEYLIST, &CWar3KeyDlg::OnLvnItemActivateKeylist)
	ON_BN_CLICKED(IDC_BUTTONLISTADD, &CWar3KeyDlg::OnBnClickedButtonlistadd)
END_MESSAGE_MAP()


// CWar3KeyDlg 消息处理程序

BOOL CWar3KeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	////Initialize ListControl
	mKeyList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	UpdateListControl();
	///////////Finished/////////////////

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWar3KeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWar3KeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CWar3KeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWar3KeyDlg::OnBnClickedButtonhook()
{
	DWORD dwThreadId = GetWindowThreadProcessId((HWND)FindWindowA("Warcraft III",NULL),NULL);
	if (!dwThreadId) 
		dwThreadId = GetWindowThreadProcessId((HWND)FindWindowA("SWarClass",NULL),NULL);;
	if (!dwThreadId) 
		dwThreadId = GetWindowThreadProcessId((HWND)FindWindowA("StarCraft II Beta",NULL),NULL);;

	if (!dwThreadId) {
		AfxMessageBox(_T("Cannot find War3!"),MB_ICONSTOP,0);
		return;
	}
	if (Hook(dwThreadId)) {
		mBtnHook.EnableWindow(0);
		mBtnUnhook.EnableWindow(1);
	}
}

void CWar3KeyDlg::OnBnClickedButtonunhook()
{
	if (Unhook()) {
		mBtnHook.EnableWindow(1);
		mBtnUnhook.EnableWindow(0);
	}
}

void CWar3KeyDlg::UpdateListControl(void)
{
	LVCOLUMN lvColumn;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	lvColumn.pszText = _T("原始键");
	mKeyList.InsertColumn(0, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 120;
	lvColumn.pszText = _T("目标键");
	mKeyList.InsertColumn(1, &lvColumn);

	LVITEM lvItem;
	int nItem,i;
	CString txt;

	for (i=0;i<lpMapping->nMappingCount;i++)  {
		ToKeyName(lpMapping->OriginalKey[i],&txt);
		
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		lvItem.pszText =(LPWSTR)txt.GetString();
		nItem = mKeyList.InsertItem(&lvItem);

		ToKeyName(lpMapping->MappedKey[i],&txt);
		mKeyList.SetItemText(nItem, 1, txt);
	}
}

void CWar3KeyDlg::OnLvnItemActivateKeylist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int index = pNMIA->iItem;
	CSetKeyDialog dlg;
	dlg.nOriginalKey = lpMapping->OriginalKey[index];
	dlg.nMappedKey = lpMapping->MappedKey[index];

	if( dlg.DoModal()==IDOK ) {
		CString txt;
		ToKeyName(dlg.nOriginalKey,&txt);
		mKeyList.SetItemText(index,0,txt);
		ToKeyName(dlg.nMappedKey,&txt);
		mKeyList.SetItemText(index,1,txt);
		EnterCriticalSection(&(lpMapping->CriticalSection));
		lpMapping->OriginalKey[index] = dlg.nOriginalKey;
		lpMapping->MappedKey[index] = dlg.nMappedKey;
		LeaveCriticalSection(&(lpMapping->CriticalSection));
	}

}

void CWar3KeyDlg::OnBnClickedButtonlistadd()
{
	CSetKeyDialog dlg;
	dlg.nOriginalKey = VK_SPACE;
	dlg.nMappedKey = VK_SPACE;

	if( dlg.DoModal()==IDOK ) {
		CString txt;
		LVITEM lvItem;
		int nItem;
		ToKeyName(dlg.nOriginalKey,&txt);
		
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = mKeyList.GetItemCount();
		lvItem.iSubItem = 0;
		lvItem.pszText =(LPWSTR)txt.GetString();
		nItem = mKeyList.InsertItem(&lvItem);

		ToKeyName(dlg.nMappedKey,&txt);
		mKeyList.SetItemText(nItem, 1, txt);

		EnterCriticalSection(&(lpMapping->CriticalSection));
		lpMapping->nMappingCount++;
		lpMapping->OriginalKey[nItem] = dlg.nOriginalKey;
		lpMapping->MappedKey[nItem] = dlg.nMappedKey;
		LeaveCriticalSection(&(lpMapping->CriticalSection));
	}
}
void CWar3KeyDlg::OnBnClickedButtonlistdelete()
{
	int i;
	for (i=0;i<mKeyList.GetItemCount();i++) 
		if (mKeyList.GetItemState(i,LVIS_SELECTED)==LVIS_SELECTED)
		{
			mKeyList.DeleteItem(i);

			EnterCriticalSection(&(lpMapping->CriticalSection));
			for (int j=i;j<lpMapping->nMappingCount-1;j++) {
				lpMapping->OriginalKey[j] = lpMapping->OriginalKey[j+1];
				lpMapping->MappedKey[j] = lpMapping->MappedKey[j+1];
			}
			lpMapping->OriginalKey[lpMapping->nMappingCount-1] = 0;
			lpMapping->MappedKey[lpMapping->nMappingCount-1] = 0;
			lpMapping->nMappingCount--;
			LeaveCriticalSection(&(lpMapping->CriticalSection));
			break;
		}
}

