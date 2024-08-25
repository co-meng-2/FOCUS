#include "pch.h"
#include "CMissileTurret.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CSceneMgr.h"

#include "CSound.h"

#include "CScene.h"
#include "CMissile.h"
#include "CImage.h"

#include "CGauge.h"


CMissileTurret::CMissileTurret()
	: m_fCoolTime(2.f)
	, m_fAccTime(0.f)
	, m_fDetectRadius(500.f)
	, m_fHideTime(0.f)
	, DetectPlayer(true)
	, m_fCoolCoolTime(2.f)
	, m_fCoolAccTime(2.f)
	, m_bRenderGauge(false)
	, m_fMaxSpeed(400.f)
{
	CImage* pTurret = CResMgr::GetInst()->LoadImg(L"Turret_Move", L"image\\Turret_Move.bmp");

	AddComponent(new CGauge);
}

CMissileTurret::~CMissileTurret()
{
}



void CMissileTurret::tick()
{
	SelectDeltaTime();
	m_fCoolAccTime += GetDT();

	if (m_fCoolAccTime >= m_fCoolCoolTime)
	{
		if (DetectPlayer && m_pPlayer->GetPos().Distance(GetPos()) <= m_fDetectRadius)
		{
			m_fAccTime += m_fDeltaTime;

			m_fHideTime = 0.f;

			m_bRenderGauge = true;
		}
		else
		{
			m_fHideTime += m_fDeltaTime;

			if (m_fHideTime > 0.5f)
				m_fAccTime = 0.f;

			m_bRenderGauge = false;
		}

		if (m_fAccTime >= m_fCoolTime)
		{
			SpawnMissile();
			m_fAccTime = 0.f;
			m_fCoolAccTime = 0.f;

			m_bRenderGauge = false;

			CSound* m_pSpawnSound = CResMgr::GetInst()->FindSound(L"MissileSpawn");
			m_pSpawnSound->SetVolume(20.f);
			m_pSpawnSound->Play();
		}
	}

	CObject::tick();
}

void CMissileTurret::render(HDC _dc)
{
	CImage* pTurret = CResMgr::GetInst()->LoadImg(L"Turret_Move", L"image\\Turret_Move.bmp");
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	//BLENDFUNCTION tFunc = {};
	//tFunc.BlendOp = AC_SRC_OVER;
	//tFunc.BlendFlags = 0;
	//tFunc.AlphaFormat = AC_SRC_ALPHA;
	//tFunc.SourceConstantAlpha = 255;

	//

	//AlphaBlend(_dc
	//	, int(vPos.x - pTurret->GetWidth() / 2.f)
	//	, int(vPos.y - pTurret->GetHeight() / 2.f)
	//	, pTurret->GetWidth()
	//	, pTurret->GetHeight()
	//	, pTurret->GetDC()
	//	, 0
	//	, 0
	//	, pTurret->GetWidth()
	//	, pTurret->GetHeight() 
	//	, tFunc);


	TransparentBlt(_dc
		, int(vPos.x - pTurret->GetWidth() / 2.f)
		, int(vPos.y - pTurret->GetHeight() / 2.f)
		, pTurret->GetWidth()
		, pTurret->GetHeight()
		, pTurret->GetDC()
		, 0
		, 0
		, pTurret->GetWidth()
		, pTurret->GetHeight()
		, RGB(255,0,255));

	CObject::render(_dc);
}

void CMissileTurret::SpawnMissile()
{
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(GetPos());
	pMissile->SetDir(m_pPlayer->GetPos() - GetPos());
	pMissile->m_fForce = m_fForce;
	pMissile->m_fCurvature = m_fCurvature;
	pMissile->m_fSpeed = m_fStartSpeed;
	pMissile->m_fMaxSpeed = m_fMaxSpeed;
	
	if (MISSILE_OPTION::LINE == m_eMissileType)
	{
		pMissile->IsLine = true;
	}
	else
	{
		pMissile->IsLine = false;
		pMissile->SetPlayer(m_pPlayer);
	}
	
	if (MISSILE_OPTION::EXPLOSIVE == m_eExplosive)
	{
		pMissile->IsExplosive = true;
	}
	else
	{
		pMissile->IsExplosive = false;
	}
	
	if (MISSILE_OPTION::FRAGMENTS == m_eFragments)
	{
		pMissile->HasFragments = true;
	}
	else
	{
		pMissile->HasFragments = false;
	}

	if (MISSILE_OPTION::ACCEL == m_eAccel)
	{
		pMissile->HasAccel = true;
	}
	else
	{
		pMissile->HasAccel = false;
	}

	AddObject_D(pMissile, LAYER_TYPE::PROJECTILES);
}