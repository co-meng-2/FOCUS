#pragma once
#include "CScene.h"

class CImage;

class CScene_Logo :
    public CScene
{
private:
    CImage* m_pClocMinutekAtlas;
    CImage* m_pClockHourAtlas;
    CImage* m_pLogoBackground;
    CImage* m_pLogoText;

    float m_fAccTime;
    float m_fCoolTime;

    int m_iRandHour;
    int m_iRandMinute;

public:    
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CScene_Logo(SCENE_TYPE _scenetype);
    ~CScene_Logo();
};

