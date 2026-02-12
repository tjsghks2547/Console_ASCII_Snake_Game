#pragma once

#include "Engine_Defines.h"
#include "Engine_Macro.h"
#include "Engine_Typedef.h"



BEGIN(Engine)

class ENGINE_DLL CEvenet_Manager
{

private:
	CEvenet_Manager();
	~CEvenet_Manager(); 


public:
	void Update();
	HRESULT Add_DeleteObject(class CGameObject* _pGameObject); 


private:
	vector<class CGameObject*> m_vecDelete; 



public:
	static CEvenet_Manager* Create();
	void Free();
	

	
};

END