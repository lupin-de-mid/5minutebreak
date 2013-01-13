// not used currently... as we implemented DocHostUIHandlerDispatch()
// and this is nore more needed.

//
// OleInPlaceSite.h
// Copyright (c) Czarek Tomczak. All rights reserved.
//

#pragma once

#include "WebBrowserFrameInterface.h"

template <class RootFrame>
class OleInPlaceSite : public IOleInPlaceSite
{
public:
    IOleClientSite* oleClientSite;
    IOleInPlaceFrame* oleInPlaceFrame;
    WebBrowserFrameInterface<RootFrame>* webframe;

    OleInPlaceSite(
        IOleClientSite* inOleClientSite,
        IOleInPlaceFrame* inOleInPlaceFrame,
        WebBrowserFrameInterface<RootFrame>* inwebframe)
    {
        oleClientSite = inOleClientSite;
        webframe = inwebframe;
        oleInPlaceFrame = inOleInPlaceFrame;
    }
public:

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

    // IOleWindow

    HRESULT STDMETHODCALLTYPE GetWindow(HWND FAR* lphwnd)
    {
        *lphwnd = webframe->View_GetHWND();
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode)
    {
        return E_NOTIMPL;
    }

    // IOleInPlaceSite

    HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void)
    {
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void)
    {
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnUIActivate(void)
    {
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetWindowContext(LPOLEINPLACEFRAME FAR* lplpFrame,
        LPOLEINPLACEUIWINDOW FAR* lplpDoc, LPRECT lprcPosRect, LPRECT lprcClipRect,
        LPOLEINPLACEFRAMEINFO lpFrameInfo)
    {
        *lplpFrame = oleInPlaceFrame;
        *lplpDoc = 0;
        lpFrameInfo->fMDIApp = FALSE;
        lpFrameInfo->hwndFrame = webframe->GetHWND();
        lpFrameInfo->haccel = 0;
        lpFrameInfo->cAccelEntries = 0;
        return (S_OK);
    }

    HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtent)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE DiscardUndoState(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect)
    {
        HRESULT hr;

        CComQIPtr<IOleObject> oleObject;
        CComQIPtr<IWebBrowser2> webBrowser;
        int ctrlid = webframe->View_GetDlgCtrlID();

        hr = webframe->Self_GetDlgControl(ctrlid, IID_IWebBrowser2, (void**) &webBrowser);
        ASSERT_EXIT(SUCCEEDED(hr), "g_webframe->Self_GetDlgControl(IID_IWebBrowser2) failed");

        hr = webBrowser->QueryInterface(IID_IOleObject, (void**) &oleObject);
        ASSERT_EXIT(SUCCEEDED(hr), "webBrowser->QueryInterface(IID_IOleObject)");

        CComQIPtr<IOleInPlaceObject> oleInPlaceObject;
        hr = oleObject->QueryInterface(IID_IOleInPlaceObject, (void**) &oleInPlaceObject);
        ASSERT_EXIT(SUCCEEDED(hr), "webBrowser->QueryInterface(IID_IOleINPlaceObject)");

        oleInPlaceObject->SetObjectRects(lprcPosRect, lprcPosRect);

        return S_OK;

        // CComQIPtr does automatic releases!
        // off: oleInPlaceObject->Release();
        // off: oleObject->Release();
        // off: webBrowser->Release();
    }

};
