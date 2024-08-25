#pragma once
#include "CObject.h"

class CImage;
class CSound;

class CCrystal :
    public CObject
{
    CRYSTAL_TYPE m_eCT;
    CImage* m_pImage;
    CSound* m_pSound;

    Vec2 m_vOriginPos;

    float m_fAccTime;
    float m_fShakeTime;
    float m_fCoolTime;

    bool m_bShakeDir;
    bool m_bShakeStart;
    
public:
    void SetOriginPos(Vec2 _pos) { m_vOriginPos = _pos; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);


public:
    CLONE(CCrystal);

public:
    CCrystal(CRYSTAL_TYPE _CT);
    ~CCrystal();
};

