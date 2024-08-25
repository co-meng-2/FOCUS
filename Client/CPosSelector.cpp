#include "pch.h"
#include "CPosSelector.h"

#include "CTimeMgr.h"
#include "CCamera.h"

#include "CObject.h"
#include "CPlayer.h"

CPosSelector::CPosSelector()
	: CComponent(COMPONENT_TYPE::POS_SELECTOR)
	, m_vScale(20.f, 20.f)
	, m_vPlayerSwitchPos()
	, m_fSpeedX(200.f)
	, m_fSpeedY(200.f)
	, m_fInRadiusSpeed(100.f)
	, m_fAccelX(100.f)
	, m_fAccelY(100.f)
{
}

CPosSelector::~CPosSelector()
{
}

void CPosSelector::AddOffsetX()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
	if ( m_vOffsetPos.Length() <= pPlayer->GetCurFocusRadius())
	{
		m_fSpeedX += m_fAccelX * DT;
		m_vOffsetPos.x += m_fSpeedX * DT;
	}
	else
		m_fSpeedX = 200.f;
}

void CPosSelector::SubOffsetX()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
	if ( m_vOffsetPos.Length() <= pPlayer->GetCurFocusRadius())
	{
		m_fSpeedX += m_fAccelX * DT;
		m_vOffsetPos.x -= m_fSpeedX * DT;
	}
	else
		m_fSpeedX = 200.f;
}

void CPosSelector::AddOffsetY()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
	if ( m_vOffsetPos.Length() <= pPlayer->GetCurFocusRadius())
	{
		m_fSpeedY += m_fAccelY * DT;
		m_vOffsetPos.y += m_fSpeedY* DT;
	}
	else
		m_fSpeedY = 200.f;
}

void CPosSelector::SubOffsetY()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
	if  (m_vOffsetPos.Length() <= pPlayer->GetCurFocusRadius())
	{
		m_fSpeedY += m_fAccelY * DT;
		m_vOffsetPos.y -= m_fSpeedY * DT;
	}
	else
		m_fSpeedY = 200.f;
}

// 범위 밖으로 못 나감
// + BLOCK 안으로 or 맵 밖으로 못 나가게
void CPosSelector::tick()
{
	Vec2 vPos = GetOwner()->GetPos();
	Vec2 vTempFinalPos = vPos + m_vOffsetPos;
	
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
	// 원 밖
	if (m_vOffsetPos.Length() >= pPlayer->GetCurFocusRadius())
	{
		Vec2 vOffset = m_vOffsetPos;
		vOffset.Normalize();

		// DT로 변경(완)
		m_vOffsetPos -= vOffset * m_fInRadiusSpeed * DT;
	}

	// 맵 밖 값 보정
	// 맵 밖
	if (vTempFinalPos.x <= 42.f)
	{
		m_vOffsetPos.x = 42.f - vPos.x;
	}
	if (vTempFinalPos.x >= 986.f)
	{
		m_vOffsetPos.x = 986.f - vPos.x;
	}
	if (vTempFinalPos.y <= 42.f)
	{
		m_vOffsetPos.y = 42.f - vPos.y;
	}
	if (vTempFinalPos.y >= 726.f)
	{
		m_vOffsetPos.y = 726.f - vPos.y;
	}

	m_vFinalPos = CCamera::GetInst()->GetRenderPos(vPos + m_vOffsetPos);
	m_vPlayerSwitchPos = m_vFinalPos;
}

void CPosSelector::render(HDC _dc)
{
	tSelectPen Pen = tSelectPen(_dc, PEN_COLOR::BLUE);
	tSelectBrush Brush = tSelectBrush(_dc, BRUSH_COLOR::HOLLOW);

	Ellipse(_dc,
		int(m_vFinalPos.x - m_vScale.x / 2.f),
		int(m_vFinalPos.y - m_vScale.y / 2.f),
		int(m_vFinalPos.x + m_vScale.x / 2.f),
		int(m_vFinalPos.y + m_vScale.y / 2.f)
	);
}


