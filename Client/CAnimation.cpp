#include "pch.h"
#include "CAnimation.h"

#include "CObject.h"
#include "CAnimator.h"

#include "CTimeMgr.h"
#include "CCamera.h"

#include "CPlayer.h"
#include "CEffect.h"
#include "CMissile.h"

#include "CImage.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pImage(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bCamRelation(false)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::tick()
{
	if (m_bFinish)
		return;

	m_fAccTime += m_fDeltaTime;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{		
		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;

		// 벡터의 인덱스를 초과한 경우 ==> Animation 재생 완료
		if (m_vecFrm.size() <= m_iCurFrm + 1)
		{
			m_bFinish = true;
		}
		else
		{
			++m_iCurFrm;
		}
	}	
}

void CAnimation::render(HDC _dc)
{
	CObject* pOwner = m_pAnimator->GetOwner();
	
	Vec2 vPos = pOwner->GetPos();

	if (m_bCamRelation)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	vPos += m_vecFrm[m_iCurFrm].vOffset;

	CMissile* pMissile = dynamic_cast<CMissile*>(m_pAnimator->GetOwner());
	CEffect* pEffect = dynamic_cast<CEffect*>(m_pAnimator->GetOwner());

	if (pMissile != nullptr && IsValid(pMissile))
	{
		tFunc.SourceConstantAlpha = 150;
		float fAngle = -pMissile->GetAngle();

		fAngle = floor(fAngle / (PI / 16.f)) * (PI / 16.f);


		vPos.x += sinf(fAngle) * 25.f;
		vPos.y += cosf(fAngle) * 25.f;

		//vPos.x += sinf(-pMissile->GetAngle()) * 25.f;
		//vPos.y += cosf(-pMissile->GetAngle()) * 25.f;


		AlphaBlend(_dc
			, int(vPos.x - m_vecFrm[m_iCurFrm].vSize.x / 2.f)
			, int(vPos.y - m_vecFrm[m_iCurFrm].vSize.y / 2.f)
			, int(m_vecFrm[m_iCurFrm].vSize.x)
			, int(m_vecFrm[m_iCurFrm].vSize.y)
			, m_pImage->GetDC()
			, int(m_vecFrm[m_iCurFrm].vLeftTop.x)
			, int(m_vecFrm[m_iCurFrm].vLeftTop.y)
			, int(m_vecFrm[m_iCurFrm].vSize.x)
			, int(m_vecFrm[m_iCurFrm].vSize.y)
			, tFunc);
	}
	else if (pEffect != nullptr && IsValid(pEffect))
	{
		if (m_pImage->HasScaleChange())
		{
			// float fRatio = pEffect->GetRatio();
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(pEffect->GetObj());
			float CurFocusRadius = pPlayer->GetCurFocusRadius();
			tFunc.SourceConstantAlpha = 50;

			AlphaBlend(_dc
				, int(vPos.x - pPlayer->GetCurFocusRadius() / 2.f * 3.f)
				, int(vPos.y - pPlayer->GetCurFocusRadius() / 2.f * 3.f)
				, int(pPlayer->GetCurFocusRadius() * 3.f)
				, int(pPlayer->GetCurFocusRadius() * 3.f)
				, m_pImage->GetDC()
				, int(m_vecFrm[m_iCurFrm].vLeftTop.x)
				, int(m_vecFrm[m_iCurFrm].vLeftTop.y)
				, int(m_vecFrm[m_iCurFrm].vSize.x)
				, int(m_vecFrm[m_iCurFrm].vSize.y)
				, tFunc);

			//TransparentBlt(_dc
			//	, int(vPos.x - CurFocusRadius / 2.f * 3.f)
			//	, int(vPos.y - CurFocusRadius / 2.f * 3.f)
			//	, int(CurFocusRadius * 3.f)
			//	, int(CurFocusRadius * 3.f)
			//	, m_pImage->GetDC()
			//	, int(m_vecFrm[m_iCurFrm].vLeftTop.x)
			//	, int(m_vecFrm[m_iCurFrm].vLeftTop.y)
			//	, int(m_vecFrm[m_iCurFrm].vSize.x)
			//	, int(m_vecFrm[m_iCurFrm].vSize.y)
			//	, RGB(255,0,255));
		}
	}
	else if (m_pImage->HasTransParent())
	{
		TransparentBlt(_dc
			, int(vPos.x - m_vecFrm[m_iCurFrm].vSize.x / 2.f)
			, int(vPos.y - m_vecFrm[m_iCurFrm].vSize.y / 2.f)
			, int(m_vecFrm[m_iCurFrm].vSize.x)
			, int(m_vecFrm[m_iCurFrm].vSize.y)
			, m_pImage->GetDC()
			, int(m_vecFrm[m_iCurFrm].vLeftTop.x)
			, int(m_vecFrm[m_iCurFrm].vLeftTop.y)
			, int(m_vecFrm[m_iCurFrm].vSize.x)
			, int(m_vecFrm[m_iCurFrm].vSize.y)
			, RGB(255, 0, 255));
	}
	else
	{
		AlphaBlend(_dc
			, int(vPos.x - m_vecFrm[m_iCurFrm].vSize.x / 2.f)
			, int(vPos.y - m_vecFrm[m_iCurFrm].vSize.y / 2.f)
			, int(m_vecFrm[m_iCurFrm].vSize.x)
			, int(m_vecFrm[m_iCurFrm].vSize.y)
			, m_pImage->GetDC()
			, int(m_vecFrm[m_iCurFrm].vLeftTop.x)
			, int(m_vecFrm[m_iCurFrm].vLeftTop.y)
			, int(m_vecFrm[m_iCurFrm].vSize.x)
			, int(m_vecFrm[m_iCurFrm].vSize.y)
			, tFunc);
	}
}

void CAnimation::Create(CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	m_pImage = _pImage;

	m_bCamRelation = _bCamRelation;

	for (UINT i = 0; i < _iFrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vLeftTop.x = _vLeftTop.x + (_fStep * (float)i);
		frm.vLeftTop.y = _vLeftTop.y;
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.fDuration = _fDuration;				

		m_vecFrm.push_back(frm);
	}
}