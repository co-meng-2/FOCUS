#include "pch.h"
#include "CState.h"

#include "CAI.h"

CState::CState()
{
}

CState::~CState()
{
}

CObject* CState::GetOwner()
{
	return m_pAI->GetOwner();	
}
