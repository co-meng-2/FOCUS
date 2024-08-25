#include "pch.h"
#include "CPosChanger.h"


#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

#include "CResMgr.h"
#include "CImage.h"

#include "CScene.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CColliderObject.h"
#include "CMine.h"

#include "CCollider.h"

CPosChanger::CPosChanger()
	: m_vScale(20.f, 20.f)
	, m_fSpeed(500.f)
	, m_fSpeedX(500.f)
	, m_fSpeedY(500.f)
	, m_fInRadiusSpeed(100.f)
	, m_fAccelX(200.f)
	, m_fAccelY(200.f)
	, m_bOntheBlock(false)
	, m_pPlayer(nullptr)
	, m_eMD(MOVE_DIRECTION::L)
{
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(32.f, 32.f));

	m_pImage = CResMgr::GetInst()->FindImg(L"WhiteCircleImage");
	m_pImage2 = CResMgr::GetInst()->FindImg(L"RedCircleImage");
}

CPosChanger::~CPosChanger()
{
}

void CPosChanger::AddOffsetX()
{
	if (m_vOffsetPos.Length() <= m_pPlayer->GetCurFocusRadius() && m_eMD == MOVE_DIRECTION::R)
	{
		m_fSpeedX += m_fAccelX * DT;
	}
	else
		m_fSpeedX = m_fSpeed;

	m_vOffsetPos.x += m_fSpeedX * DT;
	if (m_vOffsetPos.Length() >= m_pPlayer->GetCurFocusRadius())
	{
		m_vOffsetPos.x -= m_fSpeedX * DT;
	}

	m_eMD = MOVE_DIRECTION::R;
}

void CPosChanger::SubOffsetX()
{
	if (m_vOffsetPos.Length() <= m_pPlayer->GetCurFocusRadius() && m_eMD == MOVE_DIRECTION::L)
	{
		m_fSpeedX += m_fAccelX * DT;
		
	}
	else
		m_fSpeedX = m_fSpeed;

	m_vOffsetPos.x -= m_fSpeedX * DT;
	if (m_vOffsetPos.Length() >= m_pPlayer->GetCurFocusRadius())
	{
		m_vOffsetPos.x += m_fSpeedX * DT;
	}

	m_eMD = MOVE_DIRECTION::L;
}

void CPosChanger::AddOffsetY()
{
	if (m_vOffsetPos.Length() <= m_pPlayer->GetCurFocusRadius() && m_eMD == MOVE_DIRECTION::D)
	{
		m_fSpeedY += m_fAccelY * DT;
	}
	else
		m_fSpeedY = m_fSpeed;


	m_vOffsetPos.y += m_fSpeedY * DT;
	if (m_vOffsetPos.Length() >= m_pPlayer->GetCurFocusRadius())
	{
		m_vOffsetPos.y -= m_fSpeedX * DT;
	}

	m_eMD = MOVE_DIRECTION::D;
}

void CPosChanger::SubOffsetY()
{
	if (m_vOffsetPos.Length() <= m_pPlayer->GetCurFocusRadius() && m_eMD == MOVE_DIRECTION::U)
	{
		m_fSpeedY += m_fAccelY * DT;	
	}
	else
		m_fSpeedY = m_fSpeed;

	m_vOffsetPos.y -= m_fSpeedY * DT;
	if (m_vOffsetPos.Length() >= m_pPlayer->GetCurFocusRadius())
	{
		m_vOffsetPos.y += m_fSpeedX * DT;
	}

	m_eMD = MOVE_DIRECTION::U;
}

void CPosChanger::CollisionBeginOverlap(CCollider* _pOtherCollider)
{

}

void CPosChanger::CollisionOverlap(CCollider* _pOtherCollider)
{
	CMine* pMine = dynamic_cast<CMine*>(_pOtherCollider->GetOwner());
	if (pMine != nullptr && IsValid(pMine))
	{
		m_bOntheBlock = true;
	}

	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (pColObj != nullptr && IsValid(pColObj))
	{
		m_bOntheBlock = true;
	}
}

void CPosChanger::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	CMine* pMine = dynamic_cast<CMine*>(_pOtherCollider->GetOwner());
	if (pMine != nullptr && IsValid(pMine))
	{
		if (GetCollider()->GetCollisionCount() == 0)
			m_bOntheBlock = false;
	}

	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (pColObj != nullptr && IsValid(pColObj))
	{
		if (GetCollider()->GetCollisionCount() == 0)
			m_bOntheBlock = false;
	}
	
}

// 범위 밖으로 못 나감
// + BLOCK 안으로 or 맵 밖으로 못 나가게
void CPosChanger::tick()
{
	
	/*if (m_pPlayer->m_bFocus)*/
	{
		Vec2 vPos = m_pPlayer->GetPos();
		Vec2 vTempFinalPos = vPos + m_vOffsetPos;

		// 원 밖
		if (m_vOffsetPos.Length() >= m_pPlayer->GetCurFocusRadius())
		{
			Vec2 vOffset = m_vOffsetPos;
			vOffset.Normalize();

			m_vOffsetPos -= vOffset * m_fInRadiusSpeed * DT;
		}


		// 맵 밖 값 보정
		// 맵 밖
		if (vTempFinalPos.x <= 0.f)
		{
			m_vOffsetPos.x = 0.f - vPos.x;
		}
		if (vTempFinalPos.x >= 1028.f)
		{
			m_vOffsetPos.x = 1028.f - vPos.x;
		}
		if (vTempFinalPos.y <= 0.f)
		{
			m_vOffsetPos.y = 0.f - vPos.y;
		}
		if (vTempFinalPos.y >= 768.f)
		{
			m_vOffsetPos.y = 768.f - vPos.y;
		}

		m_vFinalPos = CCamera::GetInst()->GetRenderPos(vPos + m_vOffsetPos);

		SetPos(m_pPlayer->GetPos() + m_vOffsetPos);
		CObject::tick();
	}
}

void CPosChanger::render(HDC _dc)
{
	//tSelectPen Pen = tSelectPen(_dc, PEN_COLOR::WHITE);
	//tSelectBrush Brush = tSelectBrush(_dc, BRUSH_COLOR::HOLLOW);
	if (m_pPlayer->IsFocus())
	{
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 50;

		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		UINT Width = m_pImage->GetWidth();
		UINT Height = m_pImage->GetHeight();

		if (!IsOntheBlock())
		{
			AlphaBlend(_dc
				, int(vPos.x - float(Width / 12))
				, int(vPos.y - float(Width / 12))
				, Width / 6
				, Height / 6
				, m_pImage->GetDC()
				, 0
				, 0
				, Width
				, Height
				, tFunc);
		}
		else
		{
			AlphaBlend(_dc
				, int(vPos.x - float(Width / 12))
				, int(vPos.y - float(Width / 12))
				, Width / 6
				, Height / 6
				, m_pImage2->GetDC()
				, 0
				, 0
				, Width
				, Height
				, tFunc);
		}
		//Ellipse(_dc,
		//	int(m_vFinalPos.x - m_vScale.x / 2.f),
		//	int(m_vFinalPos.y - m_vScale.y / 2.f),
		//	int(m_vFinalPos.x + m_vScale.x / 2.f),
		//	int(m_vFinalPos.y + m_vScale.y / 2.f)
		//);

		CObject::render(_dc);
	}
}


