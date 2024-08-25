#pragma once
#include "CComponent.h"
class CGauge :
    public CComponent
{
private:
    Vec2        m_vOffsetPos;   
    Vec2        m_vScale;
    Vec2        m_vFinalPos;    

    float       m_fTurretCoolTime;
    float       m_fCurTurretAccTime;


public:
    void SetOffset(Vec2 _offset) { m_vOffsetPos = _offset; }
    void SetScale(Vec2 _scale) { m_vScale = _scale; }

public:
    // void init();
    virtual void tick() override;
    virtual void render(HDC _dc);

    CLONE(CGauge);

    CGauge();
    ~CGauge();
};

