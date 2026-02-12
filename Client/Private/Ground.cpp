#include "Ground.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CGround::CGround()
{

}

HRESULT CGround::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();

	image = " ";
	//m_pTransform->Set_Position(5.f, 5.f);

	const int length = static_cast<int>(strlen(image));

	m_pTransform->Set_Size({ length ,1 });



	return S_OK;
}

void CGround::Priority_Update(float _fTimeDelta)
{





}

void CGround::Update(float _fTimeDelta)
{


}

void CGround::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_BACKGROUND, this);
}


HRESULT CGround::Ready_Components()
{

	return S_OK;
}

void CGround::OnCollisionEnter(CGameObject* _pOther)
{

	int a = 4;
}

void CGround::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CGround::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CGround::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();


	// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
	const int length = static_cast<int>(strlen(image));
	const int index = (ScreenSize.x * m_pTransform->Get_Position().y) + m_pTransform->Get_Position().x;

	for (int i = 0; i < length; ++i)
	{
		if (m_pTransform->Get_Position().x + i <0
			|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
			|| (m_pTransform->Get_Position().y) + i < 0)
			continue;

		m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = image[i];
		m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Green;

	}

	return S_OK;
}



CGround* CGround::Create(GAME_OBJECT_DESC* _desc)
{
	CGround* pInstance = new CGround();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : Ground");
		__debugbreak();
	}

	return pInstance;
}


void CGround::Free()
{
	__super::Free();

	delete this;
}



