#pragma once
#include "CObject.h"

class CImage;
class CLaser;

class CLaserBody :
    public CObject
{
private:
    float m_fSpeed;
    LASER_TYPE m_eLaserType;
    MOVE_DIRECTION m_eMoveDirection;

    bool m_bHasLaser;
    CLaser* m_pLaser;

    float m_fMinusMax;
    float m_fPlusMin;

    Vec2 m_vMaxBlockPos;
    Vec2 m_vMinBlockPos;

    CImage* m_pImage;

public:
    void SetMoveDir(MOVE_DIRECTION _dir) { m_eMoveDirection = _dir; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);
public:
    CLONE(CLaserBody);

public:
    CLaserBody(LASER_TYPE _laserType);
    ~CLaserBody();
};

