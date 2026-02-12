#include "Game_ExpBar.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"
#include "Player.h"

CGame_ExpBar::CGame_ExpBar()
{
	name = "ExpBar";
}

HRESULT CGame_ExpBar::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();


	for (int i = 0; i < m_iImage_Size; ++i)
	{
		Letter_image[i] = new char[301]; // 100 + null	
	}


	strcpy_s(Letter_image[0], 300, "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	strcpy_s(Letter_image[1], 300, "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");


	m_pTransform->Set_Position(0.f, 42.f);



	return S_OK;
}

void CGame_ExpBar::Priority_Update(float _fTimeDelta)
{





}

void CGame_ExpBar::Update(float _fTimeDelta)
{


}

void CGame_ExpBar::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_UI, this);
}


HRESULT CGame_ExpBar::Ready_Components()
{

	return S_OK;
}

void CGame_ExpBar::OnCollisionEnter(CGameObject* _pOther)
{


	int a = 4;
}

void CGame_ExpBar::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CGame_ExpBar::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CGame_ExpBar::Render()
{
	_uint i_Exp =
		static_cast<CPlayer*>(m_pGameInstance->Find_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Player"), "Player"))
		->Get_Exp();


	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();

	float ratio = 0.f;
	if (i_Exp > 0)
	{
		ratio = static_cast<float>(i_Exp) / static_cast <float>(5);

		if (ratio < 0.f) ratio = 0.f;
		if (ratio > 1.f) ratio = 1.f;
	}

	
	

	for (int image_i = 0; image_i < m_iImage_Size; image_i++)
	{
		// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
		const int length = static_cast<int>(strlen(Letter_image[image_i]));
		const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;
		const int filled = static_cast<int>(length * ratio);	

		for (int i = 0; i < length; ++i)
		{
			m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Letter_image[image_i])[i];

			if (i < filled)
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			else
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		}
	}

	// 여기서 초록색 bar로 칠해주야하는데 


	return S_OK;
}



CGame_ExpBar* CGame_ExpBar::Create(GAME_OBJECT_DESC* _desc)
{
	CGame_ExpBar* pInstance = new CGame_ExpBar();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CGame_ExpBar");
		__debugbreak();
	}

	return pInstance;
}


void CGame_ExpBar::Free()
{
	__super::Free();

	for (int i = 0; i < m_iImage_Size; i++)
	{
		delete[] Letter_image[i];
	}


	delete this;
}