#pragma once
#include "CUI.h"


class CPanelUI :
    public CUI
{
private:
    Vec2    m_vCapturePos;
    TOOL_MODE m_eMode;

public:
    void SetMode(TOOL_MODE _eMode) { m_eMode = _eMode; }


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void LBtnDown() override;
    virtual void LBtnClicked() override;

public:
    CLONE(CPanelUI);

    CPanelUI();
    ~CPanelUI();
};

