#include "pch.h"
#include "CSTAGE_07.h"

#include "CCollisionMgr.h"

#include "CLaserBody.h"
#include "CLaserStopper.h"

CSTAGE_07::CSTAGE_07(SCENE_TYPE _scenetype)
	: CScene(STAGE_07) // 변경
{
}

CSTAGE_07::~CSTAGE_07()
{
}

void CSTAGE_07::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_08); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);


	// Laser
	CLaserBody* pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(286.f, 272.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	CLaserStopper* pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(192.f, 272.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(480.f, 272.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);
	//--------------------------------------------------
	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(286.f, 496.f));
	pLaserBody->SetMoveDir(MOVE_DIRECTION::R);
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);
	
	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(480.f, 496.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(192.f, 496.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	//--------------------------------------------------
	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(693.f, 272.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(832.f, 272.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(544.f, 272.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	//--------------------------------------------------
	pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(693.f, 496.f));
	pLaserBody->SetMoveDir(MOVE_DIRECTION::R);
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(544.f, 496.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(832.f, 496.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);




	LoadTile(L"content\\tile\\STAGE_07\\STAGE_07.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_07\\STAGE_07.Map"); // 변경




	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROJECTILES);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::EXPLOSION);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_OPTION, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::BLOCKCHECKER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PROJECTILES, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::EXPLOSION, LAYER_TYPE::COLLIDEROBJ);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::LASERSTOPPER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASER, LAYER_TYPE::MINE);

}

void CSTAGE_07::tick()
{
	CScene::tick();
}

void CSTAGE_07::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}