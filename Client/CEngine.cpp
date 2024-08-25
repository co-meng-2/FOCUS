#include "pch.h"
#include "CEngine.h"


#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CEventMgr.h"
#include "CDebugMgr.h"

#include "resource.h"
#include "CImage.h"
#include "CSound.h"


CEngine::CEngine()
	: m_hMainWnd(0)
	, m_hDC(0)
	, m_ptResolution{}
	, m_pBackBuffer(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
	, m_hMenu(0)
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	// 펜 삭제요청
	for (UINT i = 0; i < (UINT)PEN_COLOR::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}	

	// 메뉴 삭제	
	DestroyMenu(m_hMenu);
}


void CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	// 전역변수선언
	gChangeSceneFrame = false;
	gChecker = 0;

	// 시드값 부여
	srand((unsigned int)time(NULL));

	m_hMainWnd = _hWnd;

	m_hDC = GetDC(m_hMainWnd);

	// 윈도우 해상도 설정
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
	RECT rt = {0, 0, (LONG)_iWidth , (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);

	// 기본 펜 및 브러쉬 생성
	CreateDefaultGDIObject();

	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));

	// 이중 버퍼링
	// 윈도우 해상도와 동일한 크기의 비트맵을 생성
	m_pBackBuffer = CResMgr::GetInst()->CreateImg(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);


	// Manager 초기화
	CPathMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CResMgr::GetInst()->init();

	CSceneMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();	
	CDebugMgr::GetInst()->init();

	// CResMgr::GetInst()->init();
	// CSoundMgr::GetInst()->init();
	
	
	CCamera::GetInst()->init();

	// Sound Test
	CSound* pBGM = CResMgr::GetInst()->FindSound(L"BGM_01");
	if (nullptr != pBGM)
	{
		pBGM->Play(true);		
		pBGM->PlayToBGM();
	}	
}

// 렌더링 관련 문제
// 1. 잔상 -> 화면 클리어
// 2. 화면 클리어 시 플레이어가 잘 안보임
// 3. 화면 갱신률과 버퍼 이미지의 전송 타이밍에 문제가 있음
// 4. 버퍼를 2개 를 사용해서 해결

void CEngine::tick()
{	
	
	// ======
	// Update
	// ======
	// 매니저 업데이트
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CDebugMgr::GetInst()->tick();
	CCamera::GetInst()->tick();

	// Scene 업데이트
	CSceneMgr::GetInst()->tick(); 

	// UI 이벤트 검사
	CUIMgr::GetInst()->tick();

	// 충돌 검사
	CCollisionMgr::GetInst()->tick();
	CSoundMgr::GetInst()->tick();


	// ======
	// 렌더링
	// ======

	

	// 버퍼 클리어 
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_pBackBuffer->GetDC(), m_arrBrush[(UINT)BRUSH_COLOR::GRAY]);
	Rectangle(m_pBackBuffer->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectObject(m_pBackBuffer->GetDC(), hPrevBrush);

	// Scene Rendering
	CSceneMgr::GetInst()->render(m_pBackBuffer->GetDC());
	CTimeMgr::GetInst()->render(m_pBackBuffer->GetDC());
	CCamera::GetInst()->render(m_pBackBuffer->GetDC());

	// BackBuffer -> MainBuffer
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pBackBuffer->GetDC(), 0, 0, SRCCOPY);


	// EventMgr
	CEventMgr::GetInst()->tick();
}

void CEngine::CreateDefaultGDIObject()
{
	// 자주 쓸 색상의 펜 생성
	m_arrPen[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_COLOR::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_arrPen[(UINT)PEN_COLOR::BROWN] = CreatePen(PS_SOLID, 1, RGB(55, 38, 30));

	// 자주 쓸 Brush 생성
	m_arrBrush[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
}






void CEngine::AttachMenu()
{
	SetMenu(m_hMainWnd, m_hMenu);

	// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
	RECT rt = { 0, 0, m_ptResolution.x , m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);
}

void CEngine::DetachMenu()
{
	SetMenu(m_hMainWnd, 0);

	// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
	RECT rt = { 0, 0, m_ptResolution.x , m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);
}