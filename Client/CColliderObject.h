#pragma once
#include "CObject.h"

class CImage;

class CColliderObject :
    public CObject
{
private:
    UINT m_iColliderType;
    Vec2 m_vColScale;
    float m_fAccTime;

    bool m_bButtonPressed;

public:
    UINT GetColType() { return m_iColliderType; }
    void SetColType(UINT _collidertype) { m_iColliderType = _collidertype; }

public:
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);

public:
    CLONE(CColliderObject);

public:
    CColliderObject();
    CColliderObject(UINT _icollidertype, Vec2 _vcolscale);
    ~CColliderObject();
};

