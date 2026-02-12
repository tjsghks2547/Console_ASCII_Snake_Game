#include "GameInstance.h"
#include "TimerMgr.h"
#include "Input_Manager.h"
#include "LevelManager.h"
#include "Object_Manager.h"
#include "Device.h"
#include "ScreenBuffer.h"
#include "CollisionMgr.h"
#include "Event_Manager.h"





CGameInstance::CGameInstance()
{

}


HRESULT CGameInstance::Initalize(_uint _iNumLayers, Vector2 _screenSize)
{
	// 엔진 초기화 과정 
	m_pTimerMgr         = CTimerMgr::Create();
	m_pInput_Manager    = CInput_Manager::Create();
	m_pObject_Manager   = CObject_Manager::Create(_iNumLayers);
	m_pLevel_Manager    = CLevel_Manager::Create();
	m_pRenderer         = CRenderer::Create(); 
	m_pDevice		    = CDevice::Create(_screenSize);
	m_pCollsion_Manager = CCollision_Manager::Create();
	m_pEvent_Manager    = CEvent_Manager::Create();

	return S_OK;	
}

void CGameInstance::Update(float _fTimeDelta)
{
	// 여기서 각 매니저 timer-> input -> object update -> render 순으로 하기 
	// 

	m_pInput_Manager->Priority_Update(_fTimeDelta);

	m_pLevel_Manager->Update(_fTimeDelta);
	m_pObject_Manager->Priority_Update(_fTimeDelta);
	m_pObject_Manager->Update(_fTimeDelta);

	m_pCollsion_Manager->Update();
	m_pEvent_Manager->Update();

	m_pObject_Manager->Late_Update(_fTimeDelta);

	m_pInput_Manager->Late_Update(_fTimeDelta);

	
	
}

void CGameInstance::Render()
{
	m_pDevice->Clear();


	m_pRenderer->Render();


	m_pDevice->GetCurrentBuffer()->Draw(m_pDevice->Get_Frame()->charInfoArray);

	// 버퍼교환
	m_pDevice->Present();


}

void CGameInstance::Clear(_uint _iLevelIndex)
{
	/* 삭제된 레벨용 사봔객체를 들고있는 레이어들을 클리어한다. */
	m_pObject_Manager->Clear(_iLevelIndex);
}




#pragma region Input_Manager
bool CGameInstance::GetKeyEnter(int keyCode)
{
	return m_pInput_Manager->GetKeyEnter(keyCode);
}


bool CGameInstance::GetKeyRelease(int keyCode)
{
	return m_pInput_Manager->GetKeyRelease(keyCode);
}


bool CGameInstance::GetKeyPressed(int keyCode)
{
	return m_pInput_Manager->GetKeyPressed(keyCode);
}


#pragma endregion 


#pragma region Timer_Manager
bool CGameInstance::Timer_Update()
{
	return m_pTimerMgr->Update();
}

float* CGameInstance::Get_DeltaTime_ptr()
{
	return m_pTimerMgr->Get_DeltaTime_ptr();	
}
#pragma endregion 

#pragma region Level_Manager
void CGameInstance::Set_Level(_uint _iLevelindex ,class CLevel* _pLevel)
{
	m_pLevel_Manager->Set_Level(_iLevelindex,_pLevel);
}

_uint CGameInstance::Get_CurrentLevelIndex()
{
	return m_pLevel_Manager->Get_CurrentLevelIndex();	
}
#pragma endregion


#pragma region Object_Manager
HRESULT CGameInstance::Add_GameObject_To_Layer(_uint iLevelIndex, const wstring& strLayerTag, CGameObject* _pGameObject, void* pArg)
{
	
	return m_pObject_Manager->Add_GameObejct_To_Layer(iLevelIndex, strLayerTag, _pGameObject, pArg);

}

HRESULT CGameInstance::Sub_GameObject_To_Layer(_uint iLevelIndex, const wstring& strLayerTag, CGameObject* _pGameObject)
{
	
	return m_pObject_Manager->Sub_GameObject_To_Layer(iLevelIndex, strLayerTag, _pGameObject);

}

CGameObject* CGameInstance::Find_GameObject_To_Layer(_uint iLevelIndex, const wstring& strLayerTag, const char* _pGameObjectName)
{
	return m_pObject_Manager->Find_GameObject_To_Layer(iLevelIndex, strLayerTag, _pGameObjectName);
}


CLayer* CGameInstance::Find_Layer(_uint iLevelIndex, const wstring& strLayerTag)
{
	return m_pObject_Manager->Find_Layer(iLevelIndex, strLayerTag);
}

#pragma endregion 


#pragma region Collision_Manager
HRESULT CGameInstance::Add_ObjCollider(GROUP_TYPE _GroupType, class CGameObject* _pGameObject)
{
	return m_pCollsion_Manager->Add_ObjCollider(_GroupType, _pGameObject);
}


HRESULT CGameInstance::Sub_ObjCollider(GROUP_TYPE _GroupType, class CGameObject* _pGameObject)
{
	return m_pCollsion_Manager->Sub_ObjCollider(_GroupType, _pGameObject);
}

void CGameInstance::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	m_pCollsion_Manager->CheckGroup(_eLeft, _eRight);
}

void CGameInstance::Reset()
{
	m_pCollsion_Manager->Reset(); 
}

#pragma endregion

 
#pragma region  Renderer 

HRESULT CGameInstance::Add_RenderGroup(RENDER_GROUP eRenderGroupID, class CGameObject* pGameObject)
{
	m_pRenderer->Add_RenderGroup(eRenderGroupID, pGameObject);
	return S_OK;
}


#pragma endregion 


#pragma region Event_Manager
HRESULT CGameInstance::Add_DeleteObject(Event_DeleInfo* _Desc ,CGameObject* _pGameObject)
{
	return m_pEvent_Manager->Add_DeleteObject(_Desc, _pGameObject);
}

#pragma endregion 



void CGameInstance::Free()
{
	// 메모리 해제 과정 

	
	m_pInput_Manager->Free();			
	m_pObject_Manager->Free();
	m_pRenderer->Free();
	m_pLevel_Manager->Free();
	m_pCollsion_Manager->Free();
	m_pTimerMgr->Free();
	m_pEvent_Manager->Free();
	m_pDevice->Free();

}
