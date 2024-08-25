#pragma once
#include "CObject.h"

class CImage;
class CPlayer;

class CMonster :
    public CObject
{
private:
    tMonsterInfo    m_info;
    CImage*         m_pImage;
    CPlayer*        m_pPlayer;


public:
    const tMonsterInfo& GetInfo() { return m_info; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;
    CMonster* Clone() { return new CMonster(*this); }

public:
    CMonster();
    CMonster(const CMonster& _mon);
    ~CMonster();
};

