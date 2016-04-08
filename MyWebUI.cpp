#include "StdAfx.h"
#include "MyWebUI.h"


MyWebUI::MyWebUI(HINSTANCE hInstance) : CWebUI(hInstance)
{
}


MyWebUI::~MyWebUI(void)
{
}

BOOL MyWebUI::OnMessage(MSG msg)
{
	if (msg.message == WM_SCRIPT) {
		LPCWSTR command = (LPCWSTR)msg.wParam;
		LPCWSTR arg = (LPCWSTR)msg.lParam;
		wchar_t info[128];
		swprintf(info, L"this message is received from javascript\r\ncommand: %s\r\narg: %s", command, arg);
		MessageBox(this->GetWindowHandle(), info, L"message", 0);
		
		msg.lParam = (LPARAM)L"I'v got the message and thanks!";
		this->SendMessage(msg);
	}

return true;
}