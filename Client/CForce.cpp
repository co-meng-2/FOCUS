#include "pch.h"
#include "CForce.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CRigidBody.h"

CForce::CForce()
	: m_fForce(0.f)
	, m_fRadius(0.f)
	, m_fDuration(0.f)
	, m_fAccTime(0.f)
{
}

CForce::~CForce()
{
}


void CForce::tick()
{
	m_fAccTime += DT;
	if (m_fDuration <= m_fAccTime)
	{
		DeleteObject(this);
		return;
	}
	

	
	AddForceToLayer(LAYER_TYPE::PLAYER);
	AddForceToLayer(LAYER_TYPE::MONSTER);
}


void CForce::AddForceToLayer(LAYER_TYPE _eType)
{

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecObj = pCurScene->GetObjects(_eType);

	Vec2 vForcePos = GetPos();

	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		if (!vecObj[i]->GetRigidBody() || vForcePos.Distance(vecObj[i]->GetPos()) > m_fRadius)
		{
			continue;
		}

		Vec2 vForce = (vecObj[i]->GetPos() - vForcePos).Normalize() * m_fForce;
		vecObj[i]->GetRigidBody()->AddForce(vForce);
	}
}

void CForce::render(HDC _dc)
{
	tSelectPen pen(_dc, PEN_COLOR::BLUE);
	tSelectBrush brush(_dc, BRUSH_COLOR::HOLLOW);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());


	float fRatio = (m_fAccTime / m_fDuration);
	float fRadius = m_fRadius * (fRatio - floorf(fRatio));

	Ellipse(_dc
		,(int)( vPos.x - fRadius)
		,(int)( vPos.y - fRadius)
		,(int)( vPos.x + fRadius)
		,(int)( vPos.y + fRadius));
}

