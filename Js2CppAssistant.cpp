#include "StdAfx.h"
#include "Js2CppAssistant.h"


CJs2CppAssistant::CJs2CppAssistant(HWND hWnd)
{
	this->m_hWnd = hWnd;
}


CJs2CppAssistant::~CJs2CppAssistant(void)
{
}


HRESULT STDMETHODCALLTYPE CJs2CppAssistant::GetTypeInfoCount(UINT *pctinfo)  
{  
    return E_NOTIMPL;  
}  
  

HRESULT STDMETHODCALLTYPE CJs2CppAssistant::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)  
{  
    return E_NOTIMPL;  
}  
  
HRESULT STDMETHODCALLTYPE CJs2CppAssistant::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)  
{  
    if (wcscmp(rgszNames[0], L"SendMessage") == 0 && cNames == 1)  
    {  
        *rgDispId = WM_SCRIPT;  
        return S_OK;  
    }   else   return E_NOTIMPL;  
}  
  

HRESULT STDMETHODCALLTYPE CJs2CppAssistant::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,  
    WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)  
{  
	if (dispIdMember == DISPID_DOCUMENTCOMPLETE)
		::SendMessageW(m_hWnd, WM_HTMLDOCUMENTCOMPLETE, 0, 0);
    else if (dispIdMember == WM_SCRIPT)  
    {  
		if (pDispParams->cArgs == 2 && pDispParams->rgvarg[0].vt == VT_BSTR && pDispParams->rgvarg[1].vt == VT_BSTR )
			::SendMessageW(m_hWnd, WM_SCRIPT, (WPARAM)pDispParams->rgvarg[1].bstrVal, (WPARAM)pDispParams->rgvarg[0].bstrVal);

        return S_OK;  
    } else  
        return E_NOTIMPL;  
}  
  
HRESULT STDMETHODCALLTYPE CJs2CppAssistant::QueryInterface(REFIID riid, void **ppvObject)  
{  
    if (riid == IID_IDispatch || riid == IID_IUnknown)  
    {  
        *ppvObject = static_cast<IDispatch*>(this);  
        return S_OK;  
    }  
    else  
        return E_NOINTERFACE;  
}  
  
ULONG STDMETHODCALLTYPE CJs2CppAssistant::AddRef()  
{  
    return 1;  
}  
  
ULONG STDMETHODCALLTYPE CJs2CppAssistant::Release()  
{  
    return 1;  
}  