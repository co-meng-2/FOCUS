#include "pch.h"
#include "CScene_Logo.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollisionMgr.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CDebugMgr.h"
#include "CCamera.h"

#include "CImage.h"


CScene_Logo::CScene_Logo(SCENE_TYPE _scenetype)
	: CScene(_scenetype)
	, m_fAccTime(0.f)
	, m_fCoolTime(2.f)
	, m_iRandHour(0)
	, m_iRandMinute(0)
{
	m_pClocMinutekAtlas = CResMgr::GetInst()->FindImg(L"ClockMinuteAtlas");
	m_pClockHourAtlas = CResMgr::GetInst()->FindImg(L"ClockHourAtlas");
	m_pLogoBackground = CResMgr::GetInst()->FindImg(L"LogoBackgroundImage");
	m_pLogoText = CResMgr::GetInst()->FindImg(L"LogoTextImage");
}

CScene_Logo::~CScene_Logo()
{
}

void CScene_Logo::enter()
{
	CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::SHAKE_HORIZONTAL, 0.5f, 5, 1000);
}

void CScene_Logo::exit()
{
	DeleteAllObject();
	SetButtonCountZero();
	CCollisionMgr::GetInst()->clear();
}

void CScene_Logo::tick()
{
	CScene::tick();
	if(IsDebugModeD)
	{
		if (IsTap(KEY_TYPE::ENTER))
			SceneChange(SCENE_TYPE::TOOL);
	}

	if (IsTap(KEY_TYPE::F))
		SceneChange(SCENE_TYPE::STAGE_01);
}

void CScene_Logo::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));

	TransparentBlt(_dc
		, vPos.x
		, vPos.y
		, int(m_pLogoBackground->GetWidth())
		, int(m_pLogoBackground->GetHeight())
		, m_pLogoBackground->GetDC()
		, 0
		, 0
		, m_pLogoBackground->GetWidth()
		, m_pLogoBackground->GetHeight()
		, RGB(255, 0, 255));

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;

	vPos = CCamera::GetInst()->GetRenderPos(CEngine::GetInst()->GetResolution());


	m_fAccTime += DT;

	if (m_fAccTime >= m_fCoolTime)
	{
		m_iRandHour = (int)(rand() % 12);
		m_iRandMinute = (int)(rand() % 12);

		m_fAccTime = 0.f;
		tFunc.SourceConstantAlpha = 0.f;
	}
	else
	{
		if((float)m_fAccTime / (float)m_fCoolTime < 0.5f)
			tFunc.SourceConstantAlpha = 100.f * (float)m_fAccTime / (float)m_fCoolTime;
		else
			tFunc.SourceConstantAlpha = 100.f - 100.f * (float)m_fAccTime / (float)m_fCoolTime;
	}
		
	AlphaBlend(_dc
		, vPos.x / 2.f - m_pClockHourAtlas->GetWidth() / 12 / 2
		, vPos.y / 2.f - m_pClockHourAtlas->GetHeight() / 2
		, m_pClockHourAtlas->GetWidth() / 12
		, m_pClockHourAtlas->GetHeight()
		, m_pClockHourAtlas->GetDC()
		, m_pClockHourAtlas->GetWidth() / 12 * m_iRandHour
		, 0
		, m_pClockHourAtlas->GetWidth() / 12
		, m_pClockHourAtlas->GetHeight()
		, tFunc);

	AlphaBlend(_dc
		, vPos.x / 2.f - m_pClocMinutekAtlas->GetWidth() / 12 / 2
		, vPos.y / 2.f - m_pClocMinutekAtlas->GetHeight() / 2
		, m_pClocMinutekAtlas->GetWidth() / 12
		, m_pClocMinutekAtlas->GetHeight()
		, m_pClocMinutekAtlas->GetDC()
		, m_pClocMinutekAtlas->GetWidth() / 12 * m_iRandMinute
		, 0
		, m_pClocMinutekAtlas->GetWidth() / 12
		, m_pClocMinutekAtlas->GetHeight()
		, tFunc);

	vPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));

	BLENDFUNCTION tFunc2 = {};
	tFunc2.BlendOp = AC_SRC_OVER;
	tFunc2.BlendFlags = 0;
	tFunc2.AlphaFormat = AC_SRC_ALPHA;
	tFunc2.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, vPos.x
		, vPos.y
		, int(m_pLogoText->GetWidth())
		, int(m_pLogoText->GetHeight())
		, m_pLogoText->GetDC()
		, 0
		, 0
		, m_pLogoText->GetWidth()
		, m_pLogoText->GetHeight()
		, tFunc2);
}
