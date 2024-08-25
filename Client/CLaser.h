#pragma once
#include "CObject.h"
class CLaser :
    public CObject
{
public:
    virtual void tick();
    virtual void render(HDC _dc);

    // �浹 �̺�Ʈ
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);
public:
    CLONE(CLaser);

public:
    CLaser();
    ~CLaser();
};

