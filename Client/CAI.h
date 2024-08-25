#pragma once
#include "CComponent.h"

class CState;

class AI :
    public CComponent
{
private:
    map<wstring, CState*>   m_mapState;
    CState*                 m_pCurState;


public:
    void AddState(const wstring& _strKey, CState* _pState);
    CState* FindState(const wstring& _strKey);
    void ChangeState(const wstring& _strKey);

public:
    virtual void tick() override;



public:
    CLONE(AI);
public:
    AI();
    AI(const AI& _origin);
    ~AI();
};

