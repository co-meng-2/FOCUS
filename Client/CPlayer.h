#pragma once
#include "CObject.h"

class CSound;
class CEffect;
class CImage;
class CPosChanger;

class CPlayer :
    public CObject
{
private:
    float   m_fSpeed;

    float   m_fFocusCoolTime;
    float   m_fFocusAccTime;

    float   m_fAddForceMaxTime;
    float   m_fAddForceAccTime;

    float   m_fMaxFocusRadius;
    float   m_fCurFocusRadius;
    float   m_fRadiusDeclineSpeed;
    float   m_fRadiusInclineSpeed;
    float   m_fRadiusReduce;
    
    bool    m_bFocus;
    bool    m_bDead;
    bool    m_bDeadAnimPlayed;
    bool    m_bInvincibility;
    bool    m_bHasFocus;

    bool    m_bStartAddForce;
    Vec2    m_vForceDir;
    Vec2    m_vPrevPos;
    Vec2    m_vPrevPosForAnim;

    Vec2    m_vMovedPos;

    MOVE_DIRECTION m_eMoveDir;
    bool    m_bJump;

    CPosChanger* m_pPosChanger;
    CEffect* m_pEffect;
    CSound* m_pDyingSound;
    CSound* m_pFocusSound;

public:
    void FocusPressed();
    void FocusReleased();
    void FocusCanceled();

    void StartAddForce();
    void EndAddForce();


public:
    Vec2 GetPrevPos() { return m_vPrevPos; }
    Vec2 GetMovedPos() { return m_vMovedPos; }
    float GetSpeed() { return m_fSpeed; }
    float GetCurFocusRadius() { return m_fCurFocusRadius; }
    float GetMaxFocusRadius() { return m_fMaxFocusRadius; }

    void SetStartAddForce(bool _b) { m_bStartAddForce = _b; }
    bool GetDead() { return m_bDead; }
    bool IsInvincible() { return m_bInvincibility; }
    bool GetHasFocus() { return m_bHasFocus; }
    bool IsFocus() { return m_bFocus; }

    void SubCurFocusRadius(float _radius) { m_fCurFocusRadius *= _radius; }
    void SetDead() { m_bDead = true; }
    void SetHasFocus(bool _bool) { m_bHasFocus = _bool; }
    void SetMaxFocusRadius(float _maxradius) { m_fMaxFocusRadius = _maxradius; }
    void SetCurFocusRadius(float _curradius) { m_fCurFocusRadius = _curradius; }
    

public:
    virtual void tick() override;   
    virtual void render(HDC _dc);

    /*virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;*/

public:
    virtual CPlayer* Clone() { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

