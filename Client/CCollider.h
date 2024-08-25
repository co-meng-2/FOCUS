#pragma once
#include "CComponent.h"

union COLLIDER_ID
{
    struct
    {
        UINT LEFT_ID;
        UINT RIGHT_ID;
    };
    LONGLONG ID;
};

enum class COLLIDER_SHAPE
{
	RECT,
    LINE,
};

class CCollider :
    public CComponent
{
public:
    Vec2        m_vLT;
    Vec2        m_vRT;
    Vec2        m_vRB;
    Vec2        m_vLB;

    Vec2        m_vStartDot;
    Vec2        m_vEndDot;

private:
    Vec2        m_vOffsetPos;   // Object 로 부터 상대적인 거리
    Vec2        m_vScale;
    Vec2        m_vFinalPos;    // 충돌체의 최종 위치



    bool        m_vFixed;
    int         m_iCollisionCount; // 충돌 횟수

    int         m_iBlockCollisionCount;
    COLLIDER_SHAPE m_eShape;

public:
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    void SetOffset(Vec2 _vOffset) { m_vOffsetPos = _vOffset; }
    void SetFinalPos(Vec2 _vFinalpos) { m_vFinalPos = _vFinalpos; }
    void SetFixed() { m_vFixed = true; }
    void SetCollisionCountZero() { m_iCollisionCount = 0; }
    void SubCollisionCount() { --m_iCollisionCount; }

    Vec2 GetFinalPos() const { return m_vFinalPos;}
    Vec2 GetScale() const { return m_vScale; }
    Vec2 GetOffset() const { return m_vOffsetPos; }
    int GetCollisionCount() const { return m_iCollisionCount; }
    int GetBlockCollisionCount() { return m_iBlockCollisionCount; }
    COLLIDER_SHAPE GetShape() { return m_eShape; }

public:    
    // 충돌이 처음 발생하는 시점
    void CollisionBeginOverlap(CCollider* _pOtherCollider);   

    // 충돌 중이다.
    void CollisionOverlap(CCollider* _pOtherCollider);

    // 충돌이 벗어나지는 시점
    void CollisionEndOverlap(CCollider* _pOtherCollider);
  
public:
    CLONE(CCollider);

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CCollider();
    CCollider(COLLIDER_SHAPE _eShape);
    CCollider(const CCollider& _collider);
    ~CCollider();
};

