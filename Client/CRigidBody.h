#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_vForce;
    Vec2    m_vAccel;
    Vec2    m_vVelocity;

    float   m_fMass;
    float   m_fFriction;
    float   m_fMaxSpeed;        // 중력이 아닌 최대 속력 제한
    float   m_fMaxGravitySpeed; // 중력에 의해 발생하는 최대 속력 제한

    Vec2    m_vGravityAccel;    // 중력 가속도
    bool    m_bUseGravity;      // 중력 적용
    bool    m_bGround;          // 땅에 서있는지 확인

    float   m_fElasticity;

    COLLISION_DIRECTION m_eColDir;


public:
    virtual void tick() override;  


public:
    void AddForce(Vec2 _vF) { m_vForce += _vF; }
    void AddVelocity(Vec2 _vVelocity) { m_vVelocity += _vVelocity; }
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }


    void SetMass(float _fMass) { m_fMass = _fMass; }
    void SetMaxSpeed(float _fMax) { m_fMaxSpeed = _fMax; }
    void SetMaxGravitySpeed(float _fMax) { m_fMaxGravitySpeed = _fMax; }
    void SetGravity(bool _bSet) { m_bUseGravity = _bSet; }
    void SetGravityAccel(Vec2 _vAccel) { m_vGravityAccel = _vAccel; }
    void SetGround(bool _bGround) { m_bGround = _bGround; }
    void SetCollisionDirection(COLLISION_DIRECTION _coldir) { m_eColDir = _coldir; }

    bool IsGround() { return m_bGround; }

public:
    CLONE(CRigidBody);

public:
    CRigidBody();
    ~CRigidBody();
};

