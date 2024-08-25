#include "pch.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"

#include "CScene_Tool.h"
#include "CScene_Logo.h"
#include "CScene_Start.h"
#include "CStage_01.h"
#include "CStage_02.h"
#include "CStage_03.h"
#include "CStage_04.h"
#include "CSTAGE_05.h"
#include "CSTAGE_06.h"
#include "CSTAGE_07.h"
#include "CSTAGE_08.h"
#include "CSTAGE_09.h"
#include "CSTAGE_10.h"
#include "CEnding.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
	, m_bRender(false)
{
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	m_arrScene[TOOL] = new CScene_Tool(TOOL);
	m_arrScene[LOGO] = new CScene_Logo(LOGO);
	m_arrScene[START] = new CScene_Start(START);
	m_arrScene[STAGE_01] = new CStage_01(STAGE_01);
	m_arrScene[STAGE_02] = new CStage_02(STAGE_02);
	m_arrScene[STAGE_03] = new CStage_03(STAGE_03);
	m_arrScene[STAGE_04] = new CSTAGE_04(STAGE_04);
	m_arrScene[STAGE_05] = new CSTAGE_05(STAGE_05);
	m_arrScene[STAGE_06] = new CSTAGE_06(STAGE_06);
	m_arrScene[STAGE_07] = new CSTAGE_07(STAGE_07);
	m_arrScene[STAGE_08] = new CSTAGE_08(STAGE_08);
	m_arrScene[STAGE_09] = new CSTAGE_09(STAGE_09);
	m_arrScene[STAGE_10] = new CSTAGE_10(STAGE_10);
	m_arrScene[ENDING] = new CEnding(ENDING);

	ChangeScene(SCENE_TYPE::LOGO);
}

void CSceneMgr::tick()
{
	m_pCurScene->tick();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	CCamera::GetInst()->CamEffectClear();
	EnterEffect();
	gChangeSceneFrame = true;

	if (nullptr != m_pCurScene)
	{
		m_pCurScene->exit();
	}

	m_pCurScene = m_arrScene[_eNext];


	m_pCurScene->enter();
	m_pCurScene->ResetOneFrameAfter();
}

void CSceneMgr::EnterEffect()
{
	CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
}
