#include "MainApp.h"
#include "GameInstance.h"
#include "Level_Logo.h"
#include "Player.h"

CMainApp::CMainApp()
{

}

CMainApp::~CMainApp()
{

}


HRESULT CMainApp::Init()		
{
	m_pGameInstance = CGameInstance::GetInstance(); 
	m_pGameInstance->Initalize(2,Vector2(230,60));
	m_pGameInstance->Set_Level(LEVEL_LOGO , CLevel_Logo::Create());

	m_pfDT = m_pGameInstance->Get_DeltaTime_ptr();

	return S_OK;
}


void CMainApp::Update()
{

	m_pGameInstance->Update(*m_pfDT);
	
	//임시코드 
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		m_pGameInstance->Set_Engine_OnOff();
	}

}


void CMainApp::Late_Update()
{


}


void CMainApp::Render()
{
	m_pGameInstance->Render();	
}




CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();

	if(FAILED(pInstance->Init()))
	{
		MSG_BOX("Failed to Created MainApp");
		__debugbreak();
		delete pInstance;	
	}

	return pInstance; 
}

void CMainApp::Free()
{
	m_pGameInstance->Free();


	delete this; 
}