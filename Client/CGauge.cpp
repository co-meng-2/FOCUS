#include "pch.h"
#include "CGauge.h"

#include "CCamera.h"

#include "CObject.h"
#include "CMissileTurret.h"

CGauge::CGauge()
	: CComponent(COMPONENT_TYPE::GAUGE)
	, m_fCurTurretAccTime(0.f)
	, m_fTurretCoolTime(0.f)
	, m_vOffsetPos(0.f, -33.f)
	, m_vScale(30.f, 12.f)
	, m_vFinalPos(0.f, 0.f)
{
}

CGauge::~CGauge()
{
}



void CGauge::tick()
{
	m_fTurretCoolTime = dynamic_cast<CMissileTurret*>(GetOwner())->GetCoolTime();
	m_fCurTurretAccTime = dynamic_cast<CMissileTurret*>(GetOwner())->GetAccTime();

	Vec2 vPos = GetOwner()->GetPos();
	m_vFinalPos = CCamera::GetInst()->GetRenderPos( vPos + m_vOffsetPos );
}

void CGauge::render(HDC _dc)
{
	CMissileTurret* pTurret = dynamic_cast<CMissileTurret*>(GetOwner());

	if (pTurret->GetRenderGauge())
	{
		tSelectPen Pen = tSelectPen(_dc, PEN_COLOR::GREEN);
		tSelectBrush Brush = tSelectBrush(_dc, BRUSH_COLOR::HOLLOW);

		Rectangle(_dc,
			int(m_vFinalPos.x - m_vScale.x / 2.f),
			int(m_vFinalPos.y - m_vScale.y / 2.f),
			int(m_vFinalPos.x + m_vScale.x / 2.f),
			int(m_vFinalPos.y + m_vScale.y / 2.f)
		);


		tSelectBrush Brush2 = tSelectBrush(_dc, BRUSH_COLOR::GRAY);

		Rectangle(_dc,
			int(m_vFinalPos.x - m_vScale.x / 2.f),
			int(m_vFinalPos.y - m_vScale.y / 2.f),
			int(m_vFinalPos.x - m_vScale.x / 2.f + m_vScale.x * (m_fCurTurretAccTime / m_fTurretCoolTime)),
			int(m_vFinalPos.y + m_vScale.y / 2.f)
		);
	}
}


