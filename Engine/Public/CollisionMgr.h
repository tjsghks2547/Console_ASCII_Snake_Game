#pragma once

#include "Collider.h"

BEGIN(Engine)

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};



class ENGINE_DLL CCollision_Manager
{
private:
	CCollision_Manager();
	~CCollision_Manager();



public:
	HRESULT Initialize();
	void Update(); 
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::GROUP_END); }
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	bool isCollision(CCollider* _pLeftCol, CCollider* _pRightCol);


	HRESULT Add_ObjCollider(GROUP_TYPE _GroupType, class CGameObject* _pGameObject);
	HRESULT Sub_ObjCollider(GROUP_TYPE _GroupType, class CGameObject* _pGameObject);

private:
	CGameObject* Find_GameObject(GROUP_TYPE _GroupType, class CGameObject* _pGameObject);	

	

private:
	map<ULONGLONG, bool> m_mapCoIinfo; // 충돌체간의 이전 프레임 충돌 정보 
	UINT m_arrCheck[(UINT)GROUP_TYPE::GROUP_END];

	vector<class CGameObject*>		m_arrObjCollider[(UINT)GROUP_TYPE::GROUP_END];


public:
	static CCollision_Manager* Create(); 
	virtual void Free(); 


};

END