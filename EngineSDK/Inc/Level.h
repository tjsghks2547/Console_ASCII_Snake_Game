#pragma once

#include "Engine_Macro.h"
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CLevel
{
protected:
	CLevel();
	virtual ~CLevel() = default; 


public:
	virtual HRESULT Initialize();		
	virtual void Update(float _fTimeDelta);
	virtual void Late_Update(); 


protected:
	class CGameInstance* m_pGameInstance = nullptr; 
	class CDevice* m_pDevice = nullptr; 

public:
	static CLevel* Create(); 
	virtual void Free();

};

END