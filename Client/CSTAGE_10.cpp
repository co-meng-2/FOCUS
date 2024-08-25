#include "pch.h"
#include "CSTAGE_10.h"

#include "CCollisionMgr.h"

#include "CMissileTurret.h"
#include "CBlockChecker.h"
#include "CEnforcer.h"

CSTAGE_10::CSTAGE_10(SCENE_TYPE _scenetype)
	: CScene(STAGE_10) // 변경
{
}

CSTAGE_10::~CSTAGE_10()
{
}

void CSTAGE_10::enter()
{
	SetNextScene(SCENE_TYPE::ENDING); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetMaxFocusRadius(400.f);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	// Turret
	CMissileTurret* pTurret = new CMissileTurret;
	pTurret->SetTurret(MISSILE_OPTION::GUIDED, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS, MISSILE_OPTION::ACCEL, 500.f, 200.f, 180.f);
	pTurret->SetMaxSpeed(1000.f);
	pTurret->SetPos(Vec2(656.f, 160.f));
	pTurret->SetCoolTime(1.f);
	pTurret->SetCoolCoolTime(0.5f);
	pTurret->SetPlayer(pPlayer);
	AddObject(pTurret, LAYER_TYPE::SPAWNER);

	// BlockChekcer
	CBlockChecker* pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject(pChecker, LAYER_TYPE::BLOCKCHECKER);

	pTurret = new CMissileTurret;
	pTurret->SetTurret(MISSILE_OPTION::GUIDED, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS, MISSILE_OPTION::ACCEL, 500.f, 200.f, 180.f);
	pTurret->SetMaxSpeed(1000.f);
	pTurret->SetPos(Vec2(656.f, 288.f));
	pTurret->SetCoolTime(1.f);
	pTurret->SetCoolCoolTime(0.5f);
	pTurret->SetPlayer(pPlayer);
	AddObject(pTurret, LAYER_TYPE::SPAWNER);

	pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject(pChecker, LAYER_TYPE::BLOCKCHECKER);


	pTurret = new CMissileTurret;
	pTurret->SetTurret(MISSILE_OPTION::GUIDED, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS, MISSILE_OPTION::ACCEL, 500.f, 200.f, 180.f);
	pTurret->SetMaxSpeed(1000.f);
	pTurret->SetPos(Vec2(368.f, 160.f));
	pTurret->SetCoolTime(1.f);
	pTurret->SetCoolCoolTime(0.5f);
	pTurret->SetPlayer(pPlayer);
	AddObject(pTurret, LAYER_TYPE::SPAWNER);

	pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject(pChecker, LAYER_TYPE::BLOCKCHECKER);

	pTurret = new CMissileTurret;
	pTurret->SetTurret(MISSILE_OPTION::GUIDED, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS, MISSILE_OPTION::ACCEL, 500.f, 200.f, 180.f);
	pTurret->SetMaxSpeed(1000.f);
	pTurret->SetPos(Vec2(368.f, 288.f));
	pTurret->SetCoolTime(1.f);
	pTurret->SetCoolCoolTime(0.5f);
	pTurret->SetPlayer(pPlayer);
	AddObject(pTurret, LAYER_TYPE::SPAWNER);

	pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject(pChecker, LAYER_TYPE::BLOCKCHECKER);
	

	// Enforcer
	CEnforcer* pEnforcer = new CEnforcer;
	pEnforcer->SetPos(Vec2(512.f, 618.f));
	AddObject(pEnforcer, LAYER_TYPE::CRYSTAL);

	pEnforcer = new CEnforcer;
	pEnforcer->SetPos(Vec2(192.f, 192.f));
	AddObject(pEnforcer, LAYER_TYPE::CRYSTAL);

	pEnforcer = new CEnforcer;
	pEnforcer->SetPos(Vec2(836.f, 192.f));
	AddObject(pEnforcer, LAYER_TYPE::CRYSTAL);

	LoadTile(L"content\\tile\\STAGE_10\\STAGE_10.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_10\\STAGE_10.Map"); // 변경

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROJECTILES);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::EXPLOSION);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MINE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::FRAGMENT);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_OPTION, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::BLOCKCHECKER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::EXPLOSION, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MINE, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::FRAGMENT, LAYER_TYPE::COLLIDEROBJ);


	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::LASERSTOPPER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::MINE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::PROJECTILES);
}

void CSTAGE_10::tick()
{
	CScene::tick();
}

void CSTAGE_10::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}