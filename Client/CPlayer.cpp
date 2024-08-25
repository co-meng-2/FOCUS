#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"
#include "CEventMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CPosChanger.h"
#include "CEffect.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

CPlayer::CPlayer()
	: m_fSpeed(300.f)
	, m_fFocusAccTime(100.f)
	, m_fFocusCoolTime(2.f)
	, m_fAddForceMaxTime(0.12f)
	, m_fAddForceAccTime(0.f)
	, m_bStartAddForce(false)
	, m_bDead(false)
	, m_bInvincibility(false)
	, m_fMaxFocusRadius(200.f)
	, m_fCurFocusRadius(200.f)
	, m_fRadiusDeclineSpeed(20.f)
	, m_fRadiusInclineSpeed(50.f)
	, m_bFocus(false)
	, m_fRadiusReduce(0.5f)
	, m_vPrevPos(Vec2(0.f, 0.f))
	, m_vMovedPos(Vec2(0.f, 0.f))
	, m_bHasFocus(true)
	, m_pPosChanger(nullptr)
	, m_pEffect(nullptr)
	, m_bDeadAnimPlayed(false)
	, m_bJump(false)
	, m_eMoveDir(MOVE_DIRECTION::R)
{	
	AddComponent(new CCollider);
	AddComponent(new CAnimator);
	AddComponent(new CRigidBody);

	m_pPosChanger = new CPosChanger;
	m_pPosChanger->SetPlayer(this);
	AddObject_D((CObject*)m_pPosChanger, LAYER_TYPE::PLAYER_OPTION);

	CEffect* m_pEffect = new CEffect;
	m_pEffect->SetObject(this);
	AddObject_D((CObject*)m_pEffect, LAYER_TYPE::EFFECT);
	

	GetCollider()->SetScale(PLAYER_SIZE);
	GetCollider()->SetOffset(Vec2(0.f, 2.f));

	/*CImage* pPlayerAtlas = CResMgr::GetInst()->
	(L"PlayerAtlas", L"image\\link.bmp");
	GetAnimator()->CreateAnimation(L"Walk_Up", pPlayerAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f),		Vec2(0.f,-30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Down", pPlayerAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f),	Vec2(0.f,-30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Left", pPlayerAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f),	Vec2(0.f,-30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Right", pPlayerAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f),	Vec2(0.f,-30.f), 120.f, 10, 0.1f);*/
	CImage* pPlayerAtlas = CResMgr::GetInst()->FindImg(L"PlayerAtlas");
	GetAnimator()->CreateAnimation(L"PlayerWalkRight", pPlayerAtlas, Vec2(0.f, 32.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 32.f, 5, 0.1f);
	GetAnimator()->CreateAnimation(L"PlayerWalkLeft", pPlayerAtlas, Vec2(0.f, 96.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 32.f, 5, 0.1f);
	GetAnimator()->CreateAnimation(L"PlayerJumpR", pPlayerAtlas, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 32.f, 5, 0.1f);
	GetAnimator()->CreateAnimation(L"PlayerJumpL", pPlayerAtlas, Vec2(0.f, 192.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 32.f, 5, 0.1f);
	GetAnimator()->CreateAnimation(L"PlayerDead", pPlayerAtlas, Vec2(0.f, 64.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 32.f, 8, 0.1f);

	//CImage* pPlayerAtlas_Chik_Left = CResMgr::GetInst()->LoadImg(L"ChikAtlasLeft", L"image\\ChikBoy\\Chik_Walk_Left_320_50_10.bmp");
	//GetAnimator()->CreateAnimation(L"Chik_Walk_Left", pPlayerAtlas_Chik_Left, Vec2(0.f, 0.f), Vec2(32.f, 46.f), Vec2(0.f, 3.f), 32.f, 10, 0.1f);

	//CImage* pPlayerAtlas_Chik_Right = CResMgr::GetInst()->LoadImg(L"ChikAtlasRight", L"image\\ChikBoy\\Chik_Walk_Right_320_50_10.bmp");
	//GetAnimator()->CreateAnimation(L"Chik_Walk_Right", pPlayerAtlas_Chik_Right, Vec2(0.f, 0.f), Vec2(32.f, 46.f), Vec2(0.f, 3.f), 32.f, 10, 0.1f);

	//GetAnimator()->Play(L"Walk_Down", true);
	GetAnimator()->Play(L"PlayerWalkRight", true);
	//GetAnimator()->Play(L"PlayerWalkRight", true);

	GetRigidBody()->SetMaxSpeed(250.f);
	GetRigidBody()->SetMaxGravitySpeed(1200.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 2000.f));		

	m_pDyingSound = CResMgr::GetInst()->FindSound(L"PlayerDying");
	m_pFocusSound = CResMgr::GetInst()->FindSound(L"Focus");
	m_pFocusSound->SetVolume(100.f);
}

CPlayer::~CPlayer()
{	
}

void CPlayer::FocusPressed()
{
	GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	GetRigidBody()->SetGravity(false);

	vector<CObject*> vecObjArr[5] ;
	vecObjArr[0] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::SPAWNER);
	vecObjArr[1] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PROJECTILES);
	vecObjArr[2] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::EXPLOSION);
	vecObjArr[3] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::FRAGMENT);
	vecObjArr[4] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::LASERBODY);
	
	for (UINT i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < vecObjArr[i].size(); ++j)
		{
			if (!vecObjArr[i].empty() && vecObjArr[i][j] != nullptr)
			{
				Vec2 vObjColPos = vecObjArr[i][j]->GetPos();
				Vec2 vPlayerPos = GetPos();

 				if (vPlayerPos.Distance(vObjColPos) < m_fCurFocusRadius)
				{
					vecObjArr[i][j]->InFocus();
				}
				else
				{
					vecObjArr[i][j]->OutFocus();
				}
			}
		}
	} // end of 2-for

	if (IsPressed(KEY_TYPE::LEFT))
	{
		m_pPosChanger->SubOffsetX();
	}

	if (IsPressed(KEY_TYPE::RIGHT))
	{
		m_pPosChanger->AddOffsetX();
	}

	if (IsPressed(KEY_TYPE::UP))
	{
		m_pPosChanger->SubOffsetY();
	}

	if (IsPressed(KEY_TYPE::DOWN))
	{
		m_pPosChanger->AddOffsetY();
	}

	m_fCurFocusRadius -= m_fRadiusDeclineSpeed * DT;
}


