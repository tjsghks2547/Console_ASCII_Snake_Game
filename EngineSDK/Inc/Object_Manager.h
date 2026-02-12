#pragma once

#include "Engine_Macro.h"
#include "Engine_Defines.h"
#include "Engine_Typedef.h"

BEGIN(Engine)

class ENGINE_DLL CObject_Manager
{
private:
	CObject_Manager();
	~CObject_Manager() = default; 


public:
	HRESULT Add_GameObejct_To_Layer(_uint _iLevelIndex, const wstring& _LayerName, class CGameObject* _pGameObject, void* pArg = nullptr);
	HRESULT Sub_GameObject_To_Layer(_uint _iLevelIndex, const wstring& _LayerName, class CGameObject* _pGameObject, void* pArg = nullptr);
	class CGameObject* Find_GameObject_To_Layer(_uint _iLevelIndex, const wstring& _LayerName, const char* _pGameObjectName);


public:
	class CLayer* Find_Layer(_uint iLevelIndex, const wstring& strLayerTag);
	
public:
	HRESULT Init(_uint _iNumLayers); 
	void Priority_Update(float _fTimeDelta);
	void Update(float _fTimeDelta);
	void Late_Update(float _fTimeDelta);
	void Clear(_uint _iLevelIndex);

private:
	map<const wstring, class CLayer*>* m_pLayers = nullptr; 
	_uint m_iNumLayers = 0; 

public:
	static CObject_Manager* Create(_uint _iNumLayers);
	void Free(); 
	void Destroy();
	
};

END