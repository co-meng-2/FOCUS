#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CImage.h"
#include "CSound.h"


CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Del_Map(m_mapImage);
	Safe_Del_Map(m_mapSound);
}

void CResMgr::init()
{
	// Image 로딩	
	LoadImg(L"ButtonInImage", L"image\\Button\\ButtonIn_16_16.bmp");
	LoadImg(L"ButtonInPressedImage", L"image\\Button\\ButtonInPressed_16_16.bmp");
	LoadImg(L"ButtonOutImage", L"image\\Button\\ButtonOut_12_6.bmp");
	LoadImg(L"ButtonOutPressedImage", L"image\\Button\\ButtonOutPressed_12_2.bmp");
	LoadImg(L"MineImage", L"image\\Mine\\Mine_20_20.bmp");
	LoadImg(L"MineSpawnerAtlas", L"image\\Mine\\MineSpawner_840_120_7.bmp");
	LoadImg(L"CrystalImage", L"image\\Crystal\\Orb_R_32_32.bmp");
	LoadImg(L"EnforcerImage", L"image\\Crystal\\Enhancer_50_50.bmp");
	LoadImg(L"FocusEffectAtlas", L"image\\Effect\\FocusEffectAtlas.bmp");

	LoadImg(L"FocusBackgroundImage", L"image\\Effect\\FocusBackgroundClock_500_500.bmp");

	LoadImg(L"WhiteCircleImage", L"image\\Effect\\WhiteCircle_200_200.bmp");
	LoadImg(L"RedCircleImage", L"image\\Effect\\RedCircle_200_200.bmp");
	LoadImg(L"FocusGreenEffectAtlas", L"image\\Effect\\GreenEffectAtlas_1000_1000_100_100.bmp");
	LoadImg(L"LaserBodyImage", L"image\\Laser\\LaesrBody_24_24.bmp");
	LoadImg(L"FireEffectAtlas", L"image\\Effect\\FireEffect_80_16_5.bmp");
	LoadImg(L"MineExplosionAtlas", L"image\\Explosion\\ExplosionMine_1152_96_12.bmp");
	LoadImg(L"MissileExplosionAtlas", L"image\\Explosion\\ExplosionMissile_1664_128_13.bmp");
	LoadImg(L"ClockHourAtlas", L"image\\Logo\\Clock_Hour_3000_250_12.bmp");
	LoadImg(L"ClockMinuteAtlas", L"image\\Logo\\Clock_Minute_3000_250_12.bmp");
	LoadImg(L"LogoBackgroundImage", L"image\\Logo\\LOGO_Background_1028_768.bmp");
	LoadImg(L"LogoTextImage", L"image\\Logo\\LOGO_Text_1028_768.bmp");
	LoadImg(L"EndingTextImage", L"image\\Ending\\Ending_Text_1028_768.bmp");
	LoadImg(L"PlayerAtlas", L"image\\Player\\PlayerAtlas_224_224_7_7.bmp");
	LoadImg(L"BasicExplosionAtlas", L"image\\Explosion\\ExplosionBasic_150_25_6.bmp");

	// Sound 로딩
	LoadSound(L"BGM_01", L"sound\\BGM\\BGM.wav");
	LoadSound(L"PlayerDying", L"sound\\Player\\PlayerDying.wav");
	LoadSound(L"Explosion", L"sound\\Explosion\\Explosion.wav");
	LoadSound(L"MissileSpawn", L"sound\\Explosion\\MissileSpawn.wav");
	LoadSound(L"Focus", L"sound\\Player\\Focus.wav");
	LoadSound(L"ButtonPress", L"sound\\Button\\ButtonPress.wav");
	LoadSound(L"Earthquake", L"sound\\SceneChange\\Earthquake.wav");
	LoadSound(L"Crystal", L"sound\\Crystal\\Crystal.wav");
	LoadSound(L"SpawnMine", L"sound\\Mine\\SpawnMine.wav");
	
}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// 해당키로 이미 로딩된게 있으면 해당 리소스를 반환
		return pImage;
	}

	// 해당 키로 로딩된 이미지가 없다.
	
	// content 폴더 경로 + 상대경로 = 최종 경로
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"이미지 로딩 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::CreateImg(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		MessageBox(nullptr, L"중복 키 발생", L"이미지 생성 실패", MB_OK);
		return nullptr;
	}

	// 해당 키로 생성된 이미지가 없다.
	pImage = new CImage;
	if (FAILED(pImage->Create(_iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"이미지 생성 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);	
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
	if (iter != m_mapImage.end())
	{
		return iter->second;
	}

	return nullptr;
}


CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (nullptr != pSound)
		return pSound;

	pSound = new CSound;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}