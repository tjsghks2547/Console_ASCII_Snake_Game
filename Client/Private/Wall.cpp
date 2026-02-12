#include "Wall.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CWall::CWall()
{
	name = "Wall";
}

HRESULT CWall::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();	

	image = "#";
	m_pTransform->Set_Position(5.f, 5.f);

	const int length = static_cast<int>(strlen(image));

	m_pTransform->Set_Size({ 1 ,1 });



	return S_OK;
}

void CWall::Priority_Update(float _fTimeDelta)
{





}

void CWall::Update(float _fTimeDelta)
{
	

}

void CWall::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_BACKGROUND, this);
}


HRESULT CWall::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	//m_pColliderCom->Set_Collider_Name("Player");
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::OBJECT, this);

	return S_OK;
}

void CWall::OnCollisionEnter(CGameObject* _pOther)
{

	
	//m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Structure"), this);
	//m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::OBJECT, this);
	//
	//Free();

	int a = 4;
}

void CWall::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CWall::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CWall::Render()
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
		m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
	}

	return S_OK;
}



CWall* CWall::Create(GAME_OBJECT_DESC* _desc)
{
	CWall* pInstance = new CWall();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : Wall");
		__debugbreak();
	}

	return pInstance;
}


void CWall::Free()
{
	__super::Free();

	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::OBJECT, this);
	//m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Structure"), this);

	

	delete this;
}

