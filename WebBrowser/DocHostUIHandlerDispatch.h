//
// DocHostUIHandlerDispatch.h
// Copyright (c) Czarek Tomczak. All rights reserved.
//

#pragma once

// Mo�na ten interfejs zaimplementowa� na inny spos�b,
// pobieaj�c ICustomDoc z oleObject i odpalaj�c ICustomDoc::setUIHandler().

// Pe�na dokumentacja programowanie interfejs�w Internet Explorera:
// http://msdn.microsoft.com/en-us/library/ie/aa752038(v=vs.85).aspx

#include "keycodes.h"

template <class RootFrame>
class DocHostUIHandlerDispatch : public IDocHostUIHandlerDispatch
{
public:
	IOleClientSite* oleClientSite;
	WebBrowserFrameInterface<RootFrame>* webframe;
	RootFrame* rootframe;

	DocHostUIHandlerDispatch(IOleClientSite* inOleClientSite, WebBrowserFrameInterface<RootFrame>* inwebframe)
	{
		oleClientSite = inOleClientSite;
		webframe = inwebframe;
		rootframe = static_cast<RootFrame*>(webframe);
	}

	// IUnknown

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID FAR* ppvObj)
	{
		return oleClientSite->QueryInterface(riid, ppvObj);
	}
	ULONG STDMETHODCALLTYPE AddRef(void)
	{
		return 1;
	}
	ULONG STDMETHODCALLTYPE Release(void)
	{
		return 1;
	}

	// IDispatch

	HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo)
	{
		*pctinfo = 0;
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID  lcid, ITypeInfo **ppTInfo)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames,
		LCID lcid, DISPID *rgDispId)
	{
		if (riid != IID_NULL) {
			return ResultFromScode(DISP_E_UNKNOWNINTERFACE);
		}

		ASSERT_EXIT(rootframe->IsWindow(), "rootframe->IsWindow()");
		int id = rootframe->ExternalID(rgszNames[0]);
		if (id) {
			rgDispId[0] = id;
			return S_OK;
		}

		return DISP_E_UNKNOWNNAME;
	}

	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
		DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
	{
		//HRESULT		hres;
		//VARIANTARG	varg0;
		//VARIANTARG	varg1;
		//VARIANTARG	varg2;
		UINT			uArgErr;
		VARIANT		varResultDummy;

		if (riid != IID_NULL) {
			return ResultFromScode(DISP_E_UNKNOWNINTERFACE);
		}
		
		if (wFlags & ~(DISPATCH_METHOD | DISPATCH_PROPERTYGET
			| DISPATCH_PROPERTYPUT | DISPATCH_PROPERTYPUTREF)) {
			return ResultFromScode(E_INVALIDARG);
		}

		if (puArgErr == NULL) 
			puArgErr = &uArgErr;
		if (pVarResult == NULL) 
			pVarResult = &varResultDummy;

		//VariantInit(&varg0);
		//VariantInit(&varg1);
		//VariantInit(&varg2);
		VariantInit(pVarResult);

		// Currently no support for arguments, only simple function call.
		if (pDispParams->cArgs != 0) 
			return ResultFromScode(DISP_E_BADPARAMCOUNT);

		/*
			Getting 1st argument:

			hres = DispGetParam(pDispParams, 0, VT_BSTR, &varg0, puArgErr);
			if (FAILED(hres)) return ResultFromScode(DISP_E_TYPEMISMATCH);
			MessageBox(NULL, V_BSTR(&varg0), L"Title", 0);

			Returning int result:

			pVarResult->vt = VT_I4;
			pVarResult->lVal = 123;

			Returning string result:

			pVarResult->vt = VT_BSTR;
			pVarResult->bstrVal = SysAllocString(L"Returned value");
		*/

		ASSERT_EXIT(rootframe->IsWindow(), "rootframe->IsWindow()");
		bool result = rootframe->ExternalCall(dispIdMember);
		if (result) {
			return S_OK;
		}

		return ResultFromScode(DISP_E_MEMBERNOTFOUND);
	}

	// IDocHostUIHandler

	HRESULT STDMETHODCALLTYPE ShowContextMenu( 
		/* [in] */ DWORD dwID,
		/* [in] */ DWORD x,
		/* [in] */ DWORD y,
		/* [in] */ IUnknown *pcmdtReserved,
		/* [in] */ IDispatch *pdispReserved,
		/* [retval][out] */ HRESULT *dwRetVal)
	{
		*dwRetVal = S_OK;
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetHostInfo( 
		/* [out][in] */ DWORD *pdwFlags,
		/* [out][in] */ DWORD *pdwDoubleClick)
	{
		// http://msdn.microsoft.com/en-us/library/ie/aa753277(v=vs.85).aspx
		*pdwFlags = DOCHOSTUIFLAG_DISABLE_HELP_MENU | DOCHOSTUIFLAG_NO3DBORDER;

		// http://msdn.microsoft.com/en-us/library/ie/aa753276(v=vs.85).aspx
		*pdwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE ShowUI( 
		/* [in] */ DWORD dwID,
		/* [in] */ IUnknown *pActiveObject,
		/* [in] */ IUnknown *pCommandTarget,
		/* [in] */ IUnknown *pFrame,
		/* [in] */ IUnknown *pDoc,
		/* [retval][out] */ HRESULT *dwRetVal)
	{
		*dwRetVal = S_OK;
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE HideUI( void)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE UpdateUI( void)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE EnableModeless( 
		/* [in] */ VARIANT_BOOL fEnable)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE OnDocWindowActivate( 
		/* [in] */ VARIANT_BOOL fActivate)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( 
		/* [in] */ VARIANT_BOOL fActivate)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE ResizeBorder( 
		/* [in] */ long left,
		/* [in] */ long top,
		/* [in] */ long right,
		/* [in] */ long bottom,
		/* [in] */ IUnknown *pUIWindow,
		/* [in] */ VARIANT_BOOL fFrameWindow)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
		/* [in] */ DWORD_PTR hWnd,
		/* [in] */ DWORD nMessage,
		/* [in] */ DWORD_PTR wParam,
		/* [in] */ DWORD_PTR lParam,
		/* [in] */ BSTR bstrGuidCmdGroup,
		/* [in] */ DWORD nCmdID,
		/* [retval][out] */ HRESULT *dwRetVal)
	{
		HRESULT hr = S_FALSE;

		// TODO:
		// VK_BACK = backspace (history back)
		if (nMessage == WM_KEYDOWN && wParam == VK_BACK) {
			// Check if the active element is <input type=text|search|...> or <textarea>,
			// if so then allow Backspace, as it will delete text and not Back History.
			// <input type=color> is a selectbox in opera
			// <input type=date> also selectbox
			// Inputs that are certain to be text: (checked in fifefox, chrome, opera)
			// - text, search, email, tel, url, number, time.
			wchar_t* tag = new wchar_t[50];
			wchar_t* typeattr = new wchar_t[50];
			if (webframe->GetActiveElement(tag, typeattr)) {
				
				_wcsupr_s(tag, 50);
				_wcsupr_s(typeattr, 50);

				//ASSERT((wcscmp(tag, L"INPUT") == 0), "tag != INPUT");
				//DEBUGW(tag);
				//DEBUG_INT(wcslen(tag));
				
				if (wcscmp(tag, L"INPUT") == 0
					&& (wcscmp(typeattr, L"TEXT") == 0 
						|| wcscmp(typeattr, L"SEARCH") == 0
						|| wcscmp(typeattr, L"EMAIL") == 0
						|| wcscmp(typeattr, L"TEL") == 0
						|| wcscmp(typeattr, L"URL") == 0
						|| wcscmp(typeattr, L"NUMBER") == 0
						|| wcscmp(typeattr, L"TIME") == 0
					)
				) {
					hr = S_FALSE;
				}
				else if (wcscmp(tag, L"TEXTAREA") == 0) {
					hr = S_FALSE;
				}
				else {
					hr = S_OK;
				}
				//DEBUGW2(tag, typeattr);
			}
			delete[] tag;
			delete[] typeattr;
		}
	
		// This seem to work, others are just to be sure:		
		// VK_F1 = help
		// VK_F5 = refresh

		/*
		// Allow F5 refresh temporarily, editing html file.
		if (wParam == VK_F5) {
			*dwRetVal = S_FALSE;
			return hr;
		}
		*/

		if (nMessage == WM_KEYDOWN &&
			(wParam == VK_BROWSER_BACK || wParam == VK_BROWSER_FAVORITES
			|| wParam == VK_BROWSER_FORWARD || wParam == VK_BROWSER_HOME || wParam == VK_BROWSER_REFRESH
			|| wParam == VK_BROWSER_SEARCH || wParam == VK_BROWSER_STOP || wParam == VK_F1 || wParam == VK_F5
			|| wParam == VK_HELP || wParam == VK_MENU || wParam == VK_PRINT || wParam == VK_RMENU
			|| wParam == VK_LMENU || wParam == VK_ZOOM)
		) {
			// The message was handled.
			hr = S_OK;
		}
		
		// WM_SYSKEYDOWN = F10 or ALT is pressed.
		// Blocks: alt+left, alt+right - history backward/forward navigation.
		if (nMessage == WM_SYSKEYDOWN &&
			(wParam == VK_LEFT || wParam == VK_RIGHT)
		) {
			hr = S_OK;
		}

		// ctrl+f = find, allowed
		// ctrl+p = print, disable
		// ctrl+o = open, disable
		// ctrl+l = open, disable
		// ctrl+n = new window, disable
		if (nMessage == WM_KEYDOWN &&
			(wParam == VK_P || wParam == VK_O || wParam == VK_L || wParam == VK_N)
			&& (GetKeyState(VK_CONTROL)<0)
		) {
			hr = S_OK;
		}

		// ctrl+c, ctrl+x, ctrl+v, ctrl+z (undo)
		// ctrl+a (select all)
		// Let these shortcuts work.

		*dwRetVal = hr;
		return hr;
	}

	HRESULT STDMETHODCALLTYPE GetOptionKeyPath( 
		/* [out] */ BSTR *pbstrKey,
		/* [in] */ DWORD dw)
	{
		*pbstrKey = 0;
		return (S_FALSE);
	}

	HRESULT STDMETHODCALLTYPE GetDropTarget( 
		/* [in] */ IUnknown *pDropTarget,
		/* [out] */ IUnknown **ppDropTarget)
	{
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE GetExternal( 
		/* [out] */ IDispatch **ppDispatch)
	{
		//*ppDispatch = 0;
		//return E_NOTIMPL;
		
		// Returning IDispatch* is not enough, you also need to return this object in QueryInterface(),
		// when asked for IID_IDispatch, this function is just to say that "window.external" exists,
		// but it does not provide the real interface.
		*ppDispatch = (IDispatch*) this;
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE TranslateUrl( 
		/* [in] */ DWORD dwTranslate,
		/* [in] */ BSTR bstrURLIn,
		/* [out] */ BSTR *pbstrURLOut)
	{
		*pbstrURLOut = 0;
		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE FilterDataObject( 
		/* [in] */ IUnknown *pDO,
		/* [out] */ IUnknown **ppDORet)
	{
		*ppDORet = 0;
		return E_NOTIMPL;
	}
};
