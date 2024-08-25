#include "pch.h"
#include "CSTAGE_04.h"

#include "CCollisionMgr.h"

#include "CMineSpawner.h"
#include "CLaserBody.h"
#include "CLaserStopper.h"

CSTAGE_04::CSTAGE_04(SCENE_TYPE _scenetype)
	: CScene(STAGE_04) // 변경
{}

CSTAGE_04::~CSTAGE_04()
{}

void CSTAGE_04::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_05); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetHasFocus(false);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	// MineSpanwer
	CMineSpawner* pMineSpawner = new CMineSpawner;
	pMineSpawner->SetPos(Vec2(725.f, 450.f));
	AddObject((CObject*)pMineSpawner, LAYER_TYPE::SPAWNER);

	// Laser
	CLaserBody* pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(393.f,286.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	CLaserStopper* pLaserStopper = new CLaserStopper(); 
	pLaserStopper->SetPos(Vec2(142.f, 286.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(896.f, 286.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	LoadTile(L"content\\tile\\STAGE_04\\STAGE_04.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_04\\STAGE_04.Map"); // 변경

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERSTOPPER, LAYER_TYPE::LASERBODY);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::MINE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MINE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::COLLIDEROBJ, LAYER_TYPE::MINE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::COLLIDEROBJ, LAYER_TYPE::EXPLOSION);
}

void CSTAGE_04::tick()
{
	CScene::tick();
}

void CSTAGE_04::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}