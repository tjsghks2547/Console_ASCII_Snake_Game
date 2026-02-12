#pragma once

#include "Engine_Defines.h"	
#include "Engine_Macro.h"
#include "Engine_Typedef.h"
#include "Renderer.h"
#include "Vector2.h"


BEGIN(Engine)
class ENGINE_DLL CGameInstance
{
	SINGLETON(CGameInstance)

private:
	CGameInstance();
	~CGameInstance() = default;

public:
	HRESULT Initalize(_uint _iNumLayers, Vector2 _screenSize);
	void Update(float _fTimeDelta); 
	void Render(); 


	void Set_Engine_OnOff() { m_bEnigneRun = false; }
	bool Get_Engine_OnOff() { return m_bEnigneRun; }	


	void Clear(_uint _iLevelIndex);

#pragma region Device
	class CDevice* Get_Device_Ptr() { return m_pDevice; }
	void Clear(); 
#pragma endregion 


#pragma region Input_Manager
	// 이전에 입력이 안됐는데, 현재 입력이 됐으면 1번 호출.	
	bool GetKeyEnter(int keyCode);

	// 이전에 입력이 됐는데, 현재 입력이 취소됐으면 1번 호출.
	bool GetKeyRelease(int keyCode);

	// 현재 눌려있으면 반복 호출.
	bool GetKeyPressed(int keyCode);
#pragma endregion 

#pragma region Timer_Manager 
	bool Timer_Update();
	float* Get_DeltaTime_ptr();
#pragma endregion 


#pragma region Level_Manager
	void Set_Level(_uint _iLevelindex , class CLevel* _pLevel);

	// 현재 레벨 가져오는 함수 하나 만들기 
	_uint Get_CurrentLevelIndex();


#pragma endregion 

#pragma region Object_Manager 
	HRESULT Add_GameObject_To_Layer(_uint iLevelIndex, const wstring& strLayerTag, class CGameObject* _pGameObject, void* pArg);
	HRESULT Sub_GameObject_To_Layer(_uint iLevelIndex, const wstring& strLayerTag, class CGameObject* _pGameObject);
	class CGameObject* Find_GameObject_To_Layer(_uint iLevelIndex, const wstring& strLayerTag, const char* _pGameObjectName);
	class CLayer* Find_Layer(_uint iLevelIndex, const wstring& strLayerTag);

#pragma endregion 


#pragma region Collision_Manager

	HRESULT Add_ObjCollider(GROUP_TYPE _GroupType, class CGameObject* _pGameObject);
	HRESULT Sub_ObjCollider(GROUP_TYPE _GroupType, class CGameObject* _pGameObject);

	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset(); 

#pragma endregion 



#pragma region Renderer 
	HRESULT Add_RenderGroup(RENDER_GROUP eRenderGroupID, class CGameObject* pGameObject);
#pragma endregion 



#pragma region Event_Manager
	HRESULT Add_DeleteObject(Event_DeleInfo* _Desc ,class CGameObject* _pGameObject);


#pragma endregion 


private:
	bool m_bEnigneRun = true; 

	
	class CTimerMgr*            m_pTimerMgr         = nullptr; 
	class CInput_Manager*       m_pInput_Manager    = nullptr; 
	class CLevel_Manager*       m_pLevel_Manager    = nullptr;
	class CObject_Manager*      m_pObject_Manager   = nullptr; 
	class CRenderer*            m_pRenderer         = nullptr;
	class CDevice*		        m_pDevice           = nullptr; 
	class CCollision_Manager*   m_pCollsion_Manager = nullptr;
	class CEvent_Manager*		m_pEvent_Manager    = nullptr;

public: 
	void Free();

};
END
