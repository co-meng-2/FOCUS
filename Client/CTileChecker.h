#pragma once
#include "CObject.h"

class CPlayer;
class CMissileTurret;

class CTileChecker :
    public CObject
{
private:
    CObject*             m_pTurret;
    CObject*             m_pPlayer;

    int                  m_iCollisionCount;
    bool                 IsCollision;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) ;

public:
    virtual void tick();

    CLONE(CTileChecker);

public:
    CTileChecker(CObject* _pTurret, CObject* _pPlayer);
    ~CTileChecker();


};

