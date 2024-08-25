#pragma once
#include "CObject.h"

#include "CPlayer.h"

class CMissileTurret :
    public CObject
{
private:
    CPlayer* m_pPlayer;

    float   m_fCoolCoolTime;
    float   m_fCoolAccTime;

    float   m_fCoolTime;
    float   m_fAccTime;
    float   m_fHideTime;
    float   m_fDetectRadius;
    
    bool    DetectPlayer;
    bool    m_bRenderGauge;

    MISSILE_OPTION m_eMissileType;
    MISSILE_OPTION m_eExplosive;
    MISSILE_OPTION m_eFragments;
    MISSILE_OPTION m_eAccel;
    float m_fForce;
    float m_fCurvature;
    float m_fStartSpeed;
    float m_fMaxSpeed;

private:

public:
    float GetCoolTime() { return m_fCoolTime; }
    float GetAccTime() { return m_fAccTime; }

    bool& GetDetectPlayer() { return DetectPlayer; }
    bool GetRenderGauge() { return m_bRenderGauge; }
    
    void SetDetectRadius(float _radius) { m_fDetectRadius = _radius; }
    void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
    void SetCoolTime(float _coolTime) { m_fCoolTime = _coolTime; }
    void SetCoolCoolTime(float _coolcoolTime) { m_fCoolCoolTime = _coolcoolTime; }
    void SetTurret(MISSILE_OPTION _missileType, MISSILE_OPTION _explosive, MISSILE_OPTION _fragments, MISSILE_OPTION _accel, float _startSpeed, float _force = 0.f, float _curvature = 0.f)
    {
        m_eMissileType = _missileType;
        m_eExplosive = _explosive;
        m_eFragments = _fragments;
        m_fForce = _force;
        m_fCurvature = _curvature;
        m_eAccel = _accel;
        m_fStartSpeed = _startSpeed;
    }

    void SetMaxSpeed(float _maxSpeed) { m_fMaxSpeed = _maxSpeed; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void SpawnMissile();
   
public:
    CLONE(CMissileTurret);

public:
    CMissileTurret();
    ~CMissileTurret();
};

