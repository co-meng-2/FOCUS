#pragma once
#include "CScene.h"

class CScene_Tool :
    public CScene
{
private:
    TOOL_MODE   m_eMode;
    UINT        m_iObjectCount;

    UINT        m_iColType;
    Vec2        m_vColScale;
    

private:
    void TileMode();
    void TileSelectMode();
    void ObjectMode();

    void CreateUI();

public:
    void NextColType() 
    { 
        if (m_iColType == (UINT)COLLIDER_TYPE::END - 1)
        {
            m_iColType = (int)COLLIDER_TYPE::BLOCK; // 0
        }
        else
        {
            ++m_iColType;
        }
    }
    void PrevColType() 
    {
        if (m_iColType == (UINT)COLLIDER_TYPE::BLOCK)
        {
            m_iColType = (int)COLLIDER_TYPE::END - 1;
        }
        else
        {
            --m_iColType;
        }
    }
    void AddScaleX()
    {
        m_vColScale.x += 32.f;
    }
    void AddScaleY()
    {
        m_vColScale.y += 32.f;
    }
    void SubScaleX()
    {
        if (m_vColScale.x <= 32.f)
            m_vColScale.x = 32.f;
        else
            m_vColScale.x -= 32.f;
    }
    void SubScaleY()
    {
        if (m_vColScale.y <= 32.f)
            m_vColScale.y = 32.f;
        else
            m_vColScale.y -= 32.f;
    }

public:
    UINT GetColType() { return m_iColType; }
    Vec2 GetColScale() { return m_vColScale; }

public:    
    virtual void tick() override;
    virtual void enter() override;
    virtual void exit() override;

public:
    void TileSave();
    void TileLoad();

    void ObjectSave();
    void ObjectLoad();

    

public:
    CScene_Tool(SCENE_TYPE _scenetype);
    ~CScene_Tool();
};

