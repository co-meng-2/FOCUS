#include "pch.h"
#include "CStage_03.h"

#include "CCollisionMgr.h"

#include "CMissileTurret.h"
#include "CBlockChecker.h"

CStage_03::CStage_03(SCENE_TYPE _scenetype)
	: CScene(STAGE_03) // 변경
{
}

CStage_03::~CStage_03()
{
}

void CStage_03::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_04); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetHasFocus(false);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	// MissileTurret
	CMissileTurret* pTurret = new CMissileTurret;
	pTurret->SetPos(Vec2(512.f, 384.f));
	pTurret->SetTurret(MISSILE_OPTION::LINE, MISSILE_OPTION::EXPLOSIVE_X, MISSILE_OPTION::FRAGMENTS_X, MISSILE_OPTION::ACCELX, 200.f);
	pTurret->SetDetectRadius(100000.f);

	AddObject((CObject*)pTurret, LAYER_TYPE::SPAWNER);

	// BlockChecker
	CBlockChecker* pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject((CObject*)pChecker, LAYER_TYPE::BLOCKCHECKER);
	pTurret->SetPlayer(dynamic_cast<CPlayer*>(pPlayer));

	LoadTile(L"content\\tile\\STAGE_03\\STAGE_03.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_03\\STAGE_03.Map"); // 변경


	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::BLOCKCHECKER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROJECTILES);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::COLLIDEROBJ);
}

void CStage_03::tick()
{
	CScene::tick();
}

void CStage_03::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}