void CPlayer::FocusReleased()
{
	GetRigidBody()->SetGravity(true);

	vector<CObject*> vecObjArr[5];
	vecObjArr[0] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::SPAWNER);
	vecObjArr[1] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PROJECTILES);
	vecObjArr[2] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::EXPLOSION);
	vecObjArr[3] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::FRAGMENT);
	vecObjArr[4] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::LASERBODY);

	for (UINT i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < vecObjArr[i].size(); ++j)
		{
			if (!vecObjArr[i].empty() && vecObjArr[i][j] != nullptr)
			{
				Vec2 vObjColPos = vecObjArr[i][j]->GetPos();
				Vec2 vPlayerPos = GetPos();

				vecObjArr[i][j]->OutFocus();
			}
		}
	}

	if (GetPos().Distance(m_pPosChanger->GetSwitchPos()) >= 50.f)
	{
		if(m_pPosChanger->GetSwitchPos().y - GetPos().y >= 0)
			SetPos(Vec2(m_pPosChanger->GetSwitchPos().x, m_pPosChanger->GetSwitchPos().y - 10.f));
		else if (m_pPosChanger->GetSwitchPos().y - GetPos().y < 0)
			SetPos(Vec2(m_pPosChanger->GetSwitchPos().x, m_pPosChanger->GetSwitchPos().y + 10.f));
		/*GetRigidBody()->AddForce(Vec2(m_pPosChanger->GetOffSet().x * 200, m_pPosChanger->GetOffSet().y * 200));*/
		StartAddForce();
		m_fCurFocusRadius *= m_fRadiusReduce; // 위치 변경 했다면 범위 줄임
	}
	m_pPosChanger->ResetOffset();

	m_bFocus = false;
	//if (m_pEffect != nullptr && IsValid(m_pEffect))
	//{
	//	DeleteObject(m_pEffect);
	//	m_pEffect = nullptr;
	//}
	m_pFocusSound->Stop();
}

void CPlayer::FocusCanceled()
{
	GetRigidBody()->SetGravity(true);

	vector<CObject*> vecObjArr[5];
	vecObjArr[0] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::SPAWNER);
	vecObjArr[1] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PROJECTILES);
	vecObjArr[2] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::EXPLOSION);
	vecObjArr[3] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::FRAGMENT);
	vecObjArr[4] = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::LASERBODY);

	for (UINT i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < vecObjArr[i].size(); ++j)
		{
			if (!vecObjArr[i].empty() && vecObjArr[i][j] != nullptr)
			{
				Vec2 vObjColPos = vecObjArr[i][j]->GetPos();
				Vec2 vPlayerPos = GetPos();

				vecObjArr[i][j]->OutFocus();
			}
		}
	}
	 
	// SetPos((m_pPosChanger->GetSwitchPos()));
	m_pPosChanger->ResetOffset();;

	m_bFocus = false;
	//if (m_pEffect != nullptr && IsValid(m_pEffect))
	//{
	//	DeleteObject(m_pEffect);
	//	m_pEffect = nullptr;
	//}
	m_pFocusSound->Stop();
}

