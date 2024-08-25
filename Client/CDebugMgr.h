#pragma once
class CDebugMgr
{
	SINGLE(CDebugMgr)

private:
	bool m_bDebugMode;
	WORD m_iModeStatus;

public:
	WORD GetModeStatus() { return m_iModeStatus; }
	bool IsDebugMode() { return m_bDebugMode; }

public:
	void init();

	void tick();

};

