#pragma once

#include "CEntity.h"
#include "CCamera.h"

class CComponent;
class AI;
class CCollider;
class CAnimator;
class CRigidBody;
class CPosSelector;

class CObject :
    public CEntity
{
private:
    vector<vector<CComponent*>> m_varrComponent;

    Vec2        m_vPos;
    Vec2        m_vScale;
    LAYER_TYPE  m_eLayer;

    bool        m_bDead;
    bool        m_bFocus;

protected:
    float       m_fDeltaTime;

public:
    void SelectDeltaTime();

public:
    void SetLayer(LAYER_TYPE _layerType) { m_eLayer = _layerType; }
    void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    void InFocus() { m_bFocus = true; }
    void OutFocus() { m_bFocus = false; }

    LAYER_TYPE GetLayer() { return m_eLayer; }
    Vec2 GetPos() const { return m_vPos; }
    Vec2 GetScale() const { return m_vScale; }
    float GetDT() { return m_fDeltaTime; }

    bool IsDead() const { return m_bDead; }

    AI* GetAI() const { return (AI*)m_varrComponent[(UINT)COMPONENT_TYPE::AI][0]; }
    CCollider* GetCollider() const { return (CCollider*)m_varrComponent[(UINT)COMPONENT_TYPE::COLLIDER][0]; }
    CAnimator* GetAnimator() const { return (CAnimator*)m_varrComponent[(UINT)COMPONENT_TYPE::ANIMATOR][0]; }
    CRigidBody* GetRigidBody() const { return (CRigidBody*)m_varrComponent[(UINT)COMPONENT_TYPE::RIGIDBODY][0]; }
    CPosSelector* GetPosSelector() const { return (CPosSelector*)m_varrComponent[(UINT)COMPONENT_TYPE::POS_SELECTOR][0]; }

    vector<CComponent*>* GetSelectComponentBundle(COMPONENT_TYPE _compotype) const { return  (vector<CComponent*>*)&m_varrComponent[(UINT)_compotype]; }
   

    void AddComponent(CComponent* _pComponent);
      

public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) {};
    virtual void CollisionOverlap(CCollider* _pOtherCollider) {};
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider) {};

private:
    void SetDead() { m_bDead = true; }

public:
    virtual CObject* Clone() = 0;

public:
    CObject();    
    CObject(const CObject& _obj);
    virtual ~CObject();

    friend class CEventMgr;
};