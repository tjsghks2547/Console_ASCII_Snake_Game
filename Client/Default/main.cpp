#include <iostream>
#include "MainApp.h"
#include "GameInstance.h"


#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


int main()
{

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(198);

	CMainApp* pMainApp = CMainApp::Create();

	Engine::CGameInstance* pGameInstance = Engine::CGameInstance::GetInstance();

	//Timer ¼³Á¤ 
	
	while(pGameInstance->Get_Engine_OnOff())
	{
		if(pGameInstance->Timer_Update())
		{
			pMainApp->Update();
			pMainApp->Render();	
		}
	}
	
	pMainApp->Free();

	return 0; 
}