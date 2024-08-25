#include "pch.h"
#include "CBlockChecker.h"

#include "CMissileTurret.h"
#include "CPlayer.h"
#include "CColliderObject.h"

#include "CCollider.h"




CBlockChecker::CBlockChecker(CPlayer* _pPlayer, CMissileTurret* _pTurret)
	: m_pPlayer(_pPlayer)
	, m_pTurret(_pTurret)
	, m_fSlope(0.f)
	, IsBlock(false)
{
	AddComponent(new CCollider(COLLIDER_SHAPE::LINE));
}

CBlockChecker::~CBlockChecker()
{

}


float CBlockChecker::CalSlope(Vec2 _vL, Vec2 _vR)
{
	return (_vL.y - _vR.y) / (_vL.x - _vR.x);
}

void CBlockChecker::tick()
{
	float fColScaleX = m_pPlayer->GetPos().x - m_pTurret->GetPos().x;
	float fColScaleY = m_pPlayer->GetPos().y - m_pTurret->GetPos().y;
	GetCollider()->SetScale(Vec2(fColScaleX, fColScaleY));

	Vec2 vPos = (m_pPlayer->GetPos() + m_pTurret->GetPos()) / 2.f;
	SetPos(vPos);

	// m_fSlope = (m_pTurret->GetPos().y - m_pPlayer->GetCollider()->GetFinalPos().y) / (m_pTurret->GetPos().x - m_pPlayer->GetCollider()->GetFinalPos().x);

	if (IsBlock)
	{
		m_pTurret->GetDetectPlayer() = false;
	}
	else
	{
		m_pTurret->GetDetectPlayer() = true;
	}


	IsBlock = false;
	CObject::tick();
}

void CBlockChecker::render(HDC _dc)
{
	CObject::render(_dc);
}

void CBlockChecker::CollisionBeginOverlap(CCollider* _pOtherCollider)
{

}

void CBlockChecker::CollisionOverlap(CCollider* _pOtherCollider)
{
	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr == pColObj || !IsValid(pColObj))
		return;

	//SD fSlopeDotArr[4] = {};
	//Vec2 vLT = pColObj->GetPos() - pColObj->GetCollider()->GetScale() / 2.f + pColObj->GetCollider()->GetOffset();
	//Vec2 vRB = pColObj->GetPos() + pColObj->GetCollider()->GetScale() / 2.f + pColObj->GetCollider()->GetOffset();

	//fSlopeDotArr[(UINT)RECTPOSITION::LT] = { CalSlope(vLT, m_pTurret->GetPos()), vLT };
	//fSlopeDotArr[(UINT)RECTPOSITION::RT] = { CalSlope(Vec2(vRB.x, vLT.y), m_pTurret->GetPos()), Vec2(vRB.x, vLT.y) };
	//fSlopeDotArr[(UINT)RECTPOSITION::LB] = { CalSlope(Vec2(vLT.x, vRB.y), m_pTurret->GetPos()), Vec2(vLT.x, vRB.y) };
	//fSlopeDotArr[(UINT)RECTPOSITION::RB] = { CalSlope(vRB, m_pTurret->GetPos()), vRB };

	//SD fMinSlope = fSlopeDotArr[(UINT)RECTPOSITION::LT];
	//SD fMaxSlope = fSlopeDotArr[(UINT)RECTPOSITION::LT];
	//for (int i = 1; i < 4; ++i)
	//{
	//	if (fMinSlope.slope >= fSlopeDotArr[i].slope)
	//		fMinSlope = fSlopeDotArr[i];

	//	if (fMaxSlope.slope <= fSlopeDotArr[i].slope)
	//		fMaxSlope = fSlopeDotArr[i];
	//}

	//// 기울기 사이 선택
	//if (m_pTurret->GetPos().x - fMinSlope.dot.x >= 0 && m_pTurret->GetPos().x - fMaxSlope.dot.x <= 0)
	//{
	//	if (m_fSlope <= fMinSlope.slope || m_fSlope >= fMaxSlope.slope)
	//		IsBlock = true;
	//}
	//else
	//{
	// 	if (m_fSlope >= fMinSlope.slope && m_fSlope <= fMaxSlope.slope)
	//		IsBlock = true;
	//}
	IsBlock = true;
}

void CBlockChecker::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}


