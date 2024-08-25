#include "pch.h"
#include "CFragments.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CDebugMgr.h"

#include "CPlayer.h"
#include "CImage.h"
#include "CColliderObject.h"
#include "CTile.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"


CFragments::CFragments()
	: m_fAccTime(0.f)
	, m_fDuration(4.f)
	, m_vPrevPos(Vec2(0.f, 0.f))
	, m_pImage(nullptr)
	, m_vRandomForce(Vec2(rand() * 1000000 - 500000, -20000))
{
	m_pImage = CResMgr::GetInst()->LoadImg(L"Thorn", L"image\\Fragments\\Fragment_800_400_8_8.bmp");
	
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(10.f, 20.f));

	AddComponent(new CRigidBody);
	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(750.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 1500.f));
	GetRigidBody()->AddForce(m_vRandomForce);

	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"FragmentEffect", m_pImage, Vec2(0.f, 0.f), Vec2(100.f, 50.f), Vec2(0.f, -5.f), 100.f, 8, 0.05f);
	GetAnimator()->Play(L"FragmentEffect", true);
}

CFragments::~CFragments()
{
}

void CFragments::tick()
{
	SelectDeltaTime();

	m_fAccTime += GetDT();

	if (m_fAccTime >= m_fDuration && !IsDead()) 
		DeleteObject(this);


	CObject::tick();
	m_vMovedPos = GetPos() - m_vPrevPos;
	m_vPrevPos = GetPos();
}

void CFragments::render(HDC _dc)
{
	//m_pImage = CResMgr::GetInst()->LoadImg(L"Thorn", L"image\\Thorn_35_35.bmp");
	//Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	//TransparentBlt(_dc
	//	, (int)vRenderPos.x, (int)vRenderPos.y
	//	, TILE_SIZE, TILE_SIZE
	//	, m_pImage->GetDC()
	//	, 0, 0
	//	, TILE_SIZE, TILE_SIZE
	//	, RGB(255, 0, 255));

	CObject::render(_dc);
}

void CFragments::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	Vec2 vColPos = GetCollider()->GetFinalPos();
	Vec2 vColScale = GetCollider()->GetScale();
	Vec2 vBlockColPos = _pOtherCollider->GetFinalPos();
	Vec2 vBlockColScale = _pOtherCollider->GetScale();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());  
	if (nullptr == pPlayer || !IsValid(pPlayer))
	{

	}
	else
	{
		// DeleteObject(pPlayer);
		if (!IsInvincibleD)
			pPlayer->SetDead();
	}

	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr != pColObj && IsValid(pColObj))
	{

		if (vBlockColPos.y - vBlockColScale.y / 2.f + GetMovedPos().y >= vColPos.y + vColScale.y / 2.f || vBlockColPos.y + vBlockColScale.y / 2.f - GetMovedPos().y <= vColPos.y - vColScale.y / 2.f &&
			!(vBlockColPos.y - vBlockColScale.y / 2.f + 5.f > vColPos.y + vColScale.y / 2.f))
		{
			GetRigidBody()->SetCollisionDirection(COLLISION_DIRECTION::HORIZONTAL_VERTICAL);
			if (pColObj->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y > 0 &&
				GetRigidBody()->GetVelocity().y < 150.f) // DT 곱해지기 때문에 매우 작은 수치
			{
				GetRigidBody()->SetGround(true);
			}
		}
		else if (vBlockColPos.y - vBlockColScale.y / 2.f + GetMovedPos().y >= vColPos.y + vColScale.y / 2.f || vBlockColPos.y + vBlockColScale.y / 2.f - GetMovedPos().y <= vColPos.y - vColScale.y / 2.f)
		{
			GetRigidBody()->SetCollisionDirection(COLLISION_DIRECTION::VERTICAL);
			if (pColObj->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y > 0 &&
				GetRigidBody()->GetVelocity().y < 150.f) // DT 곱해지기 때문에 매우 작은 수치
			{
				GetRigidBody()->SetGround(true);
			}
		}
		/*else
			GetRigidBody()->SetCollisionDirection(COLLISION_DIRECTION::HORIZONTAL);*/

		else if (!(vBlockColPos.y - vBlockColScale.y / 2.f + 5.f > vColPos.y + vColScale.y / 2.f))
		{
			GetRigidBody()->SetCollisionDirection(COLLISION_DIRECTION::HORIZONTAL);
		}
	}


}

void CFragments::CollisionOverlap(CCollider* _pOtherCollider)
{
	
}

void CFragments::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr == pColObj || !IsValid(pColObj))
		return;
	else
	{
		if(GetCollider()->GetBlockCollisionCount() == 1)
			GetRigidBody()->SetGround(false);
	}
}


