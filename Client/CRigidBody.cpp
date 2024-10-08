#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CObject.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(1.f)
	, m_fFriction(1000.f)
	, m_fMaxSpeed(500.f)
	, m_fMaxGravitySpeed(200.f)
	, m_bUseGravity(true)
	, m_bGround(false)	
	, m_eColDir(COLLISION_DIRECTION::NONE)
	, m_fElasticity(0.7f)
	, m_vForce(Vec2(0.f,0.f))
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::tick()
{
	float DeltaTime = GetOwner()->GetDT();

	// F = M x A
	if (m_eColDir == COLLISION_DIRECTION::NONE)
	{
		m_vAccel = m_vForce / m_fMass;

		// 속도에 가속도를 더한다.
		m_vVelocity += m_vAccel * DeltaTime;
	}
	else
	{
		m_vVelocity *= m_fElasticity;

		if (m_eColDir == COLLISION_DIRECTION::HORIZONTAL)
		{
			m_vVelocity.x = -m_vVelocity.x;
			m_eColDir = COLLISION_DIRECTION::NONE;
		}
		else if (m_eColDir == COLLISION_DIRECTION::VERTICAL)
		{
			m_vVelocity.y = -m_vVelocity.y;
			m_eColDir = COLLISION_DIRECTION::NONE;
		}
		else if (m_eColDir == COLLISION_DIRECTION::HORIZONTAL_VERTICAL)
		{
			m_vVelocity.y = -m_vVelocity.y;
			m_vVelocity.x = -m_vVelocity.x;
			m_eColDir = COLLISION_DIRECTION::NONE;
		}
	}

	if (m_bUseGravity)
	{
		// 중력 가속도 적용
		if (!m_bGround)
		{
			m_vVelocity += m_vGravityAccel * DeltaTime;
		}
		else
		{
			/*Vec2 vGravity = m_vGravityAccel;
			vGravity.Normalize();
			m_vVelocity -= vGravity * m_vVelocity.Dot(vGravity);*/
			m_vVelocity.y = 0.f;
		}

		// 속도 제한 조건
		Vec2 vGravity = m_vGravityAccel;

		// 중력이 없으면 넘어간다.
		if (!m_vGravityAccel.IsZero())
		{
			vGravity.Normalize();
			vGravity = vGravity * m_vVelocity.Dot(vGravity); // 속도를 중력방향으로 분해
		}

		Vec2 vSideVelocity = m_vVelocity - vGravity; // Velocity.x


		if (m_fMaxGravitySpeed < vGravity.Length())
		{
			vGravity.Normalize();
			vGravity *= m_fMaxGravitySpeed;
		}

		if (m_fMaxSpeed < vSideVelocity.Length())
		{
			vSideVelocity.Normalize();
			vSideVelocity *= m_fMaxSpeed;
		}

		m_vVelocity = vGravity + vSideVelocity;
	}
	
	// 마찰력 조건(적용된 힘이 없고, 속도가 0 이 아니고, 땅 위에 있을 때)
	if (!m_vVelocity.IsZero()) // 공중에서도 마찰력 받도록 변경
	{
		// 속도의 반대방향으로 마찰력을 적용
		Vec2 vFriction = -m_vVelocity;
		vFriction = vFriction.Normalize() * m_fFriction * DeltaTime * m_fMass;

		// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
		if (m_vVelocity.Length() < vFriction.Length())
		{
			// 속도를 0 로 만든다.
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
			if (m_bGround)
				m_vVelocity += vFriction;
			else
				m_vVelocity += vFriction / 3.f;
		}		
	}

	// 속도에 맞게 물체를 이동시킨다.
	Vec2 vPos = GetOwner()->GetPos() + m_vVelocity * DeltaTime;
	GetOwner()->SetPos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}