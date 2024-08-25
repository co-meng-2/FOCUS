#include "pch.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CDebugMgr.h"
#include "CResMgr.h"
#include "CSound.h"

#include "CSceneMgr.h"

#include "CImage.h"
#include "CPlayer.h"
#include "CFragments.h"
#include "CExplosion.h"
#include "CScene.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"



CMissile::CMissile()
	: m_pImage(nullptr)
	, m_fSpeed(100.f)
	, m_fCurvature(0.1f)
	, m_vPrevDir(0.f, 0.f)
	, m_fAngle(0.f)
	, m_fMaxSpeed(400.f)
	, m_eExplosionType(EXPLOSION_TYPE::SECOND)
{
	m_pImage = CResMgr::GetInst()->LoadImg(L"Missile_01", L"image\\Missile\\Missile_800_50_16.bmp");

	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(10.f, 10.f));

	CImage* pImage = CResMgr::GetInst()->FindImg(L"FireEffectAtlas");
	AddComponent(new CAnimator);
	GetAnimator()->CreateAnimation(L"FireEffect", pImage, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), 16.f, 5, 0.05f);
	GetAnimator()->Play(L"FireEffect", true);
}

CMissile::~CMissile()
{
	if (IsExplosive && !gChangeSceneFrame)
	{  
		CObject* pExplosion = new CExplosion(m_eExplosionType);
		pExplosion->SetPos(GetPos());
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pExplosion, LAYER_TYPE::EXPLOSION);
		 
		CSound* m_pExplosionSound = CResMgr::GetInst()->FindSound(L"Explosion");
		m_pExplosionSound->SetVolume(15.f);
		m_pExplosionSound->Play();
	}
	else if (!IsExplosive && !gChangeSceneFrame)
	{
		CObject* pExplosion = new CExplosion(EXPLOSION_TYPE::THIRD);
		pExplosion->SetPos(GetPos());
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pExplosion, LAYER_TYPE::EXPLOSION);

		CSound* m_pExplosionSound = CResMgr::GetInst()->FindSound(L"Explosion");
		m_pExplosionSound->SetVolume(15.f);
		m_pExplosionSound->Play();
	}

	if (HasFragments && !gChangeSceneFrame)
	{
		int iCount = 0;
		Vec2 vPos = GetPos();

		if (m_fAngle < 0.f)
		{
			while (m_fAngle < 0.f)
				m_fAngle += 2  * PI;
		}

		if (m_fAngle > 2 * PI)
		{
			while (m_fAngle > 2 * PI)
			{
				m_fAngle -=  2 * PI;
			}
		}

		if (m_fAngle < PI)
			vPos.x -= 20.f;
		else
			vPos.x += 20.f;

		if (m_fAngle >= 0.f && m_fAngle <= PI / 4 || m_fAngle >= PI / 4 * 6 && m_fAngle <= PI * 2)
			vPos.y += 20.f ;
		else
			vPos.y -= 20.f;
		

		while (iCount < 3)
		{
			CObject* pFragment = Instantiate<CFragments>(vPos, LAYER_TYPE::FRAGMENT);
			++iCount;
		}
	}
}

void CMissile::tick()
{
	SelectDeltaTime();
	// 미사일이 향하는 방향으로 이동한다.
	Vec2 vPos = GetPos();

	if (IsLine)
	{
		if (HasAccel)
			m_fSpeed = m_fForce * GetDT();
	}
	else if (!IsLine)
	{
		Vec2 vDir = (m_pPlayer->GetPos() - GetPos()).Normalize();
		if (m_vPrevDir != Vec2(0.f, 0.f))
		{
			float fDot = vDir.Dot(m_vPrevDir);
			float fAngle = acosf(fDot);
			fAngle = (fAngle / PI) * 180.f; // 0 - PI -> 0 - 180

			float fRotateAngle = m_fCurvature * GetDT();

			if (fRotateAngle >= fAngle)
				m_fSpeed += m_fForce * GetDT();
			else
			{
				m_fSpeed -= m_fForce * GetDT();
			}

			if (fAngle < fRotateAngle)
			{
				fRotateAngle = fAngle;
			}

			if (0.f > CrossVector(m_vPrevDir, vDir))
				fRotateAngle *= -1.f;
				

			vDir = RotateVector(m_vPrevDir, fRotateAngle);
		}
		SetDir(vDir);
	}


	if (m_fSpeed <= 200.f)
	{
		m_fSpeed = 200.f;
	}


	if (m_fSpeed >= m_fMaxSpeed)
		m_fSpeed = m_fMaxSpeed;

	vPos.x += m_fSpeed * m_vDir.x * GetDT();
	vPos.y += m_fSpeed * m_vDir.y * GetDT();

	SetPos(vPos);
	m_vPrevDir = m_vDir;

	CObject::tick();
}

void CMissile::render(HDC _dc)
{	
	// 미사일 진행 방향에 따른 인덱스 계산
	UINT iWidth = m_pImage->GetWidth() / 16;

	float fDot = m_vDir.Dot(Vec2(0.f, -1.f));
	m_fAngle = acosf(fDot);

	// 각도가 180 를 넘을 때 보정하기 (양의 각도(작은 쪽) 로만 나오므로 더 큰 쪽 각도를 구하기 위함
	if (m_vDir.x < 0.f)
		m_fAngle = PI * 2 - m_fAngle;

	// fAngle += PI / 16.f;

	int iImgIdx = 15 - (int)floor(m_fAngle / (2.f * PI / 16.f));
	if (iImgIdx <= -1)
	{
		iImgIdx = 15;
	}



	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	// alphablend 로 변환
	AlphaBlend(_dc
		, (int)vPos.x - iWidth / 2
		, (int)vPos.y - m_pImage->GetHeight() / 2
		, iWidth
		, m_pImage->GetHeight()
		, m_pImage->GetDC()
		, iImgIdx * iWidth
		, 0
		, iWidth
		, m_pImage->GetHeight()
		, tFunc);

	CObject::render(_dc);
}

void CMissile::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	DeleteObject(this);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	else
	{
		// DeleteObject(pPlayer);
		if(!IsInvincibleD)
			pPlayer->SetDead();
	}
}

void CMissile::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CMissile::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}

