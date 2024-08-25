#pragma once

#include "CEntity.h"

#include "CPlayer.h"

class CTile;
class CObject;

class CScene
	: public CEntity
{
private:
	vector<CObject*>	m_arrLayer[MAX_LAYER];

	UINT				m_iTileCol;
	UINT				m_iTileRow;
	UINT				m_iSelectIdx;
	UINT				m_iButtonCount;
	UINT				m_iPrevButtonCount;

	bool				bOneFrameAFter;

	SCENE_TYPE			m_eSceneType;

	SCENE_TYPE			m_eNextScene;

public:
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayer) 
	{ 
		m_arrLayer[(UINT)_eLayer].push_back(_pObject);
		_pObject->SetLayer(_eLayer);
	}
	const vector<CObject*>& GetObjects(LAYER_TYPE _eType) { return m_arrLayer[(UINT)_eType]; }

	UINT GetTileCol(){return m_iTileCol;}
	UINT GetTileRow(){return m_iTileRow;}
	UINT GetSelectIdx() { return m_iSelectIdx; }
	SCENE_TYPE GetSceneType() { return m_eSceneType; }
	UINT GetButtonCount() { return m_iButtonCount; }
	SCENE_TYPE GetNextScene() { return m_eNextScene; }

	void ResetOneFrameAfter() { bOneFrameAFter = false; }
	void SetSelectIdx(UINT _idx) { m_iSelectIdx = _idx; }
	void SetFocusedUI(CObject* _pUI);
	void AddButtonCount() { ++m_iButtonCount; }
	void SubButtonCount() { --m_iButtonCount; }
	void SetButtonCountZero() { m_iButtonCount = 0; }
	void SetNextScene(SCENE_TYPE _nextScene) { m_eNextScene = _nextScene; }
	void MoveNextScene() { SceneChange(GetNextScene()); }
	

public:
	void CreateTile(UINT _iCol, UINT _iRow);
	void ReloadScene();

public:
	virtual void tick();

	
	// Scene 진입 시 호출
	virtual void enter() = 0;

	// Scene 나올 때 호출
	virtual void exit() = 0;
	
	virtual void render(HDC _dc);

public:
	void DeleteAllObject();
	void DeleteAllObjectEX();

protected:
	void DeleteObjectEX(LAYER_TYPE _eType);
	void DeleteObject(LAYER_TYPE _eType);
	void TileLoadOption(CTile* _pTile);
	void TileToBlock();

	void LoadTile(wstring _path);
	void LoadObject(wstring _path);
	

private:
	void render_tile(HDC _dc);


public:
	CScene(SCENE_TYPE _scenetype);
	virtual ~CScene();
};

