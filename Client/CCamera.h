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
	float		fAccTime;	// 누적 진행 시간
	float		fDuration;	// 이펙트 총 재생시간
	CAM_EFFECT	eEffect;	// 카메라 효과 타입
	UINT		iShakeWidth;
	UINT		iShakeSpeed;
	MOVE_DIRECTION eMoveDir;
};




class CCamera
{
	SINGLE(CCamera);
private:
	Vec2					m_vResolution;	// 화면 해상도
	Vec2					m_vLook;		// 현재 카메라가 보고있는 좌표
	Vec2					m_vPrevLook;
	Vec2					m_vDiff;		// 화면 해상도 중심 좌표와 현재 카메라 Look 간에 차이
	

	CObject*				m_pTargetObj;

	// veil
	CImage*					m_pVeil;		// 가림막 용도 BitmapImage 생성
	float					m_fAlpha;		// 투명 강도
	
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

