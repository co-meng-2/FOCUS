#pragma once
#include "CScene.h"
class CStage_02 :
    public CScene
{
private:

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:
    CStage_02(SCENE_TYPE _scenetype);
    ~CStage_02();
};

