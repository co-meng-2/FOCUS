#include "pch.h"
#include "CEnding.h"

#include "CResMgr.h"
#include "CImage.h"

#include "CCamera.h"

CEnding::CEnding(SCENE_TYPE _scenetype)
	: CScene(SCENE_TYPE::ENDING)
{
	m_pEndingText = CResMgr::GetInst()->FindImg(L"EndingTextImage");
	m_pBackground = CResMgr::GetInst()->FindImg(L"BackBuffer");
}

CEnding::~CEnding()
{
}

void CEnding::enter()
{
}

void CEnding::tick()
{
	CScene::tick();
}

void CEnding::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));

	TransparentBlt(_dc
		, vPos.x
		, vPos.y
		, m_pEndingText->GetWidth()
		, m_pEndingText->GetHeight()
		, m_pEndingText->GetDC()
		, 0
		, 0
		, m_pEndingText->GetWidth()
		, m_pEndingText->GetHeight()
		, RGB(255,0,255));

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, vPos.x
		, vPos.y
		, m_pEndingText->GetWidth()
		, m_pEndingText->GetHeight()
		, m_pEndingText->GetDC()
		, 0
		, 0
		, m_pEndingText->GetWidth()
		, m_pEndingText->GetHeight()
		, tFunc);
}



void CEnding::exit()
{
}

