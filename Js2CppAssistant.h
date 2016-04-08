#pragma once
#include "stdafx.h"


#include <atlbase.h>
#include <atlwin.h>

#include <ExDispid.h>
#include <Exdisp.h>

#define		WM_HTMLDOCUMENTCOMPLETE		WM_USER+10001
#define		WM_SCRIPT										WM_USER+10002

class CJs2CppAssistant:public IDispatch
{
public:
	CJs2CppAssistant(HWND hWnd);
	~CJs2CppAssistant(void);
private:
	HWND m_hWnd;

public:
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);  
  
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);  
  
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);  
  
	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);  
  
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);  
  
	virtual ULONG STDMETHODCALLTYPE AddRef();  
  
	virtual ULONG STDMETHODCALLTYPE Release();  
};

