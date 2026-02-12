#include "GameLogo.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CGameLogo::CGameLogo()
{

}

HRESULT CGameLogo::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();


	//cout << "            _____  _____ _____ _____    _____ _   _          _  ________  " << "\n";
	//cout << "     /\    / ____|/ ____|_   _|_   _|  / ____| \ | |   /\   | |/ /  ____| " << "\n";
	//cout << "    /  \  | (___ | |      | |   | |   | (___ |  \| |  /  \  | ' /| |__    " << "\n";
	//cout << "   / /\ \  \___ \| |      | |   | |    \___ \| . ` | / /\ \ |  < |  __|   " << "\n";
	//cout << "  / ____ \ ____) | |____ _| |_ _| |_   ____) | |\  |/ ____ \| . \| |____  " << "\n";
	//cout << " /_/    \_\_____/ \_____|_____|_____| |_____/|_| \_/_/    \_\_|\_\______| " << "\n";


	for (int i = 0; i < 6; ++i)
	{
		Logo_image[i] = new char[101]; // 100 + null	
	}


	strcpy_s(Logo_image[0], 100, "            _____  _____ _____ _____    _____ _   _          _  ________  ");
	strcpy_s(Logo_image[1], 100, "     /\\    / ____|/ ____|_   _|_   _|  / ____| \\ | |   /\\   | |/ /  ____| ");
	strcpy_s(Logo_image[2], 100, "    /  \\  | (___ | |      | |   | |   | (___ |  \\| |  /  \\  | ' /| |__    ");
	strcpy_s(Logo_image[3], 100, "   / /\\ \\  \\___ \\| |      | |   | |    \\___ \\| . ` | / /\\ \\ |  < |  __|   ");
	strcpy_s(Logo_image[4], 100, "  / ____ \\ ____) | |____ _| |_ _| |_   ____) | |\\  |/ ____ \\| . \\| |____  ");
	strcpy_s(Logo_image[5], 100, " /_/    \\_\\_____/ \\_____|_____|_____| |_____/|_| \\_/_/    \\_\\_|\\_\\______|");
	




	m_pTransform->Set_Position(75.f, 20.f);



	return S_OK;
}

void CGameLogo::Priority_Update(float _fTimeDelta)
{





}

void CGameLogo::Update(float _fTimeDelta)
{


}

void CGameLogo::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_UI, this);	
}


HRESULT CGameLogo::Ready_Components()
{

	return S_OK;
}

void CGameLogo::OnCollisionEnter(CGameObject* _pOther)
{


	int a = 4;
}

void CGameLogo::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CGameLogo::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CGameLogo::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();

	m_fAccumulatedDeletatime += *(m_pGameInstance->Get_DeltaTime_ptr());


	for(int image_i=0; image_i <6; image_i++)
	{
		// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
		const int length = static_cast<int>(strlen(Logo_image[image_i]));
		const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;

		for (int i = 0; i < length; ++i)
		{
			if (m_pTransform->Get_Position().x + i <0
				|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
				|| (m_pTransform->Get_Position().y) + i < 0)
				continue;


			m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Logo_image[image_i])[i];
			if((int)(m_fAccumulatedDeletatime * 4.0f) % 15 == 0)
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
			else
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (int)(m_fAccumulatedDeletatime * 4.0f) % 15;	
		}
	}


	

	return S_OK;
}



CGameLogo* CGameLogo::Create(GAME_OBJECT_DESC* _desc)
{
	CGameLogo* pInstance = new CGameLogo();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CGameLogo");
		__debugbreak();
	}

	return pInstance;
}


void CGameLogo::Free()
{
	__super::Free();

	for(int i=0; i<6; i++)
	{
		delete[] Logo_image[i];
	}


	delete this;
}

