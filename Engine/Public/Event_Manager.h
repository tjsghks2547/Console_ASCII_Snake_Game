#pragma once

#include "Engine_Defines.h"
#include "Engine_Macro.h"
#include "Engine_Typedef.h"



BEGIN(Engine)

class ENGINE_DLL CEvent_Manager
{
	
private:
	CEvent_Manager();
	~CEvent_Manager();


public:
	void Update();
	HRESULT Add_DeleteObject(Event_DeleInfo* _Desc, class CGameObject* _pGameObject);	


private:
	vector<pair<Event_DeleInfo*,class CGameObject*>> m_vecDelete;
	class CGameInstance* m_pGameInstance = nullptr;


public:
	static CEvent_Manager* Create();
	void Free();
	

	
};

END