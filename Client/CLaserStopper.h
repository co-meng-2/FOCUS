#pragma once
#include "CObject.h"
class CLaserStopper :
    public CObject
{
public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);
public:
    CLONE(CLaserStopper);

public:
    CLaserStopper();
    ~CLaserStopper();
};

