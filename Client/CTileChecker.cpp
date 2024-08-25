#include "pch.h"
#include "CTileChecker.h"

#include "CPlayer.h"
#include "CMissileTurret.h"
#include "CColliderObject.h"

#include "CCollider.h"

CTileChecker::CTileChecker(CObject* _pTurret, CObject* _pPlayer)
	: m_pTurret(_pTurret)
	, m_pPlayer(_pPlayer)
	, m_iCollisionCount(0)
{
	
}

CTileChecker::~CTileChecker()
{
}

void CTileChecker::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (nullptr == pColObj || !IsValid(pColObj))
		return;

	if (dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner())->GetColType() == (UINT)COLLIDER_TYPE::BLOCK)
	{
		++m_iCollisionCount;
		IsCollision = true;

		_pOtherCollider->SubCollisionCount();
	}
}

void CTileChecker::CollisionOverlap(CCollider* _pOtherCollider)
{

}

void CTileChecker::CollisionEndOverlap(CCollider* _pOtherCollider)
{

}

void CTileChecker::tick()
{
	
	vector<CComponent*>* vpComponent = GetSelectComponentBundle(COMPONENT_TYPE::COLLIDER);

	for (size_t j = 0; j < vpComponent->size(); ++j)
	{
		SAFE_DELETE(vpComponent->at(j));
	}

	vpComponent->resize(1);

	Vec2 vColliderVector;
	Vec2 vPtoT = m_pPlayer->GetPos() - m_pTurret->GetPos();
	vPtoT.Normalize();

	float proceed = 0.f;
	int count = 0;
	while (true)
	{
		vColliderVector = vPtoT * proceed;

		if ((m_pPlayer->GetPos() - m_pTurret->GetPos()).Length() <= vColliderVector.Length())
			break;
		
		AddComponent(new CCollider);
		CCollider* pCollider = dynamic_cast<CCollider*>(vpComponent->at(count));
		pCollider->SetScale(Vec2(10.f, 10.f));
		pCollider->SetFinalPos(vColliderVector + m_pTurret->GetPos());
		pCollider->SetFixed();
		proceed += 50.f;
		++count;
	}

	if (IsCollision)
	{
		dynamic_cast<CMissileTurret*>(m_pTurret)->GetDetectPlayer() = false;
	}
	else
	{
		dynamic_cast<CMissileTurret*>(m_pTurret)->GetDetectPlayer() = true;
	}

	m_iCollisionCount = 0;
	IsCollision = false;
}