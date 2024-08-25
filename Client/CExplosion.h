#pragma once
#include "CObject.h"
class CExplosion :
    public CObject
{
private:
    float m_fAccTime;
    float m_fDuration;

    EXPLOSION_TYPE  m_eExplosionType;

public:
   

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    CExplosion* Clone() { return new CExplosion(*this); }

public:
    CExplosion(EXPLOSION_TYPE _et);
    ~CExplosion();

};

