//
// HTMLOMWindowServices.h
// Copyright (c) Czarek Tomczak. All rights reserved.
//

#pragma once

#include "WebBrowserFrameInterface.h"

template <class RootFrame>
class HTMLOMWindowServices : public IHTMLOMWindowServices
{
public:
    WebBrowserFrameInterface<RootFrame>* webframe;

    HTMLOMWindowServices(WebBrowserFrameInterface<RootFrame>* inwebframe)
    {
        webframe = inwebframe;
    }
    ~HTMLOMWindowServices(){}

    // IUnknown

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject)
    {
        return E_NOTIMPL;
    }
    ULONG STDMETHODCALLTYPE AddRef()
    {
        return 1;
    }
    ULONG STDMETHODCALLTYPE Release()
    {
        return 1;
    }

    // IHTMLOMWindowServices

    HRESULT STDMETHODCALLTYPE moveTo(LONG x, LONG y)
    {
        SetWindowPos(webframe->GetHWND(), NULL, (int) x, (int) y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE moveBy(LONG x, LONG y)
    {
        return E_NOTIMPL;
    }
    HRESULT STDMETHODCALLTYPE resizeTo(LONG x, LONG y)
    {
        SetWindowPos(webframe->GetHWND(), NULL, 0, 0, (int) x, (int) y, SWP_NOMOVE | SWP_NOZORDER);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE resizeBy(LONG x, LONG y)
    {
        return E_NOTIMPL;
    }
};
