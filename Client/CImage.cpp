#include "pch.h"
#include "CImage.h"

#include "CEngine.h"

CImage::CImage()
	: m_hBit(0)
	, m_hDC(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_bScaleChange(false)
	, m_bTransParent(false)
{
}

CImage::~CImage()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

int CImage::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImageW(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (nullptr == m_hBit)
	{

		return E_FAIL;
	}
		
	// 비트맵 정보 확인
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;


	int iErr = GetLastError();

	HDC hMainDC = CEngine::GetInst()->GetMainDC();
	m_hDC = CreateCompatibleDC(hMainDC);

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	return S_OK;
}

int CImage::Create(UINT _iWidth, UINT _iHeight)
{
	// 새로 생성한 비트맵을 가리키는 전용 DC 생성
	// 새로 생성한 비트맵과 DC 를 서로 연결
	HDC hMainDC = CEngine::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(hMainDC, _iWidth, _iHeight);
	m_hDC = CreateCompatibleDC(hMainDC);

	if (0 == m_hBit || 0 == m_hDC)
		return E_FAIL;

	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hDefaultBitmap);

	// 비트맵 정보 확인
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;

	return S_OK;
}
