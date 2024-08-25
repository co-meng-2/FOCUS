#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CKeyMgr.h"
#include "CDebugMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CObject.h"
#include "CImage.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_pVeil(nullptr)
	, m_fAlpha(0.f)	
{	
	POINT ptResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CResMgr::GetInst()->CreateImg(L"Veil", ptResol.x, ptResol.y);
}

CCamera::~CCamera()
{
}

void CCamera::init()
{
	m_vResolution = CEngine::GetInst()->GetResolution();
	m_vLook = (m_vResolution / 2.f);
	m_vPrevLook = m_vLook;
}

void CCamera::tick()
{	
	if (IsDebugModeD)
	{
		if (IsPressed(KEY_TYPE::W))
		{
			m_vLook.y -= DT * 500.f;
		}
		if (IsPressed(KEY_TYPE::S))
		{
			m_vLook.y += DT * 500.f;
		}
		if (IsPressed(KEY_TYPE::A))
		{
			m_vLook.x -= DT * 500.f;
		}
		if (IsPressed(KEY_TYPE::D))
		{
			m_vLook.x += DT * 500.f;
		}
		if (IsPressed(KEY_TYPE::Q))
		{
			m_vLook = m_vResolution / 2;
		}
	}

	if (m_pTargetObj)
	{
		m_vLook = m_pTargetObj->GetPos();
	}
	
	// 처리할 카메라 효과가 있으면
	if (!m_CamEffectInfo.empty())
	{
		tCamEffectInfo& info = m_CamEffectInfo.front();

		info.fAccTime += DT;
		float fRatio = (info.fAccTime / info.fDuration);	// 제한 시간 대비 진행시간의 비율을 0 ~ 1 사이로 환산

		if (1.f <= fRatio)
		{
			fRatio = 1.f;

			if (CAM_EFFECT::SHAKE_HORIZONTAL == info.eEffect)
				m_vLook = m_vPrevLook;

			m_CamEffectInfo.pop_front();
		}
		
		else
		{
			if (CAM_EFFECT::FADE_IN == info.eEffect)
				m_fAlpha = 1.f - fRatio;
			else if (CAM_EFFECT::FADE_OUT == info.eEffect)
				m_fAlpha = fRatio;
			else if (CAM_EFFECT::SHAKE_HORIZONTAL == info.eEffect)
			{
				if (info.eMoveDir == MOVE_DIRECTION::L)
					m_vLook.x -= info.iShakeSpeed * DT;
				else
					m_vLook.x += info.iShakeSpeed * DT;

				if(fabs(m_vLook.x - m_vPrevLook.x) > info.iShakeWidth)
					if (info.eMoveDir == MOVE_DIRECTION::L)
					{
						info.eMoveDir = MOVE_DIRECTION::R;
						m_vLook.x = m_vPrevLook.x - info.iShakeWidth;
					}
					else
					{
						info.eMoveDir = MOVE_DIRECTION::L;
						m_vLook.x = m_vPrevLook.x + info.iShakeWidth;
					}
			}
			else
			{
				m_fAlpha = 0.f;
			}

		}
	}

	m_vDiff = m_vLook - (m_vResolution / 2.f);
}

void CCamera::render(HDC _dc)
{
	if (0.f == m_fAlpha)
		return;

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = 0;
	tFunc.SourceConstantAlpha = (BYTE)(255.f * m_fAlpha);

	AlphaBlend(_dc, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, m_pVeil->GetDC()
		, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, tFunc);

}
