#pragma once
#include "CObject.h"

class CImage;
class CPlayer;

class CMissile :
    public CObject
{
private:
    CImage* m_pImage;
    CPlayer* m_pPlayer;

    float   m_fSpeed;
    float   m_fMaxSpeed;
    Vec2    m_vDir;
    Vec2    m_vPrevDir;

    float   m_fAngle;
    float   m_fCurvature;
    float   m_fForce;

    bool    IsLine;
    bool    IsExplosive;
    bool    HasFragments;
    bool    HasAccel;
    
    EXPLOSION_TYPE m_eExplosionType;
    
    

public:   
    void SetDir(Vec2 _vDir) 
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
    void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
    void SetExplosionType(EXPLOSION_TYPE _explType) { m_eExplosionType = _explType; }

    Vec2 GetDir() { return m_vDir; }
    float GetAngle() { return m_fAngle; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();

    friend class CMissileTurret;
};

