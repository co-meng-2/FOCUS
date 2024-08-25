#pragma once
#include "CObject.h"

class CPlayer;
class CMissileTurret;

struct tSlopeDot
{
    float slope;
    Vec2 dot;
};

typedef tSlopeDot SD;

class CBlockChecker :
    public CObject
{
private:
    CPlayer* m_pPlayer;
    CMissileTurret* m_pTurret;

    bool IsBlock;
    float m_fSlope;

public:
    float CalSlope(Vec2 _vL, Vec2 _vR);

public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    CLONE(CBlockChecker);

public:
    CBlockChecker(CPlayer* _pPlayer, CMissileTurret* _pTurret);
    ~CBlockChecker();
};

