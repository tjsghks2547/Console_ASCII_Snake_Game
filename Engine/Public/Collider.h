#pragma once
#include "Component.h"


BEGIN(Engine)

class ENGINE_DLL CCollider final : public CComponent
{
private:
	CCollider();
	virtual ~CCollider();


public:
	HRESULT Initialize(class CGameObject* pOwner);

	class CGameObject* Get_Owner() { return m_pGameObejct; }
	void Set_Owner(class CGameObject* pOwner) { m_pGameObejct = pOwner; }
	bool Intersect(CCollider* pCollider); 
	UINT Get_ID() { return m_iID; }

private:

	int     m_width  = 0;
	int     m_height = 0;

	UINT		 m_iID = 0;     // 충돌체 고유한 ID 값	
	static UINT  g_iNextID; //정적맴버라 객체내용에 포함안됨

	Vector2 m_vPosition = {};
	class CGameObject* m_pGameObejct = nullptr;


public:
	static CCollider* Create(CGameObject* pOwner); 
	virtual void Free() override; 
	

};

END