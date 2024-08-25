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
	// Player �� ã�´�.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);
}

void CIdle::tick()
{
	// Monster �� ������ Ȯ���Ѵ�.
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);		
	float fDetectRange = pOwner->GetInfo().fDetectRange;
	float fDistance = (m_pPlayer->GetPos() - pOwner->GetPos()).Length();

	// Player �� IdleState �� ���� ������ �Ÿ� ���̰� ������ Ž������ �̳����
	if (fDistance < fDetectRange)
	{
		// ���º���
		GetAI()->ChangeState(L"TRACE");
	}
}

void CIdle::exit()
{

}
