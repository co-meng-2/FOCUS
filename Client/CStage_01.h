#pragma once
#include "CScene.h"
class CStage_01 :
    public CScene
{
private:

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:
    CStage_01(SCENE_TYPE _scenetype);
    ~CStage_01();
};

