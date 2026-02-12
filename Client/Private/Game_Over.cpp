#include "Game_Over.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CGame_Over::CGame_Over()
{
	name = "Exit";
}

HRESULT CGame_Over::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();


	for (int i = 0; i < m_iImage_Size; ++i)
	{
		Letter_image[i] = new char[101]; // 100 + null	
	}


	strcpy_s(Letter_image[0], 100, "   _____          __  __ ______    ______      ________ _____   ");
	strcpy_s(Letter_image[1], 100, "  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\  ");
	strcpy_s(Letter_image[2], 100, " | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) | ");
	strcpy_s(Letter_image[3], 100, " | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /  ");
	strcpy_s(Letter_image[4], 100, " | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\  ");
	strcpy_s(Letter_image[5], 100, "  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\ ");
	
	m_pTransform->Set_Position(82.f, 12.f);



	return S_OK;
}

void CGame_Over::Priority_Update(float _fTimeDelta)
{





}

void CGame_Over::Update(float _fTimeDelta)
{


}

void CGame_Over::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_UI, this);
}


HRESULT CGame_Over::Ready_Components()
{

	return S_OK;
}

void CGame_Over::OnCollisionEnter(CGameObject* _pOther)
{


	int a = 4;
}

void CGame_Over::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CGame_Over::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CGame_Over::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();

	m_fAccumulatedDeletatime += *(m_pGameInstance->Get_DeltaTime_ptr());

	for (int image_i = 0; image_i < m_iImage_Size; image_i++)
	{
		// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
		const int length = static_cast<int>(strlen(Letter_image[image_i]));
		const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;

		for (int i = 0; i < length; ++i)
		{
			if (m_pTransform->Get_Position().x + i <0
				|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
				|| (m_pTransform->Get_Position().y) + i < 0)
				continue;


			m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Letter_image[image_i])[i];

			if ((int)(m_fAccumulatedDeletatime * 4.0f) % 15 == 0)
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
			else
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (int)(m_fAccumulatedDeletatime * 4.0f) % 15;
		}
	}




	return S_OK;
}



CGame_Over* CGame_Over::Create(GAME_OBJECT_DESC* _desc)
{
	CGame_Over* pInstance = new CGame_Over();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CGame_Over");
		__debugbreak();
	}

	return pInstance;
}


void CGame_Over::Free()
{
	__super::Free();

	for (int i = 0; i < m_iImage_Size; i++)
	{
		delete[] Letter_image[i];
	}


	delete this;
}