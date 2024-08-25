#include "pch.h"
#include "CDebugMgr.h"

#include "CKeyMgr.h"

CDebugMgr::CDebugMgr()
{

}

CDebugMgr::~CDebugMgr()
{

}

void CDebugMgr::init()
{
	m_bDebugMode = false;
	m_iModeStatus = 0;
}

void CDebugMgr::tick()
{
	if (IsTap(KEY_TYPE::N_0))
	{
		SwitchTrueFalse(m_bDebugMode);
	}

	if (m_bDebugMode)
	{
		if (IsTap(KEY_TYPE::N_7))
		{
			if (m_iModeStatus & (WORD)DEBUG_MODE::COLLIDER_RENDER)
				m_iModeStatus &= !(WORD)DEBUG_MODE::COLLIDER_RENDER;
			else
				m_iModeStatus |= (WORD)DEBUG_MODE::COLLIDER_RENDER;
		}

		if (IsTap(KEY_TYPE::N_8))
		{
			if (m_iModeStatus & (WORD)DEBUG_MODE::PLAYER_INVINCIBLE)
				m_iModeStatus &= !(WORD)DEBUG_MODE::PLAYER_INVINCIBLE;
			else
				m_iModeStatus |= (WORD)DEBUG_MODE::PLAYER_INVINCIBLE;
		}

		if (IsTap(KEY_TYPE::N_9))
		{
			if (m_iModeStatus & (WORD)DEBUG_MODE::FOCUS_MAX)
				m_iModeStatus &= !(WORD)DEBUG_MODE::FOCUS_MAX;
			else
				m_iModeStatus |= (WORD)DEBUG_MODE::FOCUS_MAX;
		}
	}
}
