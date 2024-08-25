#include "pch.h"
#include "CMineSpawner.h"

#include "CSceneMgr.h"
#include "CScene.h"


#include "CResMgr.h"
#include "CImage.h"
#include "CSound.h"

#include "CAnimator.h"

#include "CMine.h"

#include "CGauge.h"

CMineSpawner::CMineSpawner()
	: m_fCoolTime(4.f)
	, m_fAccTime(0.f)
	, m_iMaxMineCount(1)
	, m_iMineCount(0)
{
	AddComponent(new CAnimator);

	m_pAtlas = CResMgr::GetInst()->FindImg(L"MineSpawnerAtlas");
	m_pSound = CResMgr::GetInst()->FindSound(L"SpawnMine");
	GetAnimator()->CreateAnimation(L"MineSpawnerAnimation", m_pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 120.f), Vec2(0.f, 0.f), 120.f, 7, 0.1f);
	GetAnimator()->Play(L"MineSpawnerAnimation", true);
}

CMineSpawner::~CMineSpawner()
{
}


void CMineSpawner::SpawnMine()
{
	m_pSound->Play();
	CMine* pMine = new CMine;
	pMine->SetPos(GetPos());
	pMine->m_pMineSpawner = this;
	CSceneMgr::GetInst()->GetCurScene()->AddObject((CObject*)pMine ,LAYER_TYPE::MINE);
}

void CMineSpawner::tick()
{
	SelectDeltaTime();
	if (m_iMineCount < m_iMaxMineCount)
	{
		m_fAccTime += m_fDeltaTime;

		if (m_fAccTime >= m_fCoolTime)
		{
			SpawnMine();
			m_fAccTime = 0.f;
			++m_iMineCount;
		}
	}
	CObject::tick();
}

void CMineSpawner::render(HDC _dc)
{
	CObject::render(_dc);
}



