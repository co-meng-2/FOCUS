#include "pch.h"
#include "func.h"

#include "CObject.h"
#include "CImage.h"
#include "CResMgr.h"



void DeleteObject(CObject* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::DELETE_OBJECT;
	info.first = (DWORD_PTR)_pObj;
	CEventMgr::GetInst()->AddEvent(info);
}

void SceneChange(SCENE_TYPE _eNextScene)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::SCENE_CHANGE;
	info.first = (DWORD_PTR)_eNextScene;
	CEventMgr::GetInst()->AddEvent(info);
}
	
void SaveWString(const wstring& _str, FILE* _pFile)
{
	size_t iLen = _str.length();
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(_str.c_str(), sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	wchar_t szBuff[256] = {};

	fread(&iLen, sizeof(size_t), 1, _pFile);
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}

void SaveImageRef(CImage* _pImage, FILE* _pFile)
{
	int iCheck = 1;
	if (nullptr == _pImage)
	{
		iCheck = 0;
		fwrite(&iCheck, sizeof(int), 1, _pFile);
	}
	else
	{
		fwrite(&iCheck, sizeof(int), 1, _pFile);

		const wstring& strKey = _pImage->GetKey();
		const wstring& strPath = _pImage->GetRelativePath();

		SaveWString(strKey, _pFile);
		SaveWString(strPath, _pFile);
	}
}

void LoadImageRef(CImage** _ppImage, FILE* _pFile)
{
	int iCheck = 0;		
	fread(&iCheck, sizeof(int), 1, _pFile);

	if (0 == iCheck)
		return;

	wstring strKey;
	wstring strRelativePath;

	LoadWString(strKey, _pFile);
	LoadWString(strRelativePath, _pFile);

	*_ppImage = CResMgr::GetInst()->LoadImg(strKey, strRelativePath);
}

Vec2 RotateVector(Vec2 _vOrigin, float _Degree)
{
	float fRadian = (_Degree / 180.f) * PI;

	_vOrigin.Normalize();
	
	return Vec2(cosf(fRadian) * _vOrigin.x - sinf(fRadian) * _vOrigin.y
		      , sinf(fRadian) * _vOrigin.x + cosf(fRadian) * _vOrigin.y);
}

float CrossVector(Vec2 _v1, Vec2 _v2)
{
	return _v1.x * _v2.y - _v1.y * _v2.x;
}

int IsCCW(Vec2 _v1, Vec2 _v2, Vec2 _v3)
{
	Vec2 line1 = _v2 - _v1;
	Vec2 line2 = _v3 - _v1;

	float output = CrossVector(line1, line2);
	// 1 -> CW / -1 -> CCW / 0 -> Dot is on the line
	if(output > 0.f) return -1;
	else if(output == 0.f) return 0;
	else return 1;
}