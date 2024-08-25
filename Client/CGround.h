#pragma once
#include "CObject.h"

class CCollider;

class CGround :
    public CObject
{
private:


public:
    virtual void tick() override;    
    virtual void CollisionBeginOverlap(CCollider* _pCollider) override;
    virtual void CollisionOverlap(CCollider* _pCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pCollider) override;


    CLONE(CGround);
public:
    CGround();
    ~CGround();
};

