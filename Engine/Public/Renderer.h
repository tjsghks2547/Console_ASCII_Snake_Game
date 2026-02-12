#pragma once

#include "Engine_Defines.h"
#include "Engine_Macro.h"

BEGIN(Engine)

enum ENGINE_DLL RENDER_GROUP
{
	RG_NONE = -1,
	RG_BACKGROUND,
	RG_ACTOR,
	RG_UI,
	RG_END
};

class ENGINE_DLL CRenderer
{
public:


private:
	CRenderer();
	~CRenderer(); 


public:
	HRESULT Initialize();
	HRESULT Add_RenderGroup(RENDER_GROUP eRenderGroupID, class CGameObject* pGameObject);
	HRESULT Render();

private:
	HRESULT Render_BackGround();
	HRESULT Render_Actor();
	HRESULT Render_UI(); 


private:
	list<class CGameObject*>		m_RenderObjects[RG_END]; // 삭제 삽입이 유리

public:
	static CRenderer* Create(); 
	void Free(); 

};

END