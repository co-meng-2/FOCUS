#include "pch.h"
#include "CColliderObject.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CResMgr.h"
#include "CSound.h"
#include "CImage.h"
#include "CDebugMgr.h"

#include "CScene.h"
#include "CPlayer.h"
#include "CFragments.h"
#include "CExplosion.h"
#include "CTile.h"
#include "CComponent.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CMissile.h"

CColliderObject::CColliderObject()
	: m_bButtonPressed(false)
{
}

CColliderObject::CColliderObject(UINT _icollidertype, Vec2 _vcolscale)
	: m_iColliderType(_icollidertype)
	, m_vColScale(_vcolscale)
{
	if (m_iColliderType == (UINT)COLLIDER_TYPE::THORN)
	{
		AddComponent(new CCollider);
		AddComponent(new CCollider);

		vector<CComponent*>* pvCol = GetSelectComponentBundle(COMPONENT_TYPE::COLLIDER);
		CCollider* pCol1 = dynamic_cast<CCollider*>(pvCol->at(0));
		pCol1->SetScale(Vec2(TILE_SIZE / 2, TILE_SIZE / 2));
		pCol1->SetOffset(Vec2(TILE_SIZE / 2, TILE_SIZE / 4));

		CCollider* pCol2 = dynamic_cast<CCollider*>(pvCol->at(1));
		pCol2->SetScale(Vec2(TILE_SIZE, TILE_SIZE / 2));
		pCol2->SetOffset(Vec2(TILE_SIZE / 2, TILE_SIZE / 4 * 3));
	}
	else
	{
		AddComponent(new CCollider);
		GetCollider()->SetScale(m_vColScale);
		GetCollider()->SetOffset(m_vColScale / 2.f);

		if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_IN) // In Out INOUT
		{

		}
		else if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_OUT) // In Out INOUT
		{
			/*AddComponent(new CCollider);
			vector<CComponent*>* pvCol = GetSelectComponentBundle(COMPONENT_TYPE::COLLIDER);
			CCollider* pCol2 = dynamic_cast<CCollider*>(pvCol->at(1));*/
			CCollider* pCol2 = GetCollider();
			pCol2->SetScale(Vec2(BUTTON_OUT_SIZE.x, BUTTON_OUT_SIZE.y));
			pCol2->SetOffset(Vec2(TILE_SIZE / 2, BUTTON_OUT_SIZE.y / 2));
		}
	}
}

CColliderObject::~CColliderObject()
{
}

void CColliderObject::Save(FILE* _pFile)
{
	Vec2 vPos = GetPos();
	fwrite(&m_iColliderType, sizeof(UINT), 1, _pFile);
	fwrite(&m_vColScale, sizeof(Vec2), 1, _pFile);
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);
}

void CColliderObject::Load(FILE* _pFile)
{
	Vec2 vPos(0.f, 0.f);

	fread(&m_iColliderType, sizeof(UINT), 1, _pFile);
	// if (m_iColliderType != (UINT)COLLIDER_TYPE::THORN)
	fread(&m_vColScale, sizeof(Vec2), 1, _pFile);
	fread(&vPos, sizeof(Vec2), 1, _pFile);

	if (m_iColliderType == (UINT)COLLIDER_TYPE::THORN)
	{
		AddComponent(new CCollider);
		AddComponent(new CCollider);

		vector<CComponent*>* pvCol = GetSelectComponentBundle(COMPONENT_TYPE::COLLIDER);
		CCollider* pCol1 = dynamic_cast<CCollider*>(pvCol->at(0));
		pCol1->SetScale(Vec2(TILE_SIZE / 2, TILE_SIZE / 2));
		pCol1->SetOffset(Vec2(TILE_SIZE / 2, TILE_SIZE / 4));

		CCollider* pCol2 = dynamic_cast<CCollider*>(pvCol->at(1));
		pCol2->SetScale(Vec2(TILE_SIZE, TILE_SIZE / 2));
		pCol2->SetOffset(Vec2(TILE_SIZE / 2, TILE_SIZE / 4 * 3));
	}
	else
	{
		AddComponent(new CCollider);
		GetCollider()->SetScale(m_vColScale);
		GetCollider()->SetOffset(m_vColScale / 2.f);

		if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_IN) // In Out INOUT
		{
		CSceneMgr::GetInst()->GetCurScene()->AddButtonCount();
		}
		else if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_OUT) // In Out INOUT
		{
			/*AddComponent(new CCollider);
			vector<CComponent*>* pvCol = GetSelectComponentBundle(COMPONENT_TYPE::COLLIDER);
			CCollider* pCol2 = dynamic_cast<CCollider*>(pvCol->at(1));*/
			CCollider* pCol2 = GetCollider();
			pCol2->SetScale(Vec2(BUTTON_OUT_SIZE.x, BUTTON_OUT_SIZE.y));
			pCol2->SetOffset(Vec2(TILE_SIZE / 2, BUTTON_OUT_SIZE.y / 2));
			CSceneMgr::GetInst()->GetCurScene()->AddButtonCount();
		}
	}

	SetPos(vPos);
}

