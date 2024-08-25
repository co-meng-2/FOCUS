#pragma once
#include "CObject.h"

class CImage;

class CFragments :
    public CObject
{
    CImage* m_pImage;

    float m_fAccTime;
    float m_fDuration;
    Vec2  m_vRandomForce;

    Vec2  m_vPrevPos;
    Vec2  m_vMovedPos;

public:
    Vec2 GetMovedPos() { return m_vMovedPos; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    CFragments* Clone() { return new CFragments(*this); }

public:
    CFragments();
    ~CFragments();
};

