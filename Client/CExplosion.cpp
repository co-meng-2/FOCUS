#include "pch.h"
#include "CExplosion.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CDebugMgr.h"

#include "CPlayer.h"
#include "CImage.h"
#include "CColliderObject.h"

#include "CCollider.h"
#include "CAnimator.h"



CExplosion::CExplosion(EXPLOSION_TYPE _et)
	: m_fAccTime(0.f)
	, m_fDuration(0.5f)
	, m_eExplosionType(_et)
{
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	AddComponent(new CAnimator);

	if (m_eExplosionType == EXPLOSION_TYPE::FIRST)
	{
		CImage* pExplosionAtlas = CResMgr::GetInst()->FindImg(L"MineExplosionAtlas");
		pExplosionAtlas->SetTransParent(true);
		GetAnimator()->CreateAnimation(L"Explosion1", pExplosionAtlas, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(0.f, -23.f), 96.f, 12, m_fDuration / 12.f);
		GetAnimator()->Play(L"Explosion1", false);
	}
	else if (m_eExplosionType == EXPLOSION_TYPE::SECOND)
	{
		CImage* pExplosionAtlas = CResMgr::GetInst()->FindImg(L"MissileExplosionAtlas");
		pExplosionAtlas->SetTransParent(true);
		GetAnimator()->CreateAnimation(L"Explosion2", pExplosionAtlas, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), 128.f, 13, m_fDuration / 13.f);
		GetAnimator()->Play(L"Explosion2", false);
	}
	else
	{
		CImage* pExplosionAtlas = CResMgr::GetInst()->FindImg(L"BasicExplosionAtlas");
		GetAnimator()->CreateAnimation(L"Explosion3", pExplosionAtlas, Vec2(0.f, 0.f), Vec2(25.f, 25.f), Vec2(0.f, 0.f), 25.f, 6, m_fDuration / 6.f);
		GetAnimator()->Play(L"Explosion3", false);
	}
}

CExplosion::~CExplosion()
{
}


void CExplosion::tick()
{
	SelectDeltaTime();

	
	m_fAccTime += GetDT();

	if (m_fAccTime >= m_fDuration + 0.1f)
		DeleteObject(this);
	else if(m_fAccTime <= m_fDuration - 0.2f )
	{
		Vec2 vColScale = GetCollider()->GetScale();
		vColScale += Vec2(50.f * GetDT() / (m_fDuration - 0.2f), 50.f * GetDT() / (m_fDuration - 0.2f));
		GetCollider()->SetScale(vColScale);
	}

	CObject::tick();
}

void CExplosion::render(HDC _dc)
{
	CObject::render(_dc);
}

void CExplosion::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr != pPlayer && IsValid(pPlayer))
	{
		// DeleteObject(pPlayer);
		if (!IsInvincibleD)
			pPlayer->SetDead();
	}

	/*CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr != pColObj && IsValid(pColObj))
	{
		if (pColObj->GetColType() == (UINT)COLLIDER_TYPE::BUTTON_IN || (pColObj->GetColType() == (UINT)COLLIDER_TYPE::BUTTON_OUT))
		{
			pColObj->
		}
	}*/

	
}

void CExplosion::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CExplosion::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}


