#include "pch.h"
#include "CCrystal.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CSound.h"

#include "CPlayer.h"

#include "CCollider.h"

CCrystal::CCrystal(CRYSTAL_TYPE _CT)
	: m_eCT(_CT)
	, m_fAccTime(0.f)
	, m_fShakeTime(1.5f)
	, m_fCoolTime(1.f)
	, m_bShakeStart(false)
	, m_bShakeDir(false)
{
	m_pImage = CResMgr::GetInst()->FindImg(L"CrystalImage");
	m_pSound = CResMgr::GetInst()->FindSound(L"Crystal");
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2((float)TILE_SIZE , (float)TILE_SIZE));
}

CCrystal::~CCrystal()
{
}

void CCrystal::tick()
{
	SelectDeltaTime();
	m_fAccTime += GetDT();

	if (m_fCoolTime <= m_fAccTime && !m_bShakeStart)
	{
		m_bShakeStart = true;
		m_fAccTime = 0.f;
	}

	if (m_bShakeStart)
	{
		if (m_fAccTime <= m_fShakeTime)
		{
			if (m_bShakeDir)
			{
				SetPos(Vec2(m_vOriginPos.x - 1, m_vOriginPos.y));
				m_bShakeDir = false;
			}
			else
			{
				SetPos(Vec2(m_vOriginPos.x + 1, m_vOriginPos.y));
				m_bShakeDir = true;
			}
		}
		else
		{
			m_fAccTime = 0.f;
			m_bShakeStart = false;
			SetPos(m_vOriginPos);
		}
	}

	CObject::tick();
}

void CCrystal::render(HDC _dc)
{
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	AlphaBlend(_dc
		, int(vPos.x - (m_pImage->GetWidth() / 2.f))
		, int(vPos.y - (m_pImage->GetHeight() / 2.f))
		, int(m_pImage->GetWidth())
		, int(m_pImage->GetHeight())
		, m_pImage->GetDC()
		, 0
		, 0
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, tFunc);

	CObject::render(_dc);
}

void CCrystal::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
	{
		return;
	}
	else
	{
		if (m_eCT == CRYSTAL_TYPE::STARTER)
		{
			pPlayer->SetHasFocus(true);
			DeleteObject(this);
		}

		if (m_eCT == CRYSTAL_TYPE::ENHANCER)
		{
			pPlayer->SetMaxFocusRadius(pPlayer->GetMaxFocusRadius() * 2.f);
			pPlayer->SetCurFocusRadius(pPlayer->GetMaxFocusRadius() * 2.f);
			DeleteObject(this);
		}

		m_pSound->SetVolume(80.f);
		m_pSound->Play();
	}
}

void CCrystal::CollisionOverlap(CCollider* _pOtherCollider)
{
}

void CCrystal::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}