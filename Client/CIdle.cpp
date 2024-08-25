#include "pch.h"
#include "CIdle.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"


CIdle::CIdle()
{
}

CIdle::~CIdle()
{
}

void CIdle::enter()
{
	// Player 를 찾는다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);
}

void CIdle::tick()
{
	// Monster 의 정보를 확인한다.
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);		
	float fDetectRange = pOwner->GetInfo().fDetectRange;
	float fDistance = (m_pPlayer->GetPos() - pOwner->GetPos()).Length();

	// Player 와 IdleState 의 소유 몬스터의 거리 차이가 몬스터의 탐지범위 이내라면
	if (fDistance < fDetectRange)
	{
		// 상태변경
		GetAI()->ChangeState(L"TRACE");
	}
}

void CIdle::exit()
{

}