void CColliderObject::tick()
{
	if (m_iColliderType == (UINT)COLLIDER_TYPE::EXIT_BLOCK && CSceneMgr::GetInst()->GetCurScene()->GetButtonCount() == 0 && !IsDead())
	{
		DeleteObject(this);

		UINT iCol = GetCollider()->GetScale().y / TILE_SIZE;
		UINT iRow = GetCollider()->GetScale().x / TILE_SIZE;

		for (UINT col = 0; col < iCol; col++)
		{
			for (UINT row = 0; row < iRow; row++)
			{
				CTile* pTile = new CTile;
				pTile->SetPos(Vec2(GetPos().x + TILE_SIZE * row, GetPos().y + TILE_SIZE * col));
				pTile->SetScale(Vec2(TILE_SIZE, TILE_SIZE));
				pTile->SetImgIdx(63);
				CSceneMgr::GetInst()->GetCurScene()->AddObject(pTile, LAYER_TYPE::TILE_ADDED);
			}
		}
	}

	CObject::tick();
}

void CColliderObject::render(HDC _dc)
{
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_IN || m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_OUT)
	{
		CImage* pBtI = nullptr;

		if (!m_bButtonPressed)
		{
			pBtI = CResMgr::GetInst()->FindImg(L"ButtonInImage");
		}
		else
		{
			pBtI = CResMgr::GetInst()->FindImg(L"ButtonInPressedImage");
		}

		AlphaBlend(_dc
			, int(vPos.x + TILE_SIZE / 2 - pBtI->GetWidth() / 2.f)
			, int(vPos.y + TILE_SIZE / 2 - pBtI->GetHeight() / 2.f)
			, int(pBtI->GetWidth())
			, int(pBtI->GetHeight())
			, pBtI->GetDC()
			, 0
			, 0
			, pBtI->GetWidth()
			, pBtI->GetHeight()
			, tFunc);

		if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_OUT)
		{ 
			CImage* pBtO = nullptr;

			if (!m_bButtonPressed)
			{
				pBtO = CResMgr::GetInst()->FindImg(L"ButtonOutImage");
			}
			else
			{
				pBtO = CResMgr::GetInst()->FindImg(L"ButtonOutPressedImage");
			}
			AlphaBlend(_dc
				, int(vPos.x + TILE_SIZE / 2 - pBtO->GetWidth() / 2.f)
				, int(vPos.y - pBtO->GetHeight() / 2.f)
				, int(pBtO->GetWidth())
				, int(pBtO->GetHeight())
				, pBtO->GetDC()
				, 0
				, 0
				, pBtO->GetWidth()
				, pBtO->GetHeight()
				, tFunc);
		}
	}



	CObject::render(_dc);
}

