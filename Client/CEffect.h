#pragma once
#include "CObject.h"

class CImage;

class CEffect :
    public CObject
{
private:
    CObject* m_pObj;

    float m_fRatio;

    bool m_bOrder;

    CImage* m_pFocusBackground;
    CImage* m_pClocMinutekAtlas;
    CImage* m_pClockHourAtlas;

    wstring m_wCurAnimKey;

    float m_fAccTime;
    float m_fCoolTime;

    int m_iRandHour;
    int m_iRandMinute;


public:
    float GetRatio() { return m_fRatio; }

    void SetObject(CObject* _pObj) { m_pObj = _pObj; }

    CObject* GetObj() { return m_pObj; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CEffect);

public:
    CEffect();
    ~CEffect();
};

