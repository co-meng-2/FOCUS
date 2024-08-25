#include "pch.h"
#include "CEnforcer.h"

#include "CSceneMgr.h"
#include "CResMgr.h"
#include "CImage.h"

#include "CCamera.h"

#include "CPlayer.h"
#include "CScene.h"


CEnforcer::CEnforcer()
	: m_fEnforceRadius(250.f)
	, m_pImage(nullptr)
{
	m_pImage = CResMgr::GetInst()->FindImg(L"EnforcerImage");
	m_pPlayer = GetpPlayer;
}

CEnforcer::~CEnforcer()
{
}


void CEnforcer::tick()
{
	if (GetPos().Distance(m_pPlayer->GetPos()) < m_fEnforceRadius)
	{
		m_pPlayer->SetCurFocusRadius(m_pPlayer->GetMaxFocusRadius());
	}

	CObject::tick();
}

void CEnforcer::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vPlayerPos = CCamera::GetInst()->GetRenderPos(m_pPlayer->GetPos());

	HPEN hPen = CreatePen(BS_SOLID, 5, RGB(255, 255, 255));
	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);

	if (GetPos().Distance(m_pPlayer->GetPos()) < m_fEnforceRadius)
	{
		MoveToEx(_dc, vPos.x, vPos.y, NULL);
		LineTo(_dc, vPlayerPos.x, vPlayerPos.y);
	}

	SelectObject(_dc, hPrevPen);
	DeleteObject(hPen);

	TransparentBlt(_dc
		, int(vPos.x - (m_pImage->GetWidth() / 2.f))
		, int(vPos.y - (m_pImage->GetHeight() / 2.f))
		, int(m_pImage->GetWidth())
		, int(m_pImage->GetHeight())
		, m_pImage->GetDC()
		, 0
		, 0
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, RGB(255, 0, 255));

	CObject::render(_dc);
}

