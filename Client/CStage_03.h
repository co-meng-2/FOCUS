#pragma once
#include "CScene.h"
class CStage_03 :
    public CScene
{
public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:
    CStage_03(SCENE_TYPE _scenetype);
    ~CStage_03();
};

