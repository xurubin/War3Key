// War3Key.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "War3Key.h"
#include "War3KeyDlg.h"
#include "xmlParser.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWar3KeyApp

BEGIN_MESSAGE_MAP(CWar3KeyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWar3KeyApp 构造

CWar3KeyApp::CWar3KeyApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CWar3KeyApp 对象

CWar3KeyApp theApp;


// CWar3KeyApp 初始化

BOOL CWar3KeyApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	HANDLE hMapping;
	hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,true,_T("War3KeyMappingShared"));
	if (!hMapping)
		hMapping = CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(KeyMappingInformation),_T("War3KeyMappingShared"));
	KeyMappingInformation *lpMapping = (KeyMappingInformation*)MapViewOfFile(hMapping,FILE_MAP_WRITE,0,0,0);
	if(!lpMapping) {
		MessageBox(0,_T("OpenFileMapping failed"),_T("Error"),0);
		return FALSE;
	}
	memset(lpMapping,0,sizeof(KeyMappingInformation));

    
	int i;
	XMLNode xMainNode;
	FILE *f;
	CWar3KeyDlg dlg;

	f = fopen("config.xml","rt");
	if(f==NULL) {
		f = fopen("config.xml","wt");
		fwrite("<?War3 KeyMapper Configuration?>",strlen("<?War3 KeyMapper Configuration?>"),1,f);
	}
	fclose(f);
	xMainNode = XMLNode::openFileHelper(_T("config.xml"));
		
	InitializeCriticalSection(&(lpMapping->CriticalSection));

	for (int i=0;i<xMainNode.nChildNode();i++) {
	
		lpMapping->OriginalKey[i] = _wtoi(xMainNode.getChildNode(i).getAttribute(_T("OriginalKey")));
		lpMapping->MappedKey[i] = _wtoi(xMainNode.getChildNode(i).getAttribute(_T("MappedKey")));
		lpMapping->nMappingCount++;
	}
	
	m_pMainWnd = &dlg;
	dlg.lpMapping = lpMapping;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	Unhook();

    xMainNode=XMLNode::createXMLTopNode(_T("War3 KeyMapper Configuration"),TRUE);
	XMLNode xNode;
	wchar_t txt[256];
	for (i=0;i<lpMapping->nMappingCount;i++) {
		_itow(i,txt,10);
		xNode=xMainNode.addChild(txt);

		_itow(lpMapping->OriginalKey[i],txt,10);
		xNode.addAttribute(_T("OriginalKey"),txt);
		_itow(lpMapping->MappedKey[i],txt,10);
		xNode.addAttribute(_T("MappedKey"),txt);
	}

    wchar_t *t=xMainNode.createXMLString(TRUE);
    size_t converted,origsize = wcslen(t) + 1;
    char* buffer = (char *)malloc(origsize);
    wcstombs_s(&converted,buffer, origsize, t, _TRUNCATE);

	f = fopen("config.xml","wt");
	fwrite(buffer,converted-1,1,f);
	fclose(f);
	free(buffer);
    free(t);

	DeleteCriticalSection(&(lpMapping->CriticalSection));
	UnmapViewOfFile(lpMapping);
	CloseHandle(hMapping);

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
