#include "pch.h"
#include "CMine.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CSound.h"

#include "CSceneMgr.h"

#include "CScene.h"


#include "CPlayer.h"
#include "CColliderObject.h"
#include "CExplosion.h"
#include "CMineSpawner.h"

#include "CCollider.h"
#include "CRigidBody.h"

CMine::CMine()
	: m_vPrevPos(Vec2(0.f, 0.f))
{	
	AddComponent(new CCollider);
	GetCollider()->SetScale(MINE_SIZE);

	AddComponent(new CRigidBody);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 1500.f));

	m_pImage = CResMgr::GetInst()->FindImg(L"MineImage");
}

CMine::~CMine()
{
	if (!gChangeSceneFrame)
	{
		CObject* pExplosion = new CExplosion(EXPLOSION_TYPE::FIRST);
		pExplosion->SetPos(GetPos());
		AddObject_D(pExplosion, LAYER_TYPE::EXPLOSION);
	}

	if (m_pMineSpawner != nullptr && IsValid(m_pMineSpawner))
		m_pMineSpawner->SubMineCount();

	CSound* m_pExplosionSound = CResMgr::GetInst()->FindSound(L"Explosion");
	m_pExplosionSound->SetVolume(15.f);
	m_pExplosionSound->Play();
}

void CMine::tick()
{
	SelectDeltaTime();

	CObject::tick();
	m_vMovedPos = GetPos() - m_vPrevPos;
	m_vPrevPos = GetPos();
}

void CMine::render(HDC _dc)
{
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	AlphaBlend(_dc
		, int(vPos.x - ((float)m_pImage->GetWidth() / 2.f))
		, int(vPos.y - ((float)m_pImage->GetHeight() / 2.f))
		, int((float)m_pImage->GetWidth())
		, int((float)m_pImage->GetHeight())
		, m_pImage->GetDC()
		, 0
		, 0
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, tFunc);

	CObject::render(_dc);
}

void CMine::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	Vec2 vColPos = GetCollider()->GetFinalPos();
	Vec2 vColScale = GetCollider()->GetScale();
	Vec2 vBlockColPos = _pOtherCollider->GetFinalPos();
	Vec2 vBlockColScale = _pOtherCollider->GetScale();


	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr != pColObj && IsValid(pColObj))
	{
		if (vBlockColPos.y - vBlockColScale.y / 2.f + GetMovedPos().y >= vColPos.y + vColScale.y / 2.f)
		{
			SetPos(Vec2(GetPos().x, vBlockColPos.y - vBlockColScale.y / 2.f - vColScale.y / 2.f - 1.f));
			GetRigidBody()->SetGround(true);
		}
		else if (fabs(vBlockColPos.y + vBlockColScale.y / 2.f - 48.f - vColPos.y) < 10.f)
		{
			if (vColPos.x - vColScale.x / 2.f > vBlockColPos.x || vColPos.x + vColScale.x / 2.f < vBlockColPos.x)
			{
				CMine* pThis = this;
				if (pThis != nullptr && IsValid(pThis))
				{
					DeleteObject(pThis);
				}
			}
		}

		return;
	}


	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr != pPlayer && IsValid(pPlayer))
	{
		Vec2 vColPos = GetCollider()->GetFinalPos();
		Vec2 vColScale = GetCollider()->GetScale();
		Vec2 vPlayerColPos = _pOtherCollider->GetFinalPos();
		Vec2 vPlayerColScale = _pOtherCollider->GetScale();
		float vPlayerMovedPosX = fabs(pPlayer->GetMovedPos().x);
		float vPlayerMovedPosY = fabs(pPlayer->GetMovedPos().y);
		float fSpeed = pPlayer->GetSpeed();

		// 기본 충돌
		// down
		if (vColPos.y - vColScale.y / 2.f + vPlayerMovedPosY >= vPlayerColPos.y + vPlayerColScale.y / 2.f)
		{
			/*vPlayerColPos.y = vColPos.y - vColScale.y / 2.f - pPlayer->GetCollider()->GetOffset().y * 2 ;
			pPlayer->SetPos(vPlayerColPos);*/
			pPlayer->SetPos(Vec2(pPlayer->GetPos().x, vColPos.y - vColScale.y / 2.f - pPlayer->GetCollider()->GetOffset().y - vPlayerColScale.y / 2.f + 2.f));
			pPlayer->GetRigidBody()->SetGround(true);
		}
		// up
		else if (vColPos.y + vColScale.y / 2.f - vPlayerMovedPosY <= vPlayerColPos.y - vPlayerColScale.y / 2.f)
		{
			pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		}
		return;
	}
}

void CMine::CollisionOverlap(CCollider* _pOtherCollider)
{

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr != pPlayer && IsValid(pPlayer))
	{
		Vec2 vColPos = GetCollider()->GetFinalPos();
		Vec2 vColScale = GetCollider()->GetScale();
		Vec2 vPlayerColPos = _pOtherCollider->GetFinalPos();
		Vec2 vPlayerColScale = _pOtherCollider->GetScale();

		if (!(vColPos.y - vColScale.y / 2.f + 5.f > vPlayerColPos.y + vPlayerColScale.y / 2.f))
		{
			// move right
			if (vColPos.x - vColScale.x / 2.f > vPlayerColPos.x)
			{
				SetPos(Vec2(vPlayerColPos.x + vPlayerColScale.x / 2.f + vColScale.x /2.f + 1.f, GetPos().y));
			}
			// move left
			else if (vColPos.x + vColScale.x / 2.f < vPlayerColPos.x)
			{
				SetPos(Vec2(vPlayerColPos.x - vPlayerColScale.x / 2.f - vColScale.x / 2.f - 1.f, GetPos().y));
			}
		}
		return;
	}

	Vec2 vColPos = GetCollider()->GetFinalPos();
	Vec2 vColScale = GetCollider()->GetScale();
	Vec2 vBlockColPos = _pOtherCollider->GetFinalPos();
	Vec2 vBlockColScale = _pOtherCollider->GetScale();
	

}

void CMine::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr != pPlayer && IsValid(pPlayer))
	{
		if (pPlayer->GetCollider()->GetBlockCollisionCount() == 0)
		{
			pPlayer->GetRigidBody()->SetGround(false);
		}
	}
}


