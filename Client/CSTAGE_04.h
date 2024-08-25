#pragma once
#include "CScene.h"
class CSTAGE_04 :
    public CScene
{
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:
    CSTAGE_04(SCENE_TYPE _scenetype);
    ~CSTAGE_04();
};

