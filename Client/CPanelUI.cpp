#include "pch.h"
#include "CPanelUI.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CScene_Tool.h"

CPanelUI::CPanelUI()
	: m_eMode(TOOL_MODE::TILE)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::tick()
{
	if (IsLBtnDown())
	{
		// 캡쳐 포지션과 현재 마우스 포지션의 차이값을 구함
		Vec2 vCurMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vMouseDiff = vCurMousePos - m_vCapturePos;
		m_vCapturePos = vCurMousePos; // 현재 마우스 위치를 캡처포즈로 갱신

		// 차이값 만큼 UI 포지션에 반영
		Vec2 vUIPos = GetPos();
		vUIPos += vMouseDiff;
		SetPos(vUIPos);
	}

	// 최종 위치 구함
	CUI::tick();
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	tSelectPen pen(_dc, PEN_COLOR::GREEN);
	tSelectBrush Brush(_dc, BRUSH_COLOR::BLACK);

	Vec2 vFinalPos = GetFinalPos();

	Rectangle(_dc
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));

	UINT iColType = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene())->GetColType();
	Vec2 iColScale = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene())->GetColScale();

	wchar_t szFloat[50] = {};
	if ((UINT)COLLIDER_TYPE::BLOCK == iColType)
		swprintf_s(szFloat, 50, L"BLOCK : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if ((UINT)COLLIDER_TYPE::EXIT_BLOCK == iColType)
		swprintf_s(szFloat, 50, L"EXIT_BLOCK : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if ((UINT)COLLIDER_TYPE::SPAWN == iColType)
		swprintf_s(szFloat, 50, L"SPAWN : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if ((UINT)COLLIDER_TYPE::THORN == iColType)
		swprintf_s(szFloat, 50, L"THORN : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if((UINT)COLLIDER_TYPE::WALL == iColType)
		swprintf_s(szFloat, 50, L"WALL : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if ((UINT)COLLIDER_TYPE::BUTTON_IN == iColType)
		swprintf_s(szFloat, 50, L"BUTTON_IN : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if ((UINT)COLLIDER_TYPE::BUTTON_OUT == iColType)
		swprintf_s(szFloat, 50, L"BUTTON_OUT : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);
	else if ((UINT)COLLIDER_TYPE::SCENE_CHANGE == iColType)
		swprintf_s(szFloat, 50, L"SCENE_CHANGE : %d, %d", (int)iColScale.x / TILE_SIZE, (int)iColScale.y / TILE_SIZE);

	int iLen = (int)wcsnlen_s(szFloat, 50);
	TextOut(_dc, (int)(vFinalPos.x), (int)(vFinalPos.y), szFloat, iLen);

	switch (m_eMode)
	{
	case TOOL_MODE::TILE:
		swprintf_s(szFloat, 50, L"TILE");
		break;
	case TOOL_MODE::TILE_SELECT:
		swprintf_s(szFloat, 50, L"TILE_SELECT");
		break;
	case TOOL_MODE::OBJECT:
		swprintf_s(szFloat, 50, L"OBJECT");
		break;
	}

	iLen = (int)wcsnlen_s(szFloat, 50);
	TextOut(_dc, (int)(vFinalPos.x) + vScale.x / 2.f, (int)(vFinalPos.y), szFloat, iLen);

	swprintf_s(szFloat, 50, L"x : %d, y : %d", (int)CKeyMgr::GetInst()->GetMousePos().x, (int)CKeyMgr::GetInst()->GetMousePos().y);
	iLen = (int)wcsnlen_s(szFloat, 50);
	TextOut(_dc, (int)(vFinalPos.x), (int)(vFinalPos.y) + 20.f, szFloat, iLen);

	CUI::render(_dc);
}

void CPanelUI::LBtnDown()
{	
	CUI::LBtnDown();

	m_vCapturePos = CKeyMgr::GetInst()->GetMousePos();
}

void CPanelUI::LBtnClicked()
{
}