#pragma once
#include "CObject.h"

class CMine;

class CImage;
class CSound;

class CMineSpawner
	: public CObject
{
private:
    float   m_fCoolTime;
    float   m_fAccTime;

    UINT    m_iMaxMineCount;
    UINT    m_iMineCount;

    CImage* m_pAtlas;
    CSound* m_pSound;

public:
    float GetCoolTime() { return m_fCoolTime; }
    float GetAccTime() { return m_fAccTime; }

    UINT GetMineCount() { return m_iMineCount; }
    void SubMineCount() { --m_iMineCount; }

public:
    void SpawnMine();

public:
    virtual void tick();
    virtual void render(HDC _dc);


public:
    CLONE(CMineSpawner);

public:
    CMineSpawner();
    ~CMineSpawner();
};

