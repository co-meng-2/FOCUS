#include "pch.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"

#include "CImage.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidBody.h"

CTile::CTile()
	: m_pTileAtlas(nullptr)
	, m_iImgIdx(0)
	, m_fAccTime(0.f)
{
	m_pTileAtlas = CResMgr::GetInst()->LoadImg(L"TileAtlas", L"image\\RECENT\\TileMap_1024_1024_32_32.bmp");
}

CTile::~CTile()
{
}

void CTile::AddImgIdx()
{
	++m_iImgIdx;

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	if (iMaxCol * iMaxRow <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}
}

void CTile::SubImgIdx()
{
	--m_iImgIdx;

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	if (0 > m_iImgIdx)
	{
		m_iImgIdx = iMaxCol * iMaxRow - 1;
	}
}

void CTile::tick()
{
	m_fAccTime += DT;
	
	// TILECHECKER - BLOCK 예외처리
	//if (m_fAccTime > 0.02f)
	//{
	//	if (m_iImgIdx == (int)TILE_TYPE::BLOCK && GetLayer() == LAYER_TYPE::BLOCK )
	//	{
	//		GetCollider()->SetCollisionCountZero();
	//	}
	//}
		

	CObject::tick();
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileAtlas || m_iImgIdx == -1)
		return;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	int iRow = m_iImgIdx / iMaxCol;
	int iCol = m_iImgIdx % iMaxCol;

	if (iMaxRow <= iRow)
	{
		return;
	}

	/*BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, (int)vRenderPos.x, (int)vRenderPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pTileAtlas->GetDC()
		, TILE_SIZE * iCol, TILE_SIZE * iRow
		, TILE_SIZE, TILE_SIZE
		, tFunc);*/

	TransparentBlt(_dc
		, (int)vRenderPos.x, (int)vRenderPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pTileAtlas->GetDC()
		, TILE_SIZE * iCol, TILE_SIZE * iRow
		, TILE_SIZE, TILE_SIZE
		, RGB(255, 0, 255));

	CObject::render(_dc);
}

void CTile::Save(FILE* _pFile)
{
	SaveImageRef(m_pTileAtlas, _pFile);

	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	LoadImageRef(&m_pTileAtlas, _pFile);

	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

// 타일 충돌에서 LAYER_TYPE::COLOBJ 충돌로 바꿈

//void CTile::CollisionBeginOverlap(CCollider* _pCollider)
//{
//	// 타일 벽 충돌
//	if (m_iImgIdx == (int)TILE_TYPE::WALL || m_iImgIdx == (int)TILE_TYPE::BLOCK)
//	{
//		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
//		if (nullptr == pPlayer || !IsValid(pPlayer))
//			return;
//
//		if (fabs(GetCollider()->GetFinalPos().x - pPlayer->GetCollider()->GetFinalPos().x) < fabs(GetCollider()->GetFinalPos().y - pPlayer->GetCollider()->GetFinalPos().y) - 5)
//		{
//			Vec2 vP = pPlayer->GetCollider()->GetFinalPos();
//			Vec2 vV = pPlayer->GetRigidBody()->GetVelocity();
//
//
//			if (GetCollider()->GetFinalPos().y - pPlayer->GetCollider()->GetFinalPos().y > 0)
//			{
//				vP.y = GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f - pPlayer->GetCollider()->GetScale().y / 2.f - pPlayer->GetCollider()->GetOffset().y + 1.f;
//				pPlayer->GetRigidBody()->SetGround(true);
//			}
//			else if (GetCollider()->GetFinalPos().y - pPlayer->GetCollider()->GetFinalPos().y < 0)
//			{
//				vP.y = GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2.f + pPlayer->GetCollider()->GetScale().y / 2.f + pPlayer->GetCollider()->GetOffset().y + 1.f;
//
//				vV.y = 0.f;
//			}
//
//			pPlayer->GetRigidBody()->SetVelocity(vV);
//			pPlayer->SetPos(vP);
//		}
//	}
//
//	if (m_iImgIdx == (int)TILE_TYPE::EXIT)
//	{
//		SceneChange(SCENE_TYPE::TOOL);
//	}
//}
//
//void CTile::CollisionOverlap(CCollider* _pCollider)
//{
//	// 타일 벽 충돌
//	if (m_iImgIdx == (int)TILE_TYPE::WALL || m_iImgIdx == (int)TILE_TYPE::BLOCK)
//	{
//		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
//		if (nullptr == pPlayer || !IsValid(pPlayer))
//			return;
//
//
//		if (fabs(GetCollider()->GetFinalPos().x - pPlayer->GetCollider()->GetFinalPos().x) >= fabs(GetCollider()->GetFinalPos().y - pPlayer->GetCollider()->GetFinalPos().y))
//		{
//			Vec2 vV = pPlayer->GetRigidBody()->GetVelocity();
//			vV.x = 0.f;
//			pPlayer->GetRigidBody()->SetVelocity(vV);
//
//			Vec2 vP = pPlayer->GetPos();
//			if (GetCollider()->GetFinalPos().x - pPlayer->GetCollider()->GetFinalPos().x > 0)
//				vP.x = GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2.f - pPlayer->GetCollider()->GetScale().x / 2.f - pPlayer->GetCollider()->GetOffset().x - 1.f;
//			else if (GetCollider()->GetFinalPos().x - pPlayer->GetCollider()->GetFinalPos().x < 0)
//				vP.x = GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2.f + pPlayer->GetCollider()->GetScale().x / 2.f + pPlayer->GetCollider()->GetOffset().x + 1.f;
//
//			pPlayer->SetPos(vP);
//		}
//	}
//}
//
//void CTile::CollisionEndOverlap(CCollider* _pCollider)
//{
//	// 타일 벽 충돌
//	if (m_iImgIdx == (int)TILE_TYPE::WALL || m_iImgIdx == (int)TILE_TYPE::BLOCK)
//	{
//		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
//		if (nullptr == pPlayer || !IsValid(pPlayer))
//			return;
//
//		if (pPlayer->GetCollider()->GetCollisionCount() == 1)
//		{
//			pPlayer->GetRigidBody()->SetGround(false);
//		}
//	}
//}