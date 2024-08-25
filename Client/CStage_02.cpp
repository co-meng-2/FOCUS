#include "pch.h"
#include "CStage_02.h"

#include "CCollisionMgr.h"

CStage_02::CStage_02(SCENE_TYPE _scenetype)
	: CScene(SCENE_TYPE::STAGE_02)
{
	SetNextScene(SCENE_TYPE::STAGE_03);

}

CStage_02::~CStage_02()
{
	
}

void CStage_02::enter()
{
	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetHasFocus(false);
	AddObject((CObject*)pPlayer, LAYER_TYPE::PLAYER);

	LoadTile(L"content\\tile\\STAGE_02\\STAGE_02.Tile");
	LoadObject(L"content\\tile\\STAGE_02\\STAGE_02.Map");

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDEROBJ);
}

void CStage_02::tick()
{
	CScene::tick();
}



void CStage_02::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
	SetButtonCountZero();
}


