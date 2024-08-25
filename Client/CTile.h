#pragma once
#include "CObject.h"


class CImage;

class CTile :
    public CObject
{
private: 
    CImage*     m_pTileAtlas;   // 타일 이미지 모음
    int         m_iImgIdx;      // 특정 타일

    float       m_fAccTime;




public:
    void SetImgIdx(int _iIdx) { m_iImgIdx = _iIdx; }
    int GetImgIdx() { return m_iImgIdx; }

    void AddImgIdx();
    void SubImgIdx();

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    //void CollisionBeginOverlap(CCollider* _pCollider);
    //void CollisionOverlap(CCollider* _pCollider);
    //void CollisionEndOverlap(CCollider* _pCollider);


    CLONE(CTile);
public:
    CTile();
    ~CTile();
};

