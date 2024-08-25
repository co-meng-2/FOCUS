#pragma once
#include "CObject.h"

class CImage;
class CMineSpawner;

class CMine :
    public CObject
{
private:
    CImage* m_pImage;

    Vec2  m_vPrevPos;
    Vec2  m_vMovedPos;

    CMineSpawner* m_pMineSpawner;



public:
    Vec2 GetMovedPos() { return m_vMovedPos; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider);
    virtual void CollisionOverlap(CCollider* _pOtherCollider);
    virtual void CollisionEndOverlap(CCollider* _pOtherCollider);
public:
    CLONE(CMine);

public:
    CMine();
    ~CMine();

    friend class CMineSpawner;
};

