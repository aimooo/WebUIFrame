#pragma once

#include "Js2CppAssistant.h"

#include "comutil.h"
#pragma comment(lib, "comsupp.lib")


class CWebUI
{
public:
	CWebUI(HINSTANCE hInstance);
	~CWebUI(void);
private:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	void InitIWebBrowser();

public:
	virtual BOOL OnMessage(MSG msg) { return TRUE; }


public:
	int run(char* url);


//properties
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	char m_url[128];
	/*ALT*/
	CComModule _Module; 
	CAxWindow m_axWindow;
	IWebBrowser2* m_iWebBrowser;
	CComDispatchDriver m_scriptDriver;

	CJs2CppAssistant *m_pJs2CppAssistant;

// getters and setters
public:
	HINSTANCE GetInstance()	{ return m_hInstance; }
	HWND GetWindowHandle() { return m_hWnd; }
	CAxWindow getAxWindow() { return m_axWindow; }

	CComDispatchDriver GetScriptDriver();

	HRESULT SendMessage(MSG msg);
};

