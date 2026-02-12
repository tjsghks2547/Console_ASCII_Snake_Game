#include "Level.h"
#include "GameInstance.h"
CLevel::CLevel()
{
	m_pGameInstance = m_pGameInstance->GetInstance();
	m_pDevice = m_pGameInstance->Get_Device_Ptr();
}


HRESULT CLevel::Initialize()
{

	 

	return S_OK; 
}


void CLevel::Update(float _fTimeDelta)
{

}

void CLevel::Late_Update()
{
}



CLevel* CLevel::Create()
{
	CLevel* pInstance = new CLevel(); 

	if(FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created Level");
		__debugbreak();
		delete pInstance;
	}
	
	return pInstance; 

}

void CLevel::Free()
{
	
}