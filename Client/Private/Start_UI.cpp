#include "Start_UI.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CStart_UI::CStart_UI()
{
	name = "Start";
}

HRESULT CStart_UI::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();


	for (int i = 0; i < m_iImage_Size; ++i)
	{
		Letter_image[i] = new char[101]; // 100 + null	
	}


	strcpy_s(Letter_image[0], 100, "  ___ _____ _   ___ _____ ");
	strcpy_s(Letter_image[1], 100, " / __|_   _/_\\ | _ \\_   _|");
	strcpy_s(Letter_image[2], 100, " \\__ \\ | |/ _ \\|   / | |  ");
	strcpy_s(Letter_image[3], 100, " |___/ |_/_/ \\_\\_|_\\ |_|  ");






	m_pTransform->Set_Position(100.f, 30.f);





	return S_OK;
}

void CStart_UI::Priority_Update(float _fTimeDelta)
{





}

void CStart_UI::Update(float _fTimeDelta)
{


}

void CStart_UI::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_UI, this);
}


HRESULT CStart_UI::Ready_Components()
{

	return S_OK;
}

void CStart_UI::OnCollisionEnter(CGameObject* _pOther)
{


	int a = 4;
}

void CStart_UI::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CStart_UI::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CStart_UI::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();



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
			
			if(m_bSetGreen)
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Green;
			else 
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
		}
	}




	return S_OK;
}



CStart_UI* CStart_UI::Create(GAME_OBJECT_DESC* _desc)
{
	CStart_UI* pInstance = new CStart_UI();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CStart_UI");
		__debugbreak();
	}

	return pInstance;
}


void CStart_UI::Free()
{
	__super::Free();

	for (int i = 0; i < m_iImage_Size; i++)
	{
		delete[] Letter_image[i];
	}


	delete this;
}