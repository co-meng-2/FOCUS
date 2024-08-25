#pragma once
#include "CObject.h"
class CForce :
    public CObject
{
private:
    float   m_fForce;   // ���� ũ��
    float   m_fRadius;  // ���� �ݰ�
    float   m_fDuration; // �� ���� �ð�

    float   m_fAccTime; // �����ð�

public:
    void SetForceInfo(float _fForce, float _fRadius, float _fDuration)
    {
        m_fForce = _fForce;
        m_fRadius = _fRadius;
        m_fDuration = _fDuration;
    }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

private:
    void AddForceToLayer(LAYER_TYPE _eType);

public:
    CForce* Clone() { return new CForce(*this); }

public:
    CForce();
    virtual ~CForce();
};

