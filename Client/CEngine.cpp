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

	// �� ������û
	for (UINT i = 0; i < (UINT)PEN_COLOR::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}	

	// �޴� ����	
	DestroyMenu(m_hMenu);
}


void CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	// ������������
	gChangeSceneFrame = false;
	gChecker = 0;

	// �õ尪 �ο�
	srand((unsigned int)time(NULL));

	m_hMainWnd = _hWnd;

	m_hDC = GetDC(m_hMainWnd);

	// ������ �ػ� ����
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
	RECT rt = {0, 0, (LONG)_iWidth , (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// ������ ũ�� ���� �� Show ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);

	// �⺻ �� �� �귯�� ����
	CreateDefaultGDIObject();

	// �޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));

	// ���� ���۸�
	// ������ �ػ󵵿� ������ ũ���� ��Ʈ���� ����
	m_pBackBuffer = CResMgr::GetInst()->CreateImg(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);


	// Manager �ʱ�ȭ
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

// ������ ���� ����
// 1. �ܻ� -> ȭ�� Ŭ����
// 2. ȭ�� Ŭ���� �� �÷��̾ �� �Ⱥ���
// 3. ȭ�� ���ŷ��� ���� �̹����� ���� Ÿ�ֿ̹� ������ ����
// 4. ���۸� 2�� �� ����ؼ� �ذ�

void CEngine::tick()
{	
	
	// ======
	// Update
	// ======
	// �Ŵ��� ������Ʈ
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CDebugMgr::GetInst()->tick();
	CCamera::GetInst()->tick();

	// Scene ������Ʈ
	CSceneMgr::GetInst()->tick(); 

	// UI �̺�Ʈ �˻�
	CUIMgr::GetInst()->tick();

	// �浹 �˻�
	CCollisionMgr::GetInst()->tick();
	CSoundMgr::GetInst()->tick();


	// ======
	// ������
	// ======

	

	// ���� Ŭ���� 
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
	// ���� �� ������ �� ����
	m_arrPen[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_COLOR::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_arrPen[(UINT)PEN_COLOR::BROWN] = CreatePen(PS_SOLID, 1, RGB(55, 38, 30));

	// ���� �� Brush ����
	m_arrBrush[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
}






void CEngine::AttachMenu()
{
	SetMenu(m_hMainWnd, m_hMenu);

	// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
	RECT rt = { 0, 0, m_ptResolution.x , m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	// ������ ũ�� ���� �� Show ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);
}

void CEngine::DetachMenu()
{
	SetMenu(m_hMainWnd, 0);

	// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
	RECT rt = { 0, 0, m_ptResolution.x , m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// ������ ũ�� ���� �� Show ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);
}