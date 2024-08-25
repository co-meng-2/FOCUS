#pragma once
#include "CScene.h"
class CSTAGE_06 :
    public CScene
{
public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CSTAGE_06(SCENE_TYPE _scenetype);
    ~CSTAGE_06();
};

