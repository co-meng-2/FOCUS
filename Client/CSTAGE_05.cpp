#include "pch.h"
#include "CSTAGE_05.h"

#include "CCollisionMgr.h"

#include "CCrystal.h"
#include "CLaserBody.h"
#include "CLaserStopper.h"
#include "CEffect.h"


CSTAGE_05::CSTAGE_05(SCENE_TYPE _scenetype)
	: CScene(STAGE_05) // 변경
{
}

CSTAGE_05::~CSTAGE_05()
{
}

void CSTAGE_05::enter()
{
	SetNextScene(SCENE_TYPE::STAGE_06); // 변경

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetHasFocus(false);
	// pPlayer->SetMaxFocusRadius(200.f);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);


	// Crystal
	CCrystal* pCrystalStart = new CCrystal(CRYSTAL_TYPE::STARTER);
	pCrystalStart->SetPos(Vec2(110, 656));
	pCrystalStart->SetOriginPos(Vec2(110, 656));
	AddObject(pCrystalStart, LAYER_TYPE::CRYSTAL);

	// Laser
	CLaserBody* pLaserBody = new CLaserBody(LASER_TYPE::HORIZONTAL);
	pLaserBody->SetPos(Vec2(588.f, 392.f));
	AddObject(pLaserBody, LAYER_TYPE::LASERBODY);

	CLaserStopper* pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(300.f, 392.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	pLaserStopper = new CLaserStopper();
	pLaserStopper->SetPos(Vec2(964.f, 392.f));
	AddObject(pLaserStopper, LAYER_TYPE::LASERSTOPPER);

	LoadTile(L"content\\tile\\STAGE_05\\STAGE_05.Tile"); // 변경
	LoadObject(L"content\\tile\\STAGE_05\\STAGE_05.Map"); // 변경

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::LASER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::CRYSTAL);
	
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::COLLIDEROBJ);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::LASERBODY, LAYER_TYPE::LASERSTOPPER);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_OPTION, LAYER_TYPE::COLLIDEROBJ);
}

void CSTAGE_05::tick()
{
	CScene::tick();
}

void CSTAGE_05::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}

