#include "pch.h"
#include "CAI.h"

#include "CState.h"

AI::AI()
	: CComponent(COMPONENT_TYPE::AI)
	, m_pCurState(nullptr)
{
}

AI::AI(const AI& _origin)
	: CComponent(_origin)
	, m_pCurState(nullptr)
{

}

AI::~AI()
{
	Safe_Del_Map(m_mapState);
}

void AI::tick()
{
	if (nullptr != m_pCurState)
		m_pCurState->tick();
}

void AI::AddState(const wstring& _strKey, CState* _pState)
{
	_pState->m_pAI = this;
	m_mapState.insert(make_pair(_strKey, _pState));
}

CState* AI::FindState(const wstring& _strKey)
{
	map<wstring, CState*>::iterator iter =  m_mapState.find(_strKey);

	if(iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void AI::ChangeState(const wstring& _strKey)
{
	if (nullptr != m_pCurState)
		m_pCurState->exit();

	m_pCurState = FindState(_strKey);

	if (nullptr != m_pCurState)
		m_pCurState->enter();
}
