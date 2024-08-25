#pragma once
// State Pattern
class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene*		m_arrScene[SCENE_TYPE::END];
	CScene*		m_pCurScene;

	bool		m_bRender;

public:
	CScene* GetCurScene() { return m_pCurScene; }

	bool GetRender() { return m_bRender; }
	void SetRender(bool _b) { m_bRender = _b; }
	
private:
	void ChangeScene(SCENE_TYPE _eNext);
	void EnterEffect();

public:
	void init();

	void tick();
	void render(HDC _dc);

	friend class CEventMgr;
};

