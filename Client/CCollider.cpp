#include "pch.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CDebugMgr.h"

#include "CScene.h"
#include "CObject.h"
#include "CEngine.h"

#include "CColliderObject.h"
#include "CMine.h"

CCollider::CCollider()
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_vFixed(false)
	, m_iCollisionCount(0)
	, m_vOffsetPos(0.f, 0.f)
	, m_iBlockCollisionCount(0)
	, m_eShape(COLLIDER_SHAPE::RECT)
{
}

CCollider::CCollider(COLLIDER_SHAPE _eShape)
	: CComponent(COMPONENT_TYPE::COLLIDER)
	, m_vFixed(false)
	, m_iCollisionCount(0)
	, m_vOffsetPos(0.f, 0.f)
	, m_iBlockCollisionCount(0)
	, m_eShape(_eShape)
{

}

CCollider::CCollider(const CCollider& _collider)
	: CComponent(_collider)
	, m_vFixed(false)
	, m_vOffsetPos(_collider.m_vOffsetPos)
	, m_vScale(_collider.m_vScale)
	, m_vFinalPos()
	, m_iCollisionCount(0)
	, m_eShape(_collider.m_eShape)
{
}

CCollider::~CCollider()
{
}

void CCollider::tick()
{
	if (!m_vFixed)
	{
		CObject* pOwner = GetOwner();

		m_vFinalPos = pOwner->GetPos() + m_vOffsetPos;

		if (m_eShape == COLLIDER_SHAPE::RECT)
		{
			m_vLT = Vec2(m_vFinalPos.x - m_vScale.x/ 2.f, m_vFinalPos.y - m_vScale.y/ 2.f);
			m_vRT = Vec2(m_vFinalPos.x + m_vScale.x/ 2.f, m_vFinalPos.y - m_vScale.y/ 2.f);
			m_vRB = Vec2(m_vFinalPos.x + m_vScale.x/ 2.f, m_vFinalPos.y + m_vScale.y/ 2.f);
			m_vLB = Vec2(m_vFinalPos.x - m_vScale.x/ 2.f, m_vFinalPos.y + m_vScale.y/ 2.f);
		}
		else if(m_eShape == COLLIDER_SHAPE::LINE)
		{
			m_vStartDot = m_vFinalPos - m_vScale / 2.f;
			m_vEndDot = m_vFinalPos + m_vScale / 2.f;
		}
	}
}

void CCollider::render(HDC _dc)
{
	// 충돌 회수 제어 오류 발생
	assert(0 <= m_iCollisionCount);

	if (IsDebugModeD && (GetModeStatusD & (WORD)DEBUG_MODE::COLLIDER_RENDER))
	{
		tSelectPen pen(_dc);
		if (0 < m_iCollisionCount)
			pen.SetPenColor(PEN_COLOR::RED);
		else
			pen.SetPenColor(PEN_COLOR::GREEN);

		tSelectBrush brush(_dc, BRUSH_COLOR::HOLLOW);

		Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

		if (m_eShape == COLLIDER_SHAPE::RECT)
		{
			Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2.f)
				, (int)(vPos.y - m_vScale.y / 2.f)
				, (int)(vPos.x + m_vScale.x / 2.f)
				, (int)(vPos.y + m_vScale.y / 2.f));
		}
		else if(m_eShape == COLLIDER_SHAPE::LINE)
		{
			MoveToEx(_dc, m_vStartDot.x, m_vStartDot.y, NULL);
			LineTo(_dc, m_vEndDot.x, m_vEndDot.y);
		}
	}
}


void CCollider::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr != pColObj && IsValid(pColObj))
	{
		++m_iBlockCollisionCount;
	}

	CMine* pMine = dynamic_cast<CMine*>(_pOtherCollider->GetOwner());
	if (nullptr != pMine && IsValid(pMine))
	{
		++m_iBlockCollisionCount;
	}

	++m_iCollisionCount;


	GetOwner()->CollisionBeginOverlap(_pOtherCollider);
}

void CCollider::CollisionOverlap(CCollider* _pOtherCollider) 
{
	GetOwner()->CollisionOverlap(_pOtherCollider);
}

void CCollider::CollisionEndOverlap(CCollider* _pOtherCollider)
{
	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr != pColObj)
	{
		--m_iBlockCollisionCount;
	}

	CMine* pMine = dynamic_cast<CMine*>(_pOtherCollider->GetOwner());
	if (nullptr != pMine)
	{
		--m_iBlockCollisionCount;
	}
	--m_iCollisionCount;
	

	GetOwner()->CollisionEndOverlap(_pOtherCollider);
}