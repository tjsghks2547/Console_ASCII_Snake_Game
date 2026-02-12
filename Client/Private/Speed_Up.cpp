#include "Speed_Up.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CSpeed_Up::CSpeed_Up()
{
	name = "Exit";
}

HRESULT CSpeed_Up::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();


	for (int i = 0; i < m_iImage_Size; ++i)
	{
		Letter_image[i] = new char[101]; // 100 + null	
	}


	strcpy_s(Letter_image[0],  100, "+------------------------------+");
	strcpy_s(Letter_image[1],  100, "|                              |");
	strcpy_s(Letter_image[2],  100, "|          >\\     >\\           |");
	strcpy_s(Letter_image[3],  100, "|          >>\\    >>\\          |");
	strcpy_s(Letter_image[4],  100, "|         >>> \\  >>> \\         |");
	strcpy_s(Letter_image[5],  100, "|        >>>>  \\>>>>  \\        |");
	strcpy_s(Letter_image[6],  100, "|        >>>>  />>>>  /        |");
	strcpy_s(Letter_image[7],  100, "|         >>> /  >>> /         |");
	strcpy_s(Letter_image[8],  100, "|          >>/    >>/          |");
	strcpy_s(Letter_image[9],  100, "|                              |");
	strcpy_s(Letter_image[10], 100, "|          SPEED  UP           |");
	strcpy_s(Letter_image[11], 100, "|                              |");
	strcpy_s(Letter_image[12], 100, "+------------------------------+");

	m_pTransform->Set_Position(0.f, 45.f);



	return S_OK;
}

void CSpeed_Up::Priority_Update(float _fTimeDelta)
{





}

void CSpeed_Up::Update(float _fTimeDelta)
{


}

void CSpeed_Up::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_UI, this);
}


HRESULT CSpeed_Up::Ready_Components()
{

	return S_OK;
}

void CSpeed_Up::OnCollisionEnter(CGameObject* _pOther)
{


	int a = 4;
}

void CSpeed_Up::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CSpeed_Up::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CSpeed_Up::Render()
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

			//if ((int)(m_fAccumulatedDeletatime * 4.0f) % 15 == 0)
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
		/*	else
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (int)(m_fAccumulatedDeletatime * 4.0f) % 15;*/
		}
	}




	return S_OK;
}



CSpeed_Up* CSpeed_Up::Create(GAME_OBJECT_DESC* _desc)
{
	CSpeed_Up* pInstance = new CSpeed_Up();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CSpeed_Up");
		__debugbreak();
	}

	return pInstance;
}


void CSpeed_Up::Free()
{
	__super::Free();

	for (int i = 0; i < m_iImage_Size; i++)
	{
		delete[] Letter_image[i];
	}


	delete this;
}