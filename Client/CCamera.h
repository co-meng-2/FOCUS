#pragma once

class CObject;
class CImage;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SHAKE_HORIZONTAL,
	NONE,
};

struct tCamEffectInfo
{
	float		fAccTime;	// ���� ���� �ð�
	float		fDuration;	// ����Ʈ �� ����ð�
	CAM_EFFECT	eEffect;	// ī�޶� ȿ�� Ÿ��
	UINT		iShakeWidth;
	UINT		iShakeSpeed;
	MOVE_DIRECTION eMoveDir;
};




class CCamera
{
	SINGLE(CCamera);
private:
	Vec2					m_vResolution;	// ȭ�� �ػ�
	Vec2					m_vLook;		// ���� ī�޶� �����ִ� ��ǥ
	Vec2					m_vPrevLook;
	Vec2					m_vDiff;		// ȭ�� �ػ� �߽� ��ǥ�� ���� ī�޶� Look ���� ����
	

	CObject*				m_pTargetObj;

	// veil
	CImage*					m_pVeil;		// ������ �뵵 BitmapImage ����
	float					m_fAlpha;		// ���� ����
	
	list<tCamEffectInfo>	m_CamEffectInfo;
		
	


public:
	void init(); 
	void tick();	
	void render(HDC _dc);



public:
	Vec2 GetLookAt() { return m_vLook; }
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void SetTargetObject(CObject* _pObj) { m_pTargetObj = _pObj; }
	void SetCameraEffect(CAM_EFFECT _type, float _fDuration, UINT _iShakeWidth = 0, UINT _iShakeSpeed = 0)
	{
		tCamEffectInfo info = {};
		info.eEffect = _type;
		info.fDuration = _fDuration;		
		info.iShakeWidth = _iShakeWidth;
		info.iShakeSpeed = _iShakeSpeed;
		info.eMoveDir = MOVE_DIRECTION::L;
		m_CamEffectInfo.push_back(info);
	}

	void CamEffectClear() { m_CamEffectInfo.clear(); }
};

