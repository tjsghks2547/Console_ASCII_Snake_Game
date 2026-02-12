#include "Level_Logo.h"
#include "GameInstance.h"
#include "Client_Defines.h"


#pragma region Level
#include "Level_Stage_1.h"
#pragma endregion 

#pragma region UI 
#include "GameLogo.h"
#include "Start_UI.h"
#include "End_UI.h"
#pragma endregion 

#pragma region Actor include
#include "Player.h"
#include "Wall.h"
#pragma endregion 

using namespace Client; 

CLevel_Logo::CLevel_Logo()
{
	

}

CLevel_Logo::~CLevel_Logo()
{


}

HRESULT CLevel_Logo::Initialize()
{

	
	if(FAILED(Ready_Layer_BackGround(TEXT("BackGround"))))
	{
		MSG_BOX("Failed to Ready Layer BackGround ");
		__debugbreak();
	}



	//Load_Map("Map1.txt");

	return S_OK;	
}

void CLevel_Logo::Update(float _fTimeDelta)
{
	// 여기서 커서 설정 ( Start, exit 에서) 
	
	CStart_UI* pStart_UI = static_cast<CStart_UI*>(m_pGameInstance->Find_GameObject_To_Layer(LEVEL::LEVEL_LOGO, TEXT("BackGround"), "Start"));
	CEnd_UI*     pEnd_UI = static_cast<CEnd_UI*>(m_pGameInstance->Find_GameObject_To_Layer(LEVEL::LEVEL_LOGO, TEXT("BackGround"), "Exit"));

	if (m_pGameInstance->GetKeyEnter(VK_UP))
	{
		m_iCurrentMenuIndex = 1; 
		// 그럼 여기서 해당 버튼에 색깔 부여해주기 
		
		pStart_UI->Set_Color_Green(true);
		pEnd_UI->Set_Color_Green(false);
	}

	
	if(m_pGameInstance->GetKeyEnter(VK_DOWN))
	{
		m_iCurrentMenuIndex = 2; 
		pStart_UI->Set_Color_Green(false);
		pEnd_UI->Set_Color_Green(true);
	}


	if (m_pGameInstance->GetKeyEnter(VK_RETURN) && m_iCurrentMenuIndex == 1)
	{
		CLevel_Stage_1* pLevel_Stage_1 = CLevel_Stage_1::Create();
		m_pGameInstance->Set_Level(LEVEL_STAGE_1, pLevel_Stage_1);
		return;
	}


	if (m_pGameInstance->GetKeyEnter(VK_RETURN) && m_iCurrentMenuIndex == 2)
	{
		m_pGameInstance->Set_Engine_OnOff();
	}


	


}

void CLevel_Logo::Late_Update()
{

	//여기서 렌더그룹에 넣는역할이였음. 



}

void CLevel_Logo::Load_Map(const char* filename)
{


}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const wchar_t* pLayerTag)
{
	
	//m_pGameInstace->Add_GameObject_To_Layer(LEVEL::LEVEL_LOGO,
	//	pLayerTag,
	//	CPlayer::Create(),
	//	nullptr);
	//
	//
	//m_pGameInstace->Add_GameObject_To_Layer(LEVEL::LEVEL_LOGO,
	//	pLayerTag,
	//	CWall::Create(),
	//	nullptr);
	
	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_LOGO,
		pLayerTag,
		CGameLogo::Create(),
		nullptr);


	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_LOGO,
		pLayerTag,
		CStart_UI::Create(),
		nullptr);


	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_LOGO,
		pLayerTag,
		CEnd_UI::Create(),
		nullptr);




	


	
	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_UI(const wchar_t* pLayerTag)
{



	return S_OK;	
}


CLevel_Logo* CLevel_Logo::Create()
{
	CLevel_Logo* pInstance = new CLevel_Logo();

	if(FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : Level_Logo");
		__debugbreak();
	}
	return pInstance;

}

void CLevel_Logo::Free()
{
	__super::Free(); 

	delete this; 
}