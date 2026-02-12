#pragma once

#include "Engine_Macro.h"
#include "Engine_Defines.h"


BEGIN(Engine)

class ENGINE_DLL CLayer
{
private:
	CLayer();
	~CLayer() = default;


public:
	void Priority_Update(float _fTimeDelta);
	void Update(float _fTimeDelta);
	void Late_Update(float _fTimeDelta);

	HRESULT Add_GameObject(class CGameObject* _pGameObject);


	vector<class CGameObject*>& Get_GameObject_List() {return m_vecGameObject;}

private:
	vector<class CGameObject*> m_vecGameObject;

	


public:
	static CLayer* Create();
	void Free();



};

END