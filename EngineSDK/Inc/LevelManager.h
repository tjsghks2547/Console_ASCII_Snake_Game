#pragma once

#include "Engine_Macro.h"
#include "Engine_Defines.h"
#include "Engine_Typedef.h"

BEGIN(Engine)

class ENGINE_DLL CLevel_Manager 
{
private:
	CLevel_Manager();
	~CLevel_Manager() = default;


public:
	HRESULT Init();
	void Update(float _fTimeDelta);
	void Late_Update(float _fTimeDelta);

	void Set_Level(_uint _iLevelindex, class CLevel* _pLevel);	
	class CLevel * Get_CurrentLevel() { return m_pCurrentLevel; }
	_uint Get_CurrentLevelIndex() {return m_iLevelIndex;}
public:


private:
	class CLevel* m_pCurrentLevel = nullptr;
	class CGameInstance* m_pGameInstance = nullptr; 


private:
	_uint m_iLevelIndex = 0; 

public:
	static CLevel_Manager* Create(); 
	void Free(); 

};

END