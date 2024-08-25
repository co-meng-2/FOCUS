#include "pch.h"
#include "CStage_01.h"

#include "CCollisionMgr.h"

CStage_01::CStage_01(SCENE_TYPE _scenetype)
	: CScene(SCENE_TYPE::STAGE_01)
{
}

CStage_01::~CStage_01()
{
	
}

void CStage_01::enter()
{


	SetNextScene(SCENE_TYPE::STAGE_02);

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetHasFocus(false);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	LoadTile(L"content\\tile\\STAGE_01\\STAGE_01.Tile");
	LoadObject(L"content\\tile\\STAGE_01\\STAGE_01.Map");

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
}

void CStage_01::tick()
{
	CScene::tick();
}



void CStage_01::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}


