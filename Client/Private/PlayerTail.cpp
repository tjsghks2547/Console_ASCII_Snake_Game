#include "PlayerTail.h"
#include "Device.h"
#include "GameInstance.h"
#include "Transform.h"
#include "Collider.h"

CPlayerTail::CPlayerTail()
{
	name = "Tail";
}

HRESULT CPlayerTail::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);

	Ready_Components();

	image = "a";
	
	m_pTransform->Set_Position(0.f, 0.f);

	const int length = static_cast<int>(strlen(image));
	m_pTransform->Set_Size({ 1 ,1 });

	return S_OK;
}

void CPlayerTail::Priority_Update(float _fTimeDelta)
{	
	// 먹으면 이펙트 나도록 하기
	

}


void CPlayerTail::Update(float _fTimeDelta)
{
	

}

void CPlayerTail::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_ACTOR, this);
}

HRESULT CPlayerTail::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();


	// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
	const int length = static_cast<int>(strlen(image));
	const int index = (ScreenSize.x * m_pTransform->Get_Position().y) + m_pTransform->Get_Position().x;

	for (int i = 0; i < length; ++i)
	{
		m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = image[i];
		
		if(m_Color != FOREGROUND_BLUE || m_Color !=0)	
			m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = m_Color;	
		else
			m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Blue;
	}

	return S_OK;
}


HRESULT CPlayerTail::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::TAIL, this);

	return S_OK;
}


CPlayerTail* CPlayerTail::Create(GAME_OBJECT_DESC* _desc)
{
	CPlayerTail* pInstance = new CPlayerTail();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : PlayerTail");
		__debugbreak();
	}

	return pInstance;

}

void CPlayerTail::Free()
{
	__super::Free();

	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::TAIL, this);
	//m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Tail"), this);	



	delete this;
}

