#include "pch.h"
#include "CScene.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CDebugMgr.h"
#include "CSceneMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CObject.h"
#include "CColliderObject.h"
#include "CTile.h"

#include "CCollider.h"



CScene::CScene(SCENE_TYPE _scenetype)
	: m_iTileCol(0)
	, m_iTileRow(0)
	, bOneFrameAFter(false)
	, m_eSceneType(_scenetype)
	, m_iButtonCount(0)
	, m_eNextScene(SCENE_TYPE::END)
	, m_iPrevButtonCount(0)
{
}

CScene::~CScene()
{
	DeleteAllObjectEX();
}

void CScene::CreateTile(UINT _iCol, UINT _iRow)
{
	DeleteObject(LAYER_TYPE::TILE);

	m_iTileCol = _iCol;
	m_iTileRow = _iRow;

	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2( (float)(iCol * TILE_SIZE), (float)(iRow * TILE_SIZE)));
			AddObject(pTile, LAYER_TYPE::TILE);
		}
	}
}

void CScene::SetFocusedUI(CObject* _pUI)
{
	// Focused 처리 하려는 UI 를 UI 레이어 벡터안에서 찾아서 지우고
	vector<CObject*>::iterator iter = m_arrLayer[(UINT)LAYER_TYPE::UI].begin();
	for (; iter != m_arrLayer[(UINT)LAYER_TYPE::UI].end(); ++iter)
	{
		if (*iter == _pUI)
		{
			m_arrLayer[(UINT)LAYER_TYPE::UI].erase(iter);
			break;
		}
	}	

	// 다시 맨 뒤로 넣는다.
	m_arrLayer[(UINT)LAYER_TYPE::UI].push_back(_pUI);
}

void CScene::tick()
{
	if (m_iPrevButtonCount >= 1 && m_iButtonCount == 0)
	{
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::SHAKE_HORIZONTAL, 1.f, 5, 1000);
		CSound* m_pEarthquakeSound = CResMgr::GetInst()->FindSound(L"Earthquake");
		m_pEarthquakeSound->SetPosition(40.f);
		m_pEarthquakeSound->Play();
	}

	if (IsDebugModeD)
	{
		if (IsTap(KEY_TYPE::B))
		{
			GetObjects(LAYER_TYPE::PLAYER).at(0)->SetPos(Vec2(500.f, 100.f));
		}

		if (IsTap(KEY_TYPE::N))
			MoveNextScene();

		if (IsTap(KEY_TYPE::T))
		{
			SceneChange(SCENE_TYPE::TOOL);
		}
	}



	if (!CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PLAYER).empty())
	{
		if (IsTap(KEY_TYPE::SPACE) && GetpPlayer->GetDead())
		{
			ReloadScene();
		}
	}

	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if(m_arrLayer[i][j] != nullptr && !m_arrLayer[i][j]->IsDead())
				m_arrLayer[i][j]->tick();
		}
	}

	m_iPrevButtonCount = m_iButtonCount;

	if (bOneFrameAFter)
	{
		gChangeSceneFrame = false;
	}

	bOneFrameAFter = true;
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if (i == (UINT)LAYER_TYPE::TILE)
			render_tile(_dc);
		else
		{
			vector<CObject*>::iterator iter = m_arrLayer[i].begin();
			for (; iter != m_arrLayer[i].end(); )
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}

void CScene::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObject((LAYER_TYPE)i);
	}
}

void CScene::DeleteObject(LAYER_TYPE _eType)
{	
	vector<CObject*>& vecObj = m_arrLayer[(UINT)_eType];

	for (UINT j = 0; j < vecObj.size(); ++j)
	{
		//if(!vecObj[j]->IsDead())
		//	SAFE_DELETE(vecObj[j]);

		::DeleteObject(vecObj[j]);
	}	

	vecObj.clear();
}

void CScene::DeleteAllObjectEX()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObjectEX((LAYER_TYPE)i);
	}
}

void CScene::DeleteObjectEX(LAYER_TYPE _eType)
{
	vector<CObject*>& vecObj = m_arrLayer[(UINT)_eType];

	for (UINT j = 0; j < vecObj.size(); ++j)
	{
		if(!vecObj[j]->IsDead())
		SAFE_DELETE(vecObj[j]);
	}

	vecObj.clear();
}

