#pragma once
#include "CState.h"

class CPlayer;

class CTrace :
    public CState
{
private:
    CPlayer* m_pPlayer;

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;


    CLONE(CTrace);
public:
    CTrace();
    ~CTrace();
};

