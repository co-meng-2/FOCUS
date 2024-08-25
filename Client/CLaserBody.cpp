#include "pch.h"
#include "CLaserBody.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CResMgr.h"
#include "CImage.h"

#include "CScene.h"

#include "CColliderObject.h"
#include "CLaser.h"
#include "CLaserStopper.h"

#include "CComponent.h"
#include "CCollider.h"



CLaserBody::CLaserBody(LASER_TYPE _laserType)
	: m_eLaserType(_laserType)
	, m_bHasLaser(false)
	, m_fMinusMax(-3000.f)
	, m_fPlusMin(3000.f)
	, m_fSpeed(100.f)
	, m_pImage(nullptr)
{
	AddComponent(new CCollider); // LASERCHECKER
	if (m_eLaserType == LASER_TYPE::HORIZONTAL)
		GetCollider()->SetScale(Vec2(4.f, 3000.f));
	else
		GetCollider()->SetScale(Vec2(3000.f, 4.f));

	if (m_eLaserType == LASER_TYPE::HORIZONTAL)
		m_eMoveDirection = MOVE_DIRECTION::L;
	else
		m_eMoveDirection = MOVE_DIRECTION::U;

	m_pImage = CResMgr::GetInst()->FindImg(L"LaserBodyImage");
}

CLaserBody::~CLaserBody()
{
}

void CLaserBody::tick()
{
	SelectDeltaTime();

	Vec2 vPos = GetPos();

	if (m_eLaserType == LASER_TYPE::HORIZONTAL)
	{
		if (m_eMoveDirection == MOVE_DIRECTION::L)
			vPos.x -= m_fSpeed * GetDT();
		else
			vPos.x += m_fSpeed * GetDT();
	}
	else
	{
		if (m_eMoveDirection == MOVE_DIRECTION::U)
			vPos.y -= m_fSpeed * GetDT();
		else
			vPos.y += m_fSpeed * GetDT();
	}

	if (m_bHasLaser)
	{
		if (m_eLaserType == LASER_TYPE::HORIZONTAL)
		{
			m_pLaser->GetCollider()->SetScale(Vec2(2.f, m_fPlusMin - m_fMinusMax - TILE_SIZE));
			m_pLaser->SetPos(Vec2(GetPos().x, ((m_vMinBlockPos.y + TILE_SIZE) + m_vMaxBlockPos.y) / 2.f));
		}
		else
		{
			m_pLaser->GetCollider()->SetScale(Vec2(m_fPlusMin - m_fMinusMax - TILE_SIZE, 2.f));
			m_pLaser->SetPos(Vec2((((m_vMinBlockPos.x + TILE_SIZE) + m_vMaxBlockPos.x) / 2.f), GetPos().y));
		}
		m_fMinusMax = -3000.f;
		m_fPlusMin = 3000.f;
	}
	SetPos(vPos);
	
	CObject::tick();
}

void CLaserBody::render(HDC _dc)
{

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, int(vPos.x - (m_pImage->GetWidth() / 2.f))
		, int(vPos.y - (m_pImage->GetHeight() / 2.f))
		, int(m_pImage->GetWidth())
		, int(m_pImage->GetHeight())
		, m_pImage->GetDC()
		, 0
		, 0
		, m_pImage->GetWidth()
		, m_pImage->GetHeight()
		, tFunc);

	//TransparentBlt(_dc
	//	, int(vPos.x - (m_pImage->GetWidth() / 2.f))
	//	, int(vPos.y - (m_pImage->GetHeight() / 2.f))
	//	, int(m_pImage->GetWidth())
	//	, int(m_pImage->GetHeight())
	//	, m_pImage->GetDC()
	//	, 0
	//	, 0
	//	, m_pImage->GetWidth()
	//	, m_pImage->GetHeight()
	//	, RGB(255, 0, 255));

	CObject::render(_dc);
}

void CLaserBody::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CLaserStopper* pLaserStopper = dynamic_cast<CLaserStopper*>(_pOtherCollider->GetOwner());
	if (pLaserStopper != nullptr && IsValid(pLaserStopper))
	{
		if (GetPos().Distance(pLaserStopper->GetPos()) < 40.f)
		{
			if (m_eLaserType == LASER_TYPE::HORIZONTAL)
			{
				if (m_eMoveDirection == MOVE_DIRECTION::L)
					m_eMoveDirection = MOVE_DIRECTION::R;
				else
					m_eMoveDirection = MOVE_DIRECTION::L;
			}
			else
			{
				if (m_eMoveDirection == MOVE_DIRECTION::U)
					m_eMoveDirection = MOVE_DIRECTION::D;
				else
					m_eMoveDirection = MOVE_DIRECTION::U;
			}
		}
	}
}

void CLaserBody::CollisionOverlap(CCollider* _pOtherCollider)
{
	CColliderObject* pColObj = dynamic_cast<CColliderObject*>(_pOtherCollider->GetOwner());
	if (pColObj != nullptr && IsValid(pColObj))
	{
		if (pColObj->GetColType() != (UINT)COLLIDER_TYPE::SCENE_CHANGE &&
			pColObj->GetColType() != (UINT)COLLIDER_TYPE::SPAWN &&
			pColObj->GetColType() != (UINT)COLLIDER_TYPE::THORN)
		{
			if (m_eLaserType == LASER_TYPE::HORIZONTAL)
			{
				float DistY = pColObj->GetPos().y - GetPos().y;
				if (DistY <= 0.f && m_fMinusMax < DistY)
				{
					m_fMinusMax = DistY;
					m_vMinBlockPos = pColObj->GetPos();
				}
				else if (DistY > 0.f && m_fPlusMin > DistY)
				{
					m_fPlusMin = DistY;
					m_vMaxBlockPos = pColObj->GetPos();
				}
			}
			else
			{
				float DistX = pColObj->GetPos().x - GetPos().x;
				if (DistX <= 0.f && m_fMinusMax < DistX)
				{
					m_fMinusMax = DistX;
					m_vMinBlockPos = pColObj->GetPos();
				}
				else if (DistX > 0.f && m_fPlusMin > DistX)
				{
					m_fPlusMin = DistX;
					m_vMaxBlockPos = pColObj->GetPos();
				}
			}

			if (!m_bHasLaser)
			{
				CLaser* pLaser = new CLaser;
				m_pLaser = pLaser;
				CSceneMgr::GetInst()->GetCurScene()->AddObject(m_pLaser, LAYER_TYPE::LASER);
				m_bHasLaser = true;
			}
		}
	}


}

void CLaserBody::CollisionEndOverlap(CCollider* _pOtherCollider)
{
}


