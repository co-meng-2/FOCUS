#pragma once
#include "CEntity.h"


#include "CMonster.h"
#include "CAI.h"

class CState :
    public CEntity
{
private:
    AI*    m_pAI;

public:
    AI* GetAI() { return m_pAI; }
    CObject* GetOwner();

public:
    virtual void enter() = 0;
    virtual void tick() = 0;
    virtual void exit() = 0;
    
    virtual CState* Clone() = 0;

public:
    CState();
    ~CState();

    friend class AI;
};

