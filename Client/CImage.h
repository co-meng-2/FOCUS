#pragma once
#include "CResource.h"

class CImage :
    public CResource
{
private:
    HBITMAP     m_hBit;
    HDC         m_hDC;

    UINT        m_iWidth;
    UINT        m_iHeight;

    bool        m_bScaleChange;
    bool        m_bTransParent;

private:
    virtual int Load(const wstring& _strFilePath) override;
    virtual int Create(UINT _iWidth, UINT _iHeight);

public:
    HDC GetDC() { return m_hDC; }
    UINT GetWidth() { return m_iWidth; }
    UINT GetHeight() { return m_iHeight; }
    bool HasScaleChange() { return m_bScaleChange; }
    bool HasTransParent() { return m_bTransParent; }

    void SetScaleChange(bool _b) { m_bScaleChange = _b; }
    void SetTransParent(bool _b) { m_bTransParent = _b; }

public:
    CImage();
    ~CImage();

    friend class CResMgr;
};

