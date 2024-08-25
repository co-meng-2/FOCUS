#include "pch.h"
#include "CMonster.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"

#include "CEventMgr.h"
#include "CMissile.h"
#include "CRigidBody.h"
#include "CAI.h"

#include "CIdle.h"
#include "CTrace.h"

CMonster::CMonster()
	: m_info{}
	, m_pImage(nullptr)
	, m_pPlayer(nullptr)
{
	m_info.fDetectRange = 400.f;
	m_info.fSpeed = 200.f;


	AddComponent(new AI);
	AddComponent(new CCollider);
	AddComponent(new CRigidBody);

	GetCollider()->SetOffset(Vec2(0.f, -35.f));
	GetCollider()->SetScale(Vec2(320.f, 130.f));

	m_pImage = CResMgr::GetInst()->LoadImg(L"Monster", L"image\\Monster.bmp");


	GetAI()->AddState(L"IDLE", new CIdle);
	GetAI()->AddState(L"TRACE", new CTrace);
	GetAI()->ChangeState(L"IDLE");
}

CMonster::CMonster(const CMonster& _mon)
	: CObject(_mon)
	, m_pImage(_mon.m_pImage)
	, m_pPlayer(_mon.m_pPlayer)
{
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{
	CObject::tick();	

}

void CMonster::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	/*TransparentBlt(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
		, (int)vPos.y - m_pImage->GetHeight() / 2
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));*/


	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;	
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, (int)vPos.x - m_pImage->GetWidth() / 2
		, (int)vPos.y - m_pImage->GetHeight() / 2
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, m_pImage->GetDC()
		, 0
		, 0
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, tFunc);

	CObject::render(_dc);
}

void CMonster::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	if (dynamic_cast<CMissile*>(_pOhterCollider->GetOwner()))
	{
		//DeleteObject(this);
	}
}
