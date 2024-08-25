#include "pch.h"
#include "CTrace.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CTimeMgr.h"

CTrace::CTrace()
{
}

CTrace::~CTrace()
{
}

void CTrace::enter()
{
	// Player 를 찾는다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);
}

void CTrace::tick()
{
	// Player 를 쫒아간다.
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	Vec2 vMonPos = pOwner->GetPos();
	Vec2 vPlayerPos = m_pPlayer->GetPos();

	Vec2 vDir = vPlayerPos - vMonPos;
	vDir.Normalize();

	vMonPos += vDir * pOwner->GetInfo().fSpeed * DT;
	pOwner->SetPos(vMonPos);



}

void CTrace::exit()
{
}