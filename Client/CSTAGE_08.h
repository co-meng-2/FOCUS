#pragma once
#include "CScene.h"
class CSTAGE_08 :
    public CScene
{
public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override;

public:
    CSTAGE_08(SCENE_TYPE _scenetype);
    ~CSTAGE_08();
};