void CColliderObject::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
	{

	}
	else
	{
		if (m_iColliderType == (UINT)COLLIDER_TYPE::SPAWN)
		{

		}
		else if (m_iColliderType == (UINT)COLLIDER_TYPE::SCENE_CHANGE)
		{
			SceneChange(CSceneMgr::GetInst()->GetCurScene()->GetNextScene());
		}
		else if (m_iColliderType == (UINT)COLLIDER_TYPE::THORN)
		{
			if (!IsInvincibleD)
				pPlayer->SetDead();
		}
		else
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
				pPlayer->SetPos(Vec2(pPlayer->GetPos().x, vColPos.y - vColScale.y / 2.f - pPlayer->GetCollider()->GetOffset().y - vPlayerColScale.y / 2.f + 1.f));
				pPlayer->GetRigidBody()->SetGround(true);
			}
			// up
			else if (vColPos.y + vColScale.y / 2.f - vPlayerMovedPosY <= vPlayerColPos.y - vPlayerColScale.y / 2.f)
			{
				pPlayer->GetRigidBody()->SetVelocity(-pPlayer->GetRigidBody()->GetVelocity() * 0.3f);
				pPlayer->SetStartAddForce(false);
			}
		}
	} // end of Collision of Player

	CFragments* pFragment = dynamic_cast<CFragments*>(_pOtherCollider->GetOwner());
	CExplosion* pExplosion = dynamic_cast<CExplosion*>(_pOtherCollider->GetOwner());
	CMissile* pMissile = dynamic_cast<CMissile*>(_pOtherCollider->GetOwner());
	

	if (!m_bButtonPressed && (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_IN || m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_OUT))
	{
		if (IsLive(pMissile) || IsLive(pFragment) || IsLive(pExplosion))
		{
			m_bButtonPressed = true;
			CSceneMgr::GetInst()->GetCurScene()->SubButtonCount();
		}

		if (m_iColliderType == (UINT)COLLIDER_TYPE::BUTTON_OUT)
		{
			if (IsLive(pPlayer))
			{
				CSound* m_pButtonSound = CResMgr::GetInst()->FindSound(L"ButtonPress");
				m_pButtonSound->SetVolume(60.f);
				m_pButtonSound->Play();
				m_bButtonPressed = true;
				CSceneMgr::GetInst()->GetCurScene()->SubButtonCount();
			}
		}
	}

}

void CColliderObject::CollisionOverlap(CCollider* _pOtherCollider)
{
	if (m_iColliderType != (UINT)COLLIDER_TYPE::SCENE_CHANGE &&
		m_iColliderType != (UINT)COLLIDER_TYPE::SPAWN &&
		m_iColliderType != (UINT)COLLIDER_TYPE::THORN)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
		if (nullptr == pPlayer || !IsValid(pPlayer))
			return;

		Vec2 vColPos = GetCollider()->GetFinalPos();
		Vec2 vColScale = GetCollider()->GetScale();
		Vec2 vPlayerColPos = _pOtherCollider->GetFinalPos();
		Vec2 vPlayerColScale = _pOtherCollider->GetScale();
		float fSpeed = pPlayer->GetSpeed();

		if (!(vColPos.y - vColScale.y / 2.f + 5.f > vPlayerColPos.y + vPlayerColScale.y / 2.f))
		{
			if (vColPos.x - vColScale.x / 2.f > vPlayerColPos.x)
			{
				pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, pPlayer->GetRigidBody()->GetVelocity().y));
				pPlayer->SetPos(Vec2(vColPos.x - vColScale.x / 2.f - pPlayer->GetCollider()->GetOffset().x - vPlayerColScale.x / 2.f - 1.f, pPlayer->GetPos().y));
				/*Vec2 vPlayerV = pPlayer->GetRigidBody()->GetVelocity();
				pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f , vPlayerV.y));*/
			}	
			// <- right
			else if (vColPos.x + vColScale.x / 2.f < vPlayerColPos.x)
			{
				pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, pPlayer->GetRigidBody()->GetVelocity().y));
				pPlayer->SetPos(Vec2(vColPos.x + vColScale.x / 2.f - pPlayer->GetCollider()->GetOffset().x + vPlayerColScale.x / 2.f + 1.f, pPlayer->GetPos().y));
			}
		}
	}
}

void CColliderObject::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	if (m_iColliderType != (UINT)COLLIDER_TYPE::SCENE_CHANGE &&
		m_iColliderType != (UINT)COLLIDER_TYPE::SPAWN &&
		m_iColliderType != (UINT)COLLIDER_TYPE::THORN)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
		if (nullptr == pPlayer || !IsValid(pPlayer))
			return;

		if (pPlayer->GetCollider()->GetBlockCollisionCount() == 1)
		{
			pPlayer->GetRigidBody()->SetGround(false);
		}
	}
}


