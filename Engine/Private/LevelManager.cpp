#include "LevelManager.h"
#include "Level.h"
#include "GameInstance.h"

CLevel_Manager::CLevel_Manager()
{
}

HRESULT CLevel_Manager::Init()
{
	m_pGameInstance = CGameInstance::GetInstance();
	return S_OK; 
}


void CLevel_Manager::Update(float _fTimeDelta)
{
	
	if (nullptr != m_pCurrentLevel)
		m_pCurrentLevel->Update(_fTimeDelta);
}


void CLevel_Manager::Late_Update(float _fTimeDelta)
{


}


void CLevel_Manager::Set_Level(_uint _iLevelindex, class CLevel* _pLevel)
{

	if(m_pCurrentLevel != nullptr)
	{
		m_pGameInstance->Clear(m_iLevelIndex);		
		m_pCurrentLevel->Free();
	}

	m_pCurrentLevel = _pLevel;			

	m_iLevelIndex = _iLevelindex;		



	
}




CLevel_Manager* CLevel_Manager::Create()
{
	CLevel_Manager* pInstance = new CLevel_Manager; 
	if(FAILED(pInstance->Init()))
	{
		MSG_BOX("Failed to Created LevelManager");
		__debugbreak();
		delete pInstance;	
	}

	return pInstance; 
	
}


void CLevel_Manager::Free()
{
	m_pCurrentLevel->Free();

	delete this;
}