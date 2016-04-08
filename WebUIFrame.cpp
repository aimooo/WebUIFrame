// WebUIFrame.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WebUIFrame.h"

#include "MyWebUI.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)


{	
	
	char fileName[_MAX_PATH] = {0};
	char url[_MAX_PATH] = {0};
	if (GetModuleFileNameA(hInstance, fileName, _MAX_PATH));
		sprintf_s(url, "res://%s/%d", fileName, DIR_HTML_DEFAULT);

	return MyWebUI(hInstance).run(url);
}

