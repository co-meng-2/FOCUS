#include "pch.h"
#include "CScene_Start.h"

#include "CCollisionMgr.h"

#include "CMissileTurret.h"
#include "CPlayer.h"
#include "CTile.h"
#include "CTileChecker.h"
#include "CBlockChecker.h"
#include "CColliderObject.h"
#include "CCrystal.h"
#include "CEnforcer.h"
#include "CLaserBody.h"
#include "CLaserStopper.h"
#include "CMineSpawner.h"

#include "CCollider.h"

CScene_Start::CScene_Start(SCENE_TYPE _scenetype)
    : CScene(_scenetype)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::tick()
{
    CScene::tick();
}

void CScene_Start::enter()
{

}

void CScene_Start::exit()
{
    DeleteAllObject();
    CCollisionMgr::GetInst()->clear();
}