void CPlayer::StartAddForce()
{
	m_bStartAddForce = true;
	m_fAddForceAccTime = 0.f;
	m_vForceDir = m_pPosChanger->GetOffSet();
}

void CPlayer::EndAddForce()
{
	m_bStartAddForce = false;
	m_vForceDir = Vec2(0.f, 0.f);
}

void CPlayer::tick()
{
	SelectDeltaTime();

	if (!m_bDead)
	{
		if (!m_bFocus)
		{
			m_fFocusAccTime += DT;
			m_fAddForceAccTime += DT;


			if (IsPressed(KEY_TYPE::LEFT))
			{
				GetRigidBody()->AddForce(Vec2(-4000.f, 0.f));
				// SetPos(Vec2(GetPos().x - m_fSpeed * DT, GetPos().y));
			}

			if (IsPressed(KEY_TYPE::RIGHT))
			{
				GetRigidBody()->AddForce(Vec2( 4000.f, 0.f));
				// SetPos(Vec2(GetPos().x + m_fSpeed * DT, GetPos().y));
			}

			if (GetRigidBody()->IsGround())
			{
				if (GetPos().x - m_vPrevPosForAnim.x < 0 && m_eMoveDir != MOVE_DIRECTION::L)
				{
					GetAnimator()->Play(L"PlayerWalkLeft", true);
					m_eMoveDir = MOVE_DIRECTION::L;
				}

				if (GetPos().x - m_vPrevPosForAnim.x > 0 && m_eMoveDir != MOVE_DIRECTION::R)
				{
					GetAnimator()->Play(L"PlayerWalkRight", true);
					m_eMoveDir = MOVE_DIRECTION::R;
				}
			}
			else
			{
				if (GetPos().x - m_vPrevPosForAnim.x < 0 && m_eMoveDir != MOVE_DIRECTION::JL)
				{
					GetAnimator()->Play(L"PlayerJumpL", true);
					m_eMoveDir = MOVE_DIRECTION::JL;
				}

				if (GetPos().x - m_vPrevPosForAnim.x > 0 && m_eMoveDir != MOVE_DIRECTION::JR)
				{
					GetAnimator()->Play(L"PlayerJumpR", true);
					m_eMoveDir = MOVE_DIRECTION::JR;
				}
			}


			if (GetRigidBody()->IsGround())
			{
				if (IsTap(KEY_TYPE::SPACE))
				{
					
					Vec2 vV = GetRigidBody()->GetVelocity();
					vV.y = -800.f;
					GetRigidBody()->SetVelocity(vV);
					GetRigidBody()->SetGround(false);
				}
			}

			if (IsTap(KEY_TYPE::F) && m_bHasFocus && !m_bFocus)
			{
				m_bFocus = true;

				m_pFocusSound->Play();
			}

			// 포커스 사용 안 할때 포커스 범위 증가
			m_fCurFocusRadius += m_fRadiusInclineSpeed * DT;
			if (m_fCurFocusRadius >= m_fMaxFocusRadius)
				m_fCurFocusRadius = m_fMaxFocusRadius;
			
			// AddForce 진행
			if (m_bStartAddForce && m_fAddForceMaxTime >= m_fAddForceAccTime)
				GetRigidBody()->AddForce(m_vForceDir * 20.f);
			else
				EndAddForce();
		}
		else if (m_bFocus && m_fCurFocusRadius > 50.f && m_fFocusAccTime >= m_fFocusCoolTime)
		{
			if (IsPressed(KEY_TYPE::F))
				FocusPressed();
			if (IsRelease(KEY_TYPE::F))
				if (m_pPosChanger->IsOntheBlock())
					FocusCanceled();
				else
					FocusReleased();
		}
		else
		{
			FocusCanceled();
			if (m_fFocusAccTime >= m_fFocusCoolTime)
				m_fFocusAccTime = 0.f;
		}

	}
	else if(m_bDead)
	{
		if (!m_bDeadAnimPlayed)
		{
			GetAnimator()->Play(L"PlayerDead", false);
			m_bDeadAnimPlayed = true;
			m_pDyingSound->SetVolume(100.f);
			m_pDyingSound->Play();
		}

		if (m_bFocus)
			FocusCanceled();


	}
	//SetPos(vPos);

	if (IsTap(KEY_TYPE::O))
	{
		if(!m_bInvincibility)
			m_bInvincibility = true;
		else
			m_bInvincibility = false;
	}


	m_vPrevPosForAnim = GetPos();

	CObject::tick();

	if (GetPos().x < 0 || GetPos().y < 0 || GetPos().x > 1028 || GetPos().y > 768)
	{
		m_bDead = true;
	}

	m_vMovedPos = GetPos() - m_vPrevPos;
	m_vPrevPos = GetPos();
}

void CPlayer::render(HDC _dc)
{

	CObject::render(_dc);
}