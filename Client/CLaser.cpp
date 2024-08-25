#include "pch.h"
#include "CLaser.h"

#include "CCamera.h"
#include "CDebugMgr.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CMine.h"
#include "CMissile.h"


CLaser::CLaser()
{
	AddComponent(new CCollider);
}

CLaser::~CLaser()
{
}

void CLaser::tick()
{
	CObject::tick();
}

void CLaser::render(HDC _dc)
{
	tSelectPen RedPen = tSelectPen(_dc, PEN_COLOR::RED);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Vec2 vColPos = CCamera::GetInst()->GetRenderPos(GetCollider()->GetFinalPos());
	Vec2 vColScale = GetCollider()->GetScale();

	Rectangle(_dc,
		vColPos.x - vColScale.x / 2.f,
		vColPos.y - vColScale.y / 2.f,
		vColPos.x + vColScale.x / 2.f,
		vColPos.y + vColScale.y / 2.f);

	SelectObject(_dc, hPrevBrush);
	DeleteObject(hBrush);
	

	CObject::render(_dc);
}

void CLaser::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	
	if (pPlayer != nullptr && IsValid(pPlayer))
	{
		if (!IsInvincibleD)
		{
			pPlayer->SetDead();
		}
	}

	CMine* pMine = dynamic_cast<CMine*>(_pOtherCollider->GetOwner());
	
	if(pMine != nullptr && IsValid(pMine))
	{
		DeleteObject(pMine);
	}

	CMissile* pMissile = dynamic_cast<CMissile*>(_pOtherCollider->GetOwner());

	if (pMissile != nullptr && IsValid(pMissile))
	{
		DeleteObject(pMissile);
	}
}

void CLaser::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CLaser::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}


