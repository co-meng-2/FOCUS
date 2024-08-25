#include "pch.h"
#include "CEffect.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CImage.h"

#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect::CEffect()
	: m_pObj(nullptr)
	, m_fRatio(0.f)
	, m_bOrder(false)
	, m_pFocusBackground(nullptr)
	, m_wCurAnimKey(L"FocusEffect0")
	, m_fAccTime(0.f)
	, m_fCoolTime(2.f)
	, m_iRandHour(0)
	, m_iRandMinute(0)
{
	m_pClocMinutekAtlas = CResMgr::GetInst()->FindImg(L"ClockMinuteAtlas");
	m_pClockHourAtlas = CResMgr::GetInst()->FindImg(L"ClockHourAtlas");
	m_pFocusBackground = CResMgr::GetInst()->FindImg(L"FocusBackgroundImage");
	m_pFocusBackground->SetScaleChange(true);

	// AddComponent(new CAnimator);
	CImage* pFocusEffectAtlas = CResMgr::GetInst()->FindImg(L"FocusGreenEffectAtlas");
	pFocusEffectAtlas->SetScaleChange(true);

	//GetAnimator()->CreateAnimation(L"FocusEffect0", pFocusEffectAtlas, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	// GetAnimator()->CreateAnimation(L"FocusEffect1", pFocusEffectAtlas, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(0.f, -6.f), 100.f, 10, 0.05f);
	//GetAnimator()->CreateAnimation(L"FocusEffect2", pFocusEffectAtlas, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	//GetAnimator()->CreateAnimation(L"FocusEffect3", pFocusEffectAtlas, Vec2(0.f, 300.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	//GetAnimator()->CreateAnimation(L"FocusEffect4", pFocusEffectAtlas, Vec2(0.f, 400.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	//GetAnimator()->CreateAnimation(L"FocusEffect5", pFocusEffectAtlas, Vec2(0.f, 500.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	//GetAnimator()->CreateAnimation(L"FocusEffect6", pFocusEffectAtlas, Vec2(0.f, 600.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	//GetAnimator()->CreateAnimation(L"FocusEffect7", pFocusEffectAtlas, Vec2(0.f, 700.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 10, 0.05f);
	/*GetAnimator()->CreateAnimation(L"FocusEffect8", pFocusEffectAtlas, Vec2(0.f, 800.f), Vec2(100.f, 100.f), Vec2(0.f, -6.f), 100.f, 10, 0.1f);*/
	/*GetAnimator()->CreateAnimation(L"FocusEffect9", pFocusEffectAtlas, Vec2(0.f, 900.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 100.f, 1, 0.05f);*/

	/*GetAnimator()->Play(L"FocusEffect0", false);*/
	// GetAnimator()->Play(L"FocusEffect1", true);
}

CEffect::~CEffect()
{
	
}

void CEffect::tick()
{
	SelectDeltaTime();

	SetPos(m_pObj->GetPos());

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pObj);
	if (pPlayer->IsFocus())
		CObject::tick();
}

void CEffect::render(HDC _dc)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pObj);


	if (pPlayer->GetHasFocus())
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 10;

		if (pPlayer->IsFocus())
		{
			tFunc.SourceConstantAlpha = 100;
		}


		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		float CurFocusRadius = pPlayer->GetCurFocusRadius();

		AlphaBlend(_dc
			, int(vPos.x - CurFocusRadius)
			, int(vPos.y - CurFocusRadius)
			, int(CurFocusRadius * 2.f)
			, int(CurFocusRadius * 2.f)
			, m_pFocusBackground->GetDC()
			, 0
			, 0
			, m_pFocusBackground->GetWidth()
			, m_pFocusBackground->GetHeight()
			, tFunc);

		if (pPlayer->IsFocus())
		{
			m_fAccTime += DT;
			tFunc.SourceConstantAlpha = 0.f;

			if (m_fAccTime >= m_fCoolTime)
			{
				m_iRandHour = (int)(rand() % 12);
				m_iRandMinute = (int)(rand() % 12);

				m_fAccTime = 0.f;
			}
			else
			{
				if ((float)m_fAccTime / (float)m_fCoolTime < 0.5f)
					tFunc.SourceConstantAlpha = 100.f * (float)m_fAccTime / (float)m_fCoolTime;
				else
					tFunc.SourceConstantAlpha = 100.f - 100.f * (float)m_fAccTime / (float)m_fCoolTime;
			}

			AlphaBlend(_dc
				, int(vPos.x - CurFocusRadius)
				, int(vPos.y - CurFocusRadius)
				, int(CurFocusRadius * 2.f)
				, int(CurFocusRadius * 2.f)
				, m_pClockHourAtlas->GetDC()
				, m_pClockHourAtlas->GetWidth() / 12 * m_iRandHour
				, 0
				, m_pClockHourAtlas->GetWidth() / 12
				, m_pClockHourAtlas->GetHeight()
				, tFunc);

			AlphaBlend(_dc
				, int(vPos.x - CurFocusRadius)
				, int(vPos.y - CurFocusRadius)
				, int(CurFocusRadius * 2.f)
				, int(CurFocusRadius * 2.f)
				, m_pClocMinutekAtlas->GetDC()
				, m_pClocMinutekAtlas->GetWidth() / 12 * m_iRandMinute
				, 0
				, m_pClocMinutekAtlas->GetWidth() / 12
				, m_pClocMinutekAtlas->GetHeight()
				, tFunc);
		}
		else
		{
			m_fAccTime = 0.f;
			m_iRandHour = (int)(rand() % 12);
			m_iRandMinute = (int)(rand() % 12);
		}
			

		




		if (pPlayer->IsFocus())
			CObject::render(_dc);
	}
}


