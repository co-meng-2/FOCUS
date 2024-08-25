#include "pch.h"
#include "CSTAGE_09.h"

#include "CCollisionMgr.h"

#include "CLaserBody.h"
#include "CLaserStopper.h"
#include "CMineSpawner.h"
#include "CMissileTurret.h"
#include "CBlockChecker.h"
#include "CEnforcer.h"

CSTAGE_09::CSTAGE_09(SCENE_TYPE _scenetype)
	: CScene(STAGE_09) // 변경
{
}

CSTAGE_09::~CSTAGE_09()
{
}

void CSTAGE_09::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_10); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetMaxFocusRadius(400.f);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	// Laser
	CLaserStopper* pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(90.f, 307.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(867.f, 307.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	// -------------------------------------------------------------

	CLaserBody* pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(242.f, 307.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(394.f, 307.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(546.f, 307.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(698.f, 307.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(850.f, 307.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	// -------------------------------------------------------------

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(528.f, 64.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(528.f, 600.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserBody = new CLaserBody(LASER_TYPE::VERTICAL);
	pLaserBody->SetPos(Vec2(528.f, 307.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	// MissileTurret
	CMissileTurret* pTurret = new CMissileTurret;
	pTurret->SetTurret(MISSILE_OPTION::LINE, MISSILE_OPTION::EXPLOSIVE, MISSILE_OPTION::FRAGMENTS_X, MISSILE_OPTION::ACCEL, 500.f, 200.f);
	pTurret->SetMaxSpeed(700.f);
	pTurret->SetPos(Vec2(496.f, 111.f));
	pTurret->SetPlayer(pPlayer);
	AddObject(pTurret, LAYER_TYPE::SPAWNER);

	// BlockChekcer
	CBlockChecker* pChecker = new CBlockChecker(pPlayer, pTurret);
	AddObject(pChecker, LAYER_TYPE::BLOCKCHECKER);
	

	// Mine
	CMineSpawner* pMineSpawner = new CMineSpawner;
	pMineSpawner->SetPos(Vec2(957.f, 556.f));
	AddObject(pMineSpawner, LAYER_TYPE::SPAWNER);


	// Enforcer
	CEnforcer* pEnforcer = new CEnforcer;
	pEnforcer->SetPos(Vec2(512.f, 384.f));
	AddObject(pEnforcer, LAYER_TYPE::CRYSTAL);


	LoadTile(L"content\\tile\\STAGE_09\\STAGE_09.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_09\\STAGE_09.Map"); // 변경

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROJECTILES);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::EXPLOSION);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MINE);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_OPTION, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::BLOCKCHECKER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::EXPLOSION, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MINE, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::LASERSTOPPER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::MINE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::PROJECTILES);


}

void CSTAGE_09::tick()
{
	CScene::tick();
}

void CSTAGE_09::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}