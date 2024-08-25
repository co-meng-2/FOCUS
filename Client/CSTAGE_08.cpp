#include "pch.h"
#include "CSTAGE_08.h"

#include "CCollisionMgr.h"

#include "CCrystal.h"

CSTAGE_08::CSTAGE_08(SCENE_TYPE _scenetype)
	: CScene(STAGE_08) // 변경
{
}

CSTAGE_08::~CSTAGE_08()
{
}

void CSTAGE_08::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_09); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	// Crystal
	CCrystal* pCrystal = new CCrystal(CRYSTAL_TYPE::ENHANCER);
	pCrystal->SetPos(Vec2(97.f, 131.f));
	pCrystal->SetOriginPos(Vec2(97.f, 131.f));
	AddObject((CObject*)pCrystal, LAYER_TYPE::CRYSTAL);

	LoadTile(L"content\\tile\\STAGE_08\\STAGE_08.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_08\\STAGE_08.Map"); // 변경

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROJECTILES);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::EXPLOSION);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::CRYSTAL);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_OPTION, LAYER_TYPE::COLLIDEROBJ);

	
}

void CSTAGE_08::tick()
{
	CScene::tick();
}

void CSTAGE_08::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}