#pragma once
#include "CObject.h"

class CImage;
class CPlayer;

class CEnforcer :
    public CObject
{
private:
    float m_fEnforceRadius;

    CImage* m_pImage;
    CPlayer* m_pPlayer;

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE(CEnforcer);

public:
    CEnforcer();
    ~CEnforcer();
};

