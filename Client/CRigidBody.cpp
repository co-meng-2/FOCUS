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

		// �ӵ��� ���ӵ��� ���Ѵ�.
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
		// �߷� ���ӵ� ����
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

		// �ӵ� ���� ����
		Vec2 vGravity = m_vGravityAccel;

		// �߷��� ������ �Ѿ��.
		if (!m_vGravityAccel.IsZero())
		{
			vGravity.Normalize();
			vGravity = vGravity * m_vVelocity.Dot(vGravity); // �ӵ��� �߷¹������� ����
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
	
	// ������ ����(����� ���� ����, �ӵ��� 0 �� �ƴϰ�, �� ���� ���� ��)
	if (!m_vVelocity.IsZero()) // ���߿����� ������ �޵��� ����
	{
		// �ӵ��� �ݴ�������� �������� ����
		Vec2 vFriction = -m_vVelocity;
		vFriction = vFriction.Normalize() * m_fFriction * DeltaTime * m_fMass;

		// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
		if (m_vVelocity.Length() < vFriction.Length())
		{
			// �ӵ��� 0 �� �����.
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
			if (m_bGround)
				m_vVelocity += vFriction;
			else
				m_vVelocity += vFriction / 3.f;
		}		
	}

	// �ӵ��� �°� ��ü�� �̵���Ų��.
	Vec2 vPos = GetOwner()->GetPos() + m_vVelocity * DeltaTime;
	GetOwner()->SetPos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}