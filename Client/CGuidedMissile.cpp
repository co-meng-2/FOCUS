//#include "pch.h"
//#include "CGuidedMissile.h"
//
//#include "CTimeMgr.h"
//
//#include "CSceneMgr.h"
//#include "CScene.h"
//
//#include "CMonster.h"
//#include "CCollider.h"
//
//CGuidedMissile::CGuidedMissile()
//	: m_pTarget(nullptr)
//	, m_fRotateSpeed(100.f)
//	, m_fDetectRange(1000.f)
//{
//
//}
//
//CGuidedMissile::~CGuidedMissile()
//{
//
//}
//
//void CGuidedMissile::tick()
//{
//	// 타겟을 찾는다.
//	FindTarget();
//
//	if (nullptr != m_pTarget)
//	{
//		// 타겟을 향해서 방향을 회전한다.		
//		Vec2 vMonPos = m_pTarget->GetPos();
//		Vec2 vMissilePos = GetPos();
//
//		Vec2 vDirToMon = vMonPos - vMissilePos;
//		Vec2 vMissileDir = GetDir();
//
//		vDirToMon.Normalize();
//		vMissileDir.Normalize();
//
//		float fDot = vMissileDir.Dot(vDirToMon);
//		float fAngle = acosf(fDot); // 미사일의 진행방향과 몬스터를 향하는 방향 사이의 각도를 구함
//		fAngle = (fAngle / PI) * 180.f; // Radian to Degree
//
//		float fRotateAngle = m_fRotateSpeed * DT; // 회전 각도 크기
//
//		if (fAngle < fRotateAngle)
//		{
//			fRotateAngle = fAngle;
//		}
//
//		if (0.f < CrossVector(vDirToMon, vMissileDir))
//			fRotateAngle *= -1.f;
//
//		vMissileDir = RotateVector(vMissileDir, fRotateAngle);
//		SetDir(vMissileDir);
//	}
//
//	CMissile::tick();
//}
//
//void CGuidedMissile::FindTarget()
//{
//	if (IsValid(m_pTarget))
//		return;
//
//	Vec2 vMissilePos = GetPos();
//
//	// 현재 Scene 을 찾는다.
//	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
//
//	// Monster Layer 를 가져온다.
//	const vector<CObject*>& vecMon = pCurScene->GetObjects(LAYER_TYPE::MONSTER);
//
//	float fDistance = m_fDetectRange;
//	for (size_t i = 0; i < vecMon.size(); ++i)
//	{
//		float fDist = vMissilePos.Distance(vecMon[i]->GetPos());
//
//		if (fDist < fDistance)
//		{
//			fDistance = fDist;
//			m_pTarget = vecMon[i];
//		}
//	}
//}
//
//
//void CGuidedMissile::render(HDC _dc)
//{
//
//	CMissile::render(_dc);
//}
//
//
//
//
//
//void CGuidedMissile::CollisionBeginOverlap(CCollider* _pOhterCollider)
//{
//	if (dynamic_cast<CMonster*>(_pOhterCollider->GetOwner()))
//	{
//		DeleteObject(this);
//	}
//}