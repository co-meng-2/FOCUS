#pragma once
#include "CObject.h"

class CPlayer;

class CPosChanger :
    public CObject
{
private:
    Vec2        m_vOffsetPos;
    Vec2        m_vScale;
    Vec2        m_vFinalPos;

    float       m_fSpeed;
    float       m_fSpeedX;
    float       m_fSpeedY;
    float       m_fInRadiusSpeed;

    float       m_fAccelX;
    float       m_fAccelY;

    bool        m_bOntheBlock;

    CPlayer*    m_pPlayer;

    CImage*     m_pImage;
    CImage*     m_pImage2;

    MOVE_DIRECTION m_eMD;


    // bool        m_bOutOfMap;

public:
    void AddOffsetX();
    void SubOffsetX();
    void AddOffsetY();
    void SubOffsetY();
    void ResetOffset() { m_vOffsetPos = Vec2(0.f, 0.f); }

    void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }

    Vec2 GetSwitchPos() { return m_vFinalPos; }
    Vec2 GetOffSet() { return m_vOffsetPos; }

    bool IsOntheBlock() { return m_bOntheBlock; }

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    // void init();
    virtual void tick() override;
    virtual void render(HDC _dc);

    CLONE(CPosChanger);

    CPosChanger();
    ~CPosChanger();
};