void CScene::TileLoadOption(CTile* _pTile)
{
	/*if (_pTile->GetImgIdx() == (int)TILE_TYPE::WALL)
	{
		_pTile->AddComponent(new CCollider);
		_pTile->GetCollider()->SetScale(Vec2(35.f, 35.f));
		_pTile->GetCollider()->SetOffset(Vec2(float(TILE_SIZE) / 2.f, float(TILE_SIZE) / 2.f));
	}	
	else if (_pTile->GetImgIdx() == (int)TILE_TYPE::BLOCK)
	{
		_pTile->AddComponent(new CCollider);
		_pTile->GetCollider()->SetScale(Vec2(35.f, 35.f));
		_pTile->GetCollider()->SetOffset(Vec2(float(TILE_SIZE) / 2.f, float(TILE_SIZE) / 2.f));
	}*/
}

void CScene::TileToBlock()
{
	//vector<CObject*>::iterator iter = m_arrLayer[(int)LAYER_TYPE::TILE].begin();
	//for (; iter != m_arrLayer[(int)LAYER_TYPE::TILE].end(); ++iter)
	//{
	//	if (dynamic_cast<CTile*>(*iter)->GetImgIdx() == (int)TILE_TYPE::BLOCK)
	//	{
	//		vector<CObject*>::iterator tmpIter = iter;
	//		
	//		AddObject(dynamic_cast<CTile*>(*iter)->Clone(), LAYER_TYPE::BLOCK);
	//		// iter = m_arrLayer[(int)LAYER_TYPE::TILE].erase(iter);
	//	}
	//		
	//	else
	//	{
	//		
	//	}
	//}
}

void CScene::LoadTile(wstring _path)
{
	FILE* pFile = nullptr;

	// 읽기 모드로 열기
	_wfopen_s(&pFile, _path.c_str(), L"rb");

	if (nullptr == pFile)
	{
		return;
	}

	// 타일 가로 세로 개수
	UINT iCol = 0;
	UINT iRow = 0;

	fread(&iCol, sizeof(UINT), 1, pFile);
	fread(&iRow, sizeof(UINT), 1, pFile);

	CreateTile(iCol, iRow);

	const vector<CObject*>& vecTile = GetObjects(LAYER_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		CTile* pTile = (CTile*)vecTile[i];
		pTile->Load(pFile);

		// Tile 이미지 index로 Collider생성 시도 확장성이 낮아서 막아둠.
		// TileLoadOption(pTile); 
	}

	// Tile 이미지 index로 Collider생성 시도 확장성이 낮아서 막아둠.
	// TileToBlock();
	fclose(pFile);
}

void CScene::LoadObject(wstring _path)
{
	// OBJ
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _path.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	// 타일 가로 세로 개수
	UINT iObjectCount = 0;

	fread(&iObjectCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < iObjectCount; ++i)
	{
		CColliderObject* pColObj = new CColliderObject;
		pColObj->Load(pFile);
		AddObject(pColObj, LAYER_TYPE::COLLIDEROBJ);
	}

	fclose(pFile);

	
	// pPlayer->SetPos(Vec2(500.f, 100.f));
	// spawn 타일로 위치설정
	vector<CObject*> vTile = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::COLLIDEROBJ);
	for (int i = 0; i < vTile.size(); ++i)
	{
		if (vTile[i] != nullptr && dynamic_cast<CColliderObject*>(vTile[i])->GetColType() == (UINT)COLLIDER_TYPE::SPAWN)
		{
			GetpPlayer->SetPos(Vec2((vTile[i])->GetPos().x + TILE_SIZE / 2 , vTile[i]->GetPos().y));
		}
	}
}

void CScene::ReloadScene()
{
	SceneChange(GetSceneType());
}




void CScene::render_tile(HDC _dc)
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCamLT = CCamera::GetInst()->GetLookAt() - (vResolution / 2.f);

	// 화면안에 들어오는 최대 타일 개수
	int iMaxCol = (int)(vResolution.x / (float)TILE_SIZE) + 1;
	int iMaxRow = (int)(vResolution.y / (float)TILE_SIZE) + 1;

	// 카메라 좌상단 위치가 몇행 몇 열인지 계산
	int iLTCol = (int)(vCamLT.x / (float)TILE_SIZE);
	int iLTRow = (int)(vCamLT.y / (float)TILE_SIZE);	

	vector<CObject*>& vecTile = m_arrLayer[(UINT)LAYER_TYPE::TILE];

	for (int j = 0; j < iMaxRow; ++j)
	{
		for (int i = 0; i < iMaxCol; ++i)
		{
			int iRow = iLTRow + j;
			int iCol = iLTCol + i;

			if (iRow < 0 || (int)GetTileRow() <= iRow
				|| iCol < 0 || (int)GetTileCol() <= iCol)
			{
				continue;
			}

			int iTileIdx = iRow * GetTileCol() + iCol;

			if(!vecTile.empty())
				vecTile[iTileIdx]->render(_dc);
		}
	}	
}
