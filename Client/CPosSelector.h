#pragma once
#include "CComponent.h"

class CPosSelector :
    public CComponent
{
private:
    Vec2        m_vOffsetPos;   
    Vec2        m_vScale;
    Vec2        m_vFinalPos;   

    Vec2        m_vPlayerSwitchPos;

    float       m_fSpeedX;
    float       m_fSpeedY;
    float       m_fInRadiusSpeed;

    float       m_fAccelX;
    float       m_fAccelY;


    
    // bool        m_bOutOfMap;

public:
    void AddOffsetX();
    void SubOffsetX();
    void AddOffsetY();
    void SubOffsetY();
    void ResetOffset() { m_vOffsetPos = Vec2(0.f, 0.f); }

    Vec2 GetSwitchPos() { return m_vFinalPos; }
    Vec2 GetOffSet() { return m_vOffsetPos; }

public:
    // void init();
    virtual void tick() override;
    virtual void render(HDC _dc);

    CLONE(CPosSelector);

    CPosSelector();
    ~CPosSelector();
};

