#pragma once
#include "CScene.h"

class CImage;

class CEnding :
    public CScene
{
public:
    CImage* m_pEndingText;
    CImage* m_pBackground;

public:

    virtual void enter() override;
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void exit() override;


public:
    CEnding(SCENE_TYPE _scenetype);
    ~CEnding();
};

