#pragma once
#include "CScene.h"

class CObject;

class CScene_Start :
    public CScene
{
private:

public:
    virtual void tick() override;

    virtual void enter() override;
    virtual void exit() override; 
    
public:
    CScene_Start(SCENE_TYPE _scenetype);
    ~CScene_Start();
};

