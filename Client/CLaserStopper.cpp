#include "pch.h"
#include "CLaserStopper.h"

#include "CCollider.h"

CLaserStopper::CLaserStopper()
{
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(10.f, 10.f));
}

CLaserStopper::~CLaserStopper()
{
}

void CLaserStopper::tick()
{

	CObject::tick();
}

void CLaserStopper::render(HDC _dc)
{
	tSelectPen hBrownPen = tSelectPen(_dc, PEN_COLOR::BROWN);
	tSelectBrush hHollowBrush = tSelectBrush(_dc, BRUSH_COLOR::HOLLOW);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vColScale = GetCollider()->GetScale();


	Ellipse(_dc,
		vPos.x - vColScale.x / 2.f,
		vPos.y - vColScale.y / 2.f,
		vPos.x + vColScale.x / 2.f,
		vPos.y + vColScale.y / 2.f
	);

	CObject::render(_dc);
}

void CLaserStopper::CollisionBeginOverlap (CCollider* _pOtherCollider)
{
}

void CLaserStopper::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CLaserStopper::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}