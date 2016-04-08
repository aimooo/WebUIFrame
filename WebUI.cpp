#include "stdafx.h"
#include "WebUI.h"

CWebUI *theApp;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

CWebUI::CWebUI(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	theApp = this;
}


CWebUI::~CWebUI(void)
{
}

ATOM CWebUI::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			=  LoadIcon( hInstance, IDI_APPLICATION );
	wcex.hCursor		=   LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"WebUIClass";
	wcex.hIconSm		= LoadIcon( hInstance, IDI_APPLICATION );

	return RegisterClassEx(&wcex);
}

BOOL CWebUI::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   m_hWnd = CreateWindow(L"WebUIClass", L"", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!m_hWnd)
   {
      return FALSE;
   }

   InitIWebBrowser();

   ShowWindow(m_hWnd, nCmdShow);
   UpdateWindow(m_hWnd);

   return TRUE;
}

int CWebUI::run(char* url)
{
	strcpy(m_url, url);

	MyRegisterClass(m_hInstance);
	if (!InitInstance (m_hInstance, SW_SHOWNORMAL))
	{
		MessageBox(m_hWnd, L"initialize window failed", L"error", 0);
		return 0;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

void CWebUI::InitIWebBrowser(void)
{
	GUID guid; 
	HRESULT hRes = _Module.Init(NULL, m_hInstance, &guid);

	RECT rc;
	GetClientRect(m_hWnd, &rc);

	m_axWindow.Create(m_hWnd, rc, 0,WS_CHILD |WS_VISIBLE);
	m_axWindow.CreateControl(OLESTR("shell.Explorer.2"));
	m_axWindow.QueryControl(__uuidof(IWebBrowser2),(void**)&m_iWebBrowser); 


	if (m_iWebBrowser) {
		IConnectionPointContainer* pCPC = NULL;
        IConnectionPoint* pCP = NULL;
		m_iWebBrowser->QueryInterface(IID_IConnectionPointContainer,(void**)&pCPC);
		pCPC->FindConnectionPoint( DIID_DWebBrowserEvents2,&pCP);

		DWORD dwCookie = 0;

		m_pJs2CppAssistant = new CJs2CppAssistant(m_hWnd);
        pCP->Advise( (IUnknown*)(void*)m_pJs2CppAssistant,&dwCookie);

		m_iWebBrowser-> Release(); 

		CComVariant g = m_url;
		m_iWebBrowser->Navigate2(&g,0,0,0,0);
	}
}


CComDispatchDriver CWebUI::GetScriptDriver() {
		if (m_scriptDriver) return m_scriptDriver;

		CComQIPtr<IDispatch> doc;
		this->m_iWebBrowser->get_Document(&doc);
		((CComQIPtr<IHTMLDocument2>)doc)->get_Script(&m_scriptDriver);
		
		CComVariant obj(static_cast<IDispatch*>(new CJs2CppAssistant(m_hWnd)));
		m_scriptDriver.PutPropertyByName(L"theApp", &obj);
		VARIANT v;
		m_scriptDriver.GetPropertyByName(L"theApp", &v);
		

		BSTR title;
		((CComQIPtr<IHTMLDocument2>)doc)->get_title(&title);
		_bstr_t a = title;
		::SetWindowText(m_hWnd, a);

		return m_scriptDriver;
	}



HRESULT CWebUI::SendMessage(MSG msg) 
{
	if (msg.message == WM_SCRIPT) {
		CComVariant wVar = (BSTR)msg.wParam;
		CComVariant lVar = (BSTR)msg.lParam;
		return m_scriptDriver.Invoke2(L"OnAppMessage", &wVar, &lVar);
	} 

	return ::SendMessageW(msg.hwnd, msg.message, msg.wParam, msg.lParam);
}

 LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	 MSG msg;
	 msg.message = message;
	 msg.hwnd = hWnd;
	 msg.wParam = wParam;
	 msg.lParam = lParam;

	// 预先处理的事件 子类重载不需要自己实现
	 if (message == WM_HTMLDOCUMENTCOMPLETE) {
		 theApp->GetScriptDriver();
	}

	//交由子类重载处理
	if (!theApp->OnMessage(msg)) return 0;

	//如果子类不重载或返回false 则父类实现默认的消息处理
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		RECT rc;
		GetClientRect(hWnd, &rc);
		rc.left = rc.top = 0;
		theApp->getAxWindow().MoveWindow(&rc, false);
		break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}
