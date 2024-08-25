#include "pch.h"
#include "CSTAGE_06.h"

#include "CCollisionMgr.h"

#include "CMissileTurret.h"
#include "CBlockChecker.h"

CSTAGE_06::CSTAGE_06(SCENE_TYPE _scenetype)
	: CScene(STAGE_06) // 변경
{
}

CSTAGE_06::~CSTAGE_06()
{
}

void CSTAGE_06::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_07); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	// MissileTurret
	CMissileTurret* pTurret = new CMissileTurret;
	pTurret->SetPos(Vec2(128.f, 364.f));
	pTurret->SetTurret(MISSILE_OPTION::GUIDED, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS, MISSILE_OPTION::ACCEL, 200.f, 200.f, 120.f);	
	AddObject((CObject*)pTurret, LAYER_TYPE::SPAWNER);

	// BlockChecker
	CBlockChecker* pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject((CObject*)pChecker, LAYER_TYPE::BLOCKCHECKER);
	pTurret->SetPlayer(dynamic_cast<CPlayer*>(pPlayer));

	pTurret = new CMissileTurret;
	pTurret->SetPos(Vec2(896.f, 364.f));
	pTurret->SetTurret(MISSILE_OPTION::GUIDED, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS_X, MISSILE_OPTION::ACCEL, 200.f, 200.f, 120.f);
	AddObject((CObject*)pTurret, LAYER_TYPE::SPAWNER);

	pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject((CObject*)pChecker, LAYER_TYPE::BLOCKCHECKER);
	pTurret->SetPlayer(dynamic_cast<CPlayer*>(pPlayer));




	LoadTile(L"content\\tile\\STAGE_06\\STAGE_06.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_06\\STAGE_06.Map"); // 변경




	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROJECTILES);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::EXPLOSION);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::FRAGMENT);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_OPTION, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::BLOCKCHECKER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::EXPLOSION, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::FRAGMENT, LAYER_TYPE::COLLIDEROBJ);
	
}

void CSTAGE_06::tick()
{
	CScene::tick();
}

void CSTAGE_06::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}