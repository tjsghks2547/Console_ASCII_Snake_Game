#include "TailPlus_Item.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"
#include <cstdlib> // rand
#include <ctime>   // time


CTailPlus_Item::CTailPlus_Item()
{
	name = "TailPlus_Item";
}

CTailPlus_Item::~CTailPlus_Item()
{

}


HRESULT CTailPlus_Item::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();

	image = "■";
	m_pTransform->Set_Position(10.f, 10.f);

	const int length = static_cast<int>(strlen(image));

	m_pTransform->Set_Size({ length ,1 });


	// 여기서 랜덤으로 생성해야할듯

	//// y는 41이였음 x는 230 
	//Vector2 Position = GetRandomPos(3, 205, 2, 40);

	if(_desc != nullptr)
	{
		m_pTransform->Set_Position(_desc->x, _desc->y);	
	}
	



	return S_OK;
}

void CTailPlus_Item::Priority_Update(float _fTimeDelta)
{





}

void CTailPlus_Item::Update(float _fTimeDelta)
{


}

void CTailPlus_Item::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_ACTOR, this);
}


HRESULT CTailPlus_Item::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	//m_pColliderCom->Set_Collider_Name("Player");
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::OBJECT, this);

	return S_OK;
}

void CTailPlus_Item::OnCollisionEnter(CGameObject* _pOther)
{
	if(_pOther->Get_Name() == "Player")
	{
		Event_DeleInfo* Info = new Event_DeleInfo();

		Info->iLevelIndex = m_pGameInstance->Get_CurrentLevelIndex();
		Info->strLayerTag = TEXT("Item");

		m_pGameInstance->Add_DeleteObject(Info, this);
	}
		
	
	/*m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::OBJECT, this);
	m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Item"), this);
	*/
	//Free();

	int a = 4;
}

void CTailPlus_Item::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CTailPlus_Item::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CTailPlus_Item::Render()
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



CTailPlus_Item* CTailPlus_Item::Create(GAME_OBJECT_DESC* _desc)
{
	CTailPlus_Item* pInstance = new CTailPlus_Item();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : TailPlus_Item");
		__debugbreak();
	}

	return pInstance;
}


void CTailPlus_Item::Free()
{

	__super::Free();

	//free가 겹치네 
	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::OBJECT, this);
	//m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Item"), this);

	

	delete this;
}

