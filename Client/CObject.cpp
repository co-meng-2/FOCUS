#include "pch.h"
#include "CObject.h"

#include "CTimeMgr.h"
#include "CComponent.h"

CObject::CObject()
	: m_varrComponent((int)COMPONENT_TYPE::END, vector<CComponent*>(1, nullptr))
	, m_bDead(false)
	, m_bFocus(false)
{
	
}

CObject::CObject(const CObject& _obj)
	: CEntity(_obj)
	, m_varrComponent((int)COMPONENT_TYPE::END, vector<CComponent*>(1, nullptr))
	, m_vPos(_obj.m_vPos)
	, m_vScale(_obj.m_vScale)
	, m_bDead(false)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_varrComponent[i].size(); ++j)
		{
			if (nullptr != _obj.m_varrComponent[i][j])
			{
				AddComponent(_obj.m_varrComponent[i][j]->Clone());
			}
		}
	}
}

CObject::~CObject()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_varrComponent[i].size(); ++j)
		{
			SAFE_DELETE(m_varrComponent[i][j]);
		}
	}
}

void CObject::SelectDeltaTime()
{
	if (m_bFocus)
	{
		m_fDeltaTime = FDT;
	}
	else
	{
		m_fDeltaTime = DT;
	}
}

void CObject::AddComponent(CComponent* _pComponent)
{
	if (m_varrComponent[(UINT)_pComponent->GetType()][0] == nullptr)
	{
		m_varrComponent[(UINT)_pComponent->GetType()][0] = _pComponent;
	}
	else
		m_varrComponent[(UINT)_pComponent->GetType()].push_back(_pComponent);
	_pComponent->m_pOwner = this;
}

void CObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_varrComponent[i].size(); ++j)
		{
			if (nullptr == m_varrComponent[i][j])
				continue;

			m_varrComponent[i][j]->tick();
		}
	}
}

void CObject::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_varrComponent[i].size(); ++j)
		{
			if (nullptr == m_varrComponent[i][j])
				continue;

			m_varrComponent[i][j]->render(_dc);
		}
	}
}
