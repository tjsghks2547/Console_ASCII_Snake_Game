#include "Boss_Monster.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"
#include "Tower_projectile.h"
#include "Victory_UI.h"
#include "Player.h"


CBoss_Monster::CBoss_Monster()
{
	name = "Boss_Monster";
}

HRESULT CBoss_Monster::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();



	for (int i = 0; i < m_iImage_Size; ++i)
	{
		Letter_image[i] = new char[100]; // 20 + null	
	}


	//위 
	strcpy_s(Letter_image[0], 100, "      ,~.");
	strcpy_s(Letter_image[1], 100, "   ,-'__ `-,");
	strcpy_s(Letter_image[2], 100, "  {,-'  `. }              ,')");
	strcpy_s(Letter_image[3], 100, " ,( a )   `-.__         ,',')~,");
	strcpy_s(Letter_image[4], 100, "&lt;=.) (         `-.__,==' ' ' '}");
	strcpy_s(Letter_image[5], 100, "  (   )                      /)");
	strcpy_s(Letter_image[6], 100, "   `-'\\   ,                    )");
	strcpy_s(Letter_image[7], 100, "       |  \\        `~.        /");
	strcpy_s(Letter_image[8], 100, "       \\   `._        \\      /");
	strcpy_s(Letter_image[9], 100, "        \\     `._____,'    ,'");
	strcpy_s(Letter_image[10], 100, "         `-.             ,'");
	strcpy_s(Letter_image[11], 100, "            `-._     _,-'");
	strcpy_s(Letter_image[12], 100, "                77jj'");
	strcpy_s(Letter_image[13], 100, "            __//--'/`          ");
	strcpy_s(Letter_image[14], 100, "          ,--'/`  '");


	m_pTransform->Set_Size({ 10 ,15 }); // 여기 크기에 문제가 있음 충돌에서 한번에 여러콜 들어와서 	

	m_pTransform->Set_Speed(5.f);


	m_pTransform->Set_Position(190, 15);

	return S_OK;
}

void CBoss_Monster::Priority_Update(float _fTimeDelta)
{

	

}

void CBoss_Monster::Update(float _fTimeDelta)
{
	if(m_bBossHurtEnter)
	{
		m_fBossHurtCool += _fTimeDelta; 

		if(m_fBossHurtCool >= 0.2f)
		{
			m_bBossHurtEnter = false; 
			m_fBossHurtCool = 0.f; 
		}
	}
}

void CBoss_Monster::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_ACTOR, this);
}


HRESULT CBoss_Monster::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	//m_pColliderCom->Set_Collider_Name("Player");
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::MONSTER, this);

	return S_OK;
}

void CBoss_Monster::OnCollisionEnter(CGameObject* _pOther)
{
	if (_pOther->Get_Name() == "Attack_item")
	{
		m_iHp--;

		m_bBossHurtEnter = true; 

		if (m_iHp <= 0 && !m_bDead)
		{
			Event_DeleInfo* Info = new Event_DeleInfo();

			Info->iLevelIndex = m_pGameInstance->Get_CurrentLevelIndex();
			Info->strLayerTag = TEXT("Monster");

			m_pGameInstance->Add_DeleteObject(Info, this);

			m_bDead = true;
			m_bBossHurtEnter = false; 

			m_pGameInstance->Add_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("UI"), CVictory_UI::Create(), nullptr);
			
			CPlayer* pPlayer = static_cast<CPlayer*>(m_pGameInstance->Find_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("Player"), "Player"));
			pPlayer->Set_GameStatue(true);

		}

	
	}

	int a = 4;
}

void CBoss_Monster::OnCollision(CGameObject* _pOther)
{
	

}

void CBoss_Monster::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CBoss_Monster::Render()
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

			if (m_fBossHurtCool)
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Red;
			else
				m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
		}
	}
	
	return S_OK;
}



CBoss_Monster* CBoss_Monster::Create(GAME_OBJECT_DESC* _desc)
{
	CBoss_Monster* pInstance = new CBoss_Monster();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CBoss_Monster");
		__debugbreak();
	}

	return pInstance;
}


void CBoss_Monster::Free()
{

	__super::Free();

	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::MONSTER, this);

	for (int i = 0; i < m_iImage_Size; i++)
	{
		delete[] Letter_image[i];

	}

	delete this;
}