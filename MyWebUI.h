#pragma once
#include "WebUI.h"
class MyWebUI : public CWebUI
{
public:
	MyWebUI(HINSTANCE hInstance);
	~MyWebUI(void);


private:
	virtual BOOL OnMessage(MSG msg);
};
