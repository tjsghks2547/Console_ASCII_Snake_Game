#include "Tower_projectile.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"


CTower_projectile::CTower_projectile()
{
	name = "Tower_Bullet";
}

HRESULT CTower_projectile::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);

	Ready_Components();

	image = "a";

	if(_desc != nullptr)
	{
		m_vDir.x = _desc->dir_x;
		m_vDir.y = _desc->dir_y;

		m_pTransform->Set_Position(_desc->x, _desc->y);
	}

	m_pTransform->Set_Speed(15.f);
	m_pTransform->Set_Size({ 1 ,1 });

	return S_OK;
}

void CTower_projectile::Priority_Update(float _fTimeDelta)
{


}

void CTower_projectile::Update(float _fTimeDelta)
{
	

	if(m_vDir.x == 1 && m_vDir.y == 0) // Right
	{
		m_pTransform->Go_Right(_fTimeDelta);
	}

	if (m_vDir.x == -1 && m_vDir.y == 0) // Left 
	{
		m_pTransform->Go_Left(_fTimeDelta);
	}

	if (m_vDir.x == 0 && m_vDir.y == -1) // Up
	{
		m_pTransform->Go_Up(_fTimeDelta);
	}

	if (m_vDir.x == 0 && m_vDir.y == 1) // down
	{
		m_pTransform->Go_Down(_fTimeDelta);
	}


	

}

void CTower_projectile::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_ACTOR, this);
}


HRESULT CTower_projectile::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	//m_pColliderCom->Set_Collider_Name("Player");
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::BULLET, this);

	return S_OK;
}

void CTower_projectile::OnCollisionEnter(CGameObject* _pOther)
{
	//m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::BULLET, this);


	if (!m_bDead)
	{
		Event_DeleInfo* Info = new Event_DeleInfo();

		Info->iLevelIndex = m_pGameInstance->Get_CurrentLevelIndex();
		Info->strLayerTag = TEXT("Projectile");

		m_pGameInstance->Add_DeleteObject(Info, this);
		
		m_bDead = true; 
	}

	int a = 4;
}

void CTower_projectile::OnCollision(CGameObject* _pOther)
{

	int a = 4;
}

void CTower_projectile::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CTower_projectile::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();


	// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
	const int length = static_cast<int>(strlen(image));
	const int index = (ScreenSize.x * m_pTransform->Get_Position().y) + m_pTransform->Get_Position().x;

	for (int i = 0; i < length; ++i)
	{
		m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = image[i];
		m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	}

	return S_OK;
}



CTower_projectile* CTower_projectile::Create(GAME_OBJECT_DESC* _desc)
{
	CTower_projectile* pInstance = new CTower_projectile();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : Tower_projectile");
		__debugbreak();
	}

	return pInstance;
}


void CTower_projectile::Free()
{
	__super::Free();	

	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::BULLET, this);	
	//m_pGameInstance->Sub_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("Projectile"), this);	


	delete this;
}