#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_llFrequence;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER   m_llPrevCount;

	float			m_fAccTime;
	float			m_fDeltaTime;
	float			m_fSlow;

public:
	void init();
	void tick();
	void render(HDC _dc);

public:
	float GetDeltaTime() { return m_fDeltaTime; }
	float GetFocusDeltaTime() { return m_fDeltaTime / m_fSlow; }

};

