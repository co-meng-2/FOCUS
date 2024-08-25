#pragma once

class CScene;
class CCollider;



class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	UINT				m_matrix[MAX_LAYER];
	map<LONGLONG, bool> m_mapColInfo;

	float m_fAccTime;


public:
	void tick();



private:
	void CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _eLeft, LAYER_TYPE _eRight);
	void CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight);
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);

	// tilechecker map 불 필요.
	void CollisionTileChecker(CCollider* _pLeft, CCollider* _pRight);

	bool CheckCross(CCollider* _pColLine, CCollider* _pColRect);

public: 
	void clear() {
		memset(m_matrix, 0, sizeof(WORD) * MAX_LAYER); 
		m_mapColInfo.clear();
	}
	void CollisionLayerCheck(LAYER_TYPE _eLeft, LAYER_TYPE _eRight);
	void CollisionLayerRelease(LAYER_TYPE _eLeft, LAYER_TYPE _eRight);
};

