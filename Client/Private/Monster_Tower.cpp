#include "Monster_Tower.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"
#include "Tower_projectile.h"


CMonster_Tower::CMonster_Tower()
{
	name = "Monster_Tower";
}

HRESULT CMonster_Tower::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);


	Ready_Components();


	
	for (int i = 0; i < m_iImage_Size; ++i)
	{
		Letter_image_Up[i]    = new char[10]; // 20 + null	
		Letter_image_Right[i] = new char[10];
		Letter_image_Left[i]  = new char[10];
		
	}

	for (int i = 0; i < 3; ++i)
	{
		Letter_image_Down[i] = new char[10];
	}
	


	//위 
	strcpy_s(Letter_image_Up[0], 10, " |");
	strcpy_s(Letter_image_Up[1], 10, "[O]");
	
	

	// 오른쪽
	strcpy_s(Letter_image_Right[0], 10, "    ");
	strcpy_s(Letter_image_Right[1], 10, "[O]ㅡ");


	//왼쪽
	strcpy_s(Letter_image_Left[0],  10, "     ");
	strcpy_s(Letter_image_Left[1],  10, "ㅡ[O]");



	// 아래
	strcpy_s(Letter_image_Down[0], 10, "   ");
	strcpy_s(Letter_image_Down[1], 10, "[O]");	
	strcpy_s(Letter_image_Down[2], 10, " | ");


	m_pTransform->Set_Size({ 6 ,3 }); // 여기 크기에 문제가 있음 충돌에서 한번에 여러콜 들어와서 	

	m_pTransform->Set_Speed(5.f);

	m_pTransform->Set_Position(_desc->x, _desc->y);

	return S_OK;
}

void CMonster_Tower::Priority_Update(float _fTimeDelta)
{

	if(m_iCurrentTowerHead != m_iPreTowerHead)
	{
		m_iRandomMoveNumber = GetRandomX(0, 100) % 4;
		m_iPreTowerHead = m_iCurrentTowerHead;
	}
	

	//여기서 포탑의 회전상태 설정  
	if((int)m_fAccumulatedTimeDelta % 4 == 0)  // up
	{
		m_iCurrentTowerHead = Tower_Up;

		//m_pTransform->Set_Position(20.f, 20.f);
	}

	else if ((int)m_fAccumulatedTimeDelta % 4 == 1) // right 
	{
		m_iCurrentTowerHead = Tower_Right;
		//m_pTransform->Set_Position(20.f, 20.f);
	
	}
	
	else if ((int)m_fAccumulatedTimeDelta % 4 == 2) // down 
	{
		m_iCurrentTowerHead = Tower_Down;
		//m_pTransform->Set_Position(20.f, 20.f);
	}

	else if ((int)m_fAccumulatedTimeDelta % 4 == 3) // left
	{
		m_iCurrentTowerHead = Tower_Left;

		//아이디어 괜찮은데?
		//m_pTransform->Set_Position(m_pTransform->Get_Position().x - 1, m_pTransform->Get_Position().y);
		//m_pTransform->Set_Position(18.5f, 20.f);
	}


	// 숫자 랜덤 

	
	switch (m_iRandomMoveNumber)
	{
	case 0:
		m_pTransform->Go_Down(_fTimeDelta);	
		break;
	case 1:
		m_pTransform->Go_Up(_fTimeDelta);	
		break;
	case 2:
		m_pTransform->Go_Right(_fTimeDelta);
		break;
	case 3:
		m_pTransform->Go_Left(_fTimeDelta);
	}

}

void CMonster_Tower::Update(float _fTimeDelta)
{
	m_fAccumulatedTimeDelta += _fTimeDelta;
	m_fBulletAccumulatedTimeDelta += _fTimeDelta;


	if (m_fBulletAccumulatedTimeDelta >=1.f)	
	{
		//CGameObject* pObject = m_pGameInstance->Find_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("Player"), "Player");
		//CTransform*  pPlayerTransform = dynamic_cast<CTransform*>(pObject->Find_Component(TEXT("Transform")));
		
		//방향벡터 구하기 
		

		//플레이어 위치
		//Vector2 vPlayerPos = pPlayerTransform->Get_Position();

		//포탑의 위치 
		Vector2 vTowerPos = m_pTransform->Get_Position();		

		Vector2 vDir = { 0,0 };

		GAME_OBJECT_DESC desc;

		// 방향과 위치를 전달해야함.

		// 노말라이즈 작업해야함 방향이니깐
	

		// 어차피 8방향이니깐
		// X 방향
		switch (m_iCurrentTowerHead)
		{
		case Tower_Up:
			vDir = { 0,-1 };
			desc.x = m_pTransform->Get_Position().x;
			desc.y = m_pTransform->Get_Position().y -2.f;
			break;

		case Tower_Right:
			vDir = { 1,0 };
			desc.x = m_pTransform->Get_Position().x + 2.f;
			desc.y = m_pTransform->Get_Position().y;
			break;

		case Tower_Down:
			vDir = { 0,1 };
			desc.x = m_pTransform->Get_Position().x;
			desc.y = m_pTransform->Get_Position().y + 2.f;
			break;

		case Tower_Left:
			vDir = { -1,0 };
			desc.x = m_pTransform->Get_Position().x - 2.f;
			desc.y = m_pTransform->Get_Position().y;
			break;
		}

		desc.dir_x = vDir.x;
		desc.dir_y = vDir.y;
		


		

		m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1, TEXT("Projectile"), CTower_projectile::Create(&desc), nullptr);

		m_fBulletAccumulatedTimeDelta = 0.f; 
	}
}

void CMonster_Tower::Late_Update(float _fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_ACTOR, this);	
}


HRESULT CMonster_Tower::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	//m_pColliderCom->Set_Collider_Name("Player");
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::MONSTER, this);

	return S_OK;
}

void CMonster_Tower::OnCollisionEnter(CGameObject* _pOther)
{
	if(_pOther->Get_Name() == "Wall" && !m_bDead)
	{
		Event_DeleInfo* Info = new Event_DeleInfo();

		Info->iLevelIndex = m_pGameInstance->Get_CurrentLevelIndex();
		Info->strLayerTag = TEXT("Tower");

		m_pGameInstance->Add_DeleteObject(Info, this);
		// 어떻게 이게 2번이나 불리지?
		m_bDead = true; // 이거 추가해주기 (크기가 커서 여러번 호출 된거였음)
	}


	else if (_pOther->Get_Name() == "Boss_Monster" && !m_bDead)
	{
		Event_DeleInfo* Info = new Event_DeleInfo();

		Info->iLevelIndex = m_pGameInstance->Get_CurrentLevelIndex();
		Info->strLayerTag = TEXT("Tower");

		m_pGameInstance->Add_DeleteObject(Info, this);

		m_bDead = true; 
	}

}

void CMonster_Tower::OnCollision(CGameObject* _pOther)
{
	int a = 4;
}

void CMonster_Tower::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4;
}

HRESULT CMonster_Tower::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();


#pragma region Tower_Up 

	if (m_iCurrentTowerHead == Tower_Up)
	{
		for (int image_i = 0; image_i < m_iImage_Size; image_i++)
		{
			// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
			const int length = static_cast<int>(strlen(Letter_image_Up[image_i]));
			const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;

			for (int i = 0; i < length; ++i)
			{
				if (m_pTransform->Get_Position().x + i <0
					|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
					|| (m_pTransform->Get_Position().y) + i < 0)
					continue;


				m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Letter_image_Up[image_i])[i];

				if (m_bSetGreen)
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Green;
				else
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
			}
		}
	}
#pragma endregion 

#pragma region Tower_Right 

	else if (m_iCurrentTowerHead == Tower_Right)
	{
		for (int image_i = 0; image_i < m_iImage_Size; image_i++)
		{
			// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
			const int length = static_cast<int>(strlen(Letter_image_Right[image_i]));
			const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;

			for (int i = 0; i < length; ++i)
			{
				if (m_pTransform->Get_Position().x + i <0
					|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
					|| (m_pTransform->Get_Position().y) + i < 0)
					continue;


				m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Letter_image_Right[image_i])[i];

				if (m_bSetGreen)
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Green;
				else
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
			}
		}
	}
#pragma endregion 

#pragma region Tower_Left

	else if (m_iCurrentTowerHead == Tower_Left)
	{
		for (int image_i = 0; image_i < m_iImage_Size; image_i++)
		{
			// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
			const int length = static_cast<int>(strlen(Letter_image_Left[image_i]));	
			const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;

			for (int i = 0; i < length; ++i)
			{
				if (m_pTransform->Get_Position().x + i <0
					|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
					|| (m_pTransform->Get_Position().y) + i < 0)
					continue;


				m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Letter_image_Left[image_i])[i];

				if (m_bSetGreen)
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Green;
				else
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
			}
		}
	}
#pragma endregion 

#pragma region Tower_Down
	else if (m_iCurrentTowerHead ==	Tower_Down)
	{
		for (int image_i = 0; image_i < 3; image_i++)
		{
			// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
			const int length = static_cast<int>(strlen(Letter_image_Down[image_i]));
			const int index = (ScreenSize.x * (m_pTransform->Get_Position().y + image_i)) + m_pTransform->Get_Position().x;

			for (int i = 0; i < length; ++i)
			{
				if (m_pTransform->Get_Position().x + i <0
					|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
					|| (m_pTransform->Get_Position().y) + i < 0)
					continue;


				m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = (Letter_image_Down[image_i])[i];

				if (m_bSetGreen)
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Green;
				else
					m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::White;
			}
		}
	}
#pragma endregion 

	return S_OK;
}



CMonster_Tower* CMonster_Tower::Create(GAME_OBJECT_DESC* _desc)
{
	CMonster_Tower* pInstance = new CMonster_Tower();

	if (FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CMonster_Tower");
		__debugbreak();
	}

	return pInstance;
}


void CMonster_Tower::Free()
{

	__super::Free();

	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::MONSTER, this);

	for (int i = 0; i < m_iImage_Size; i++)
	{
		delete[] Letter_image_Up[i];
		delete[] Letter_image_Right[i];
		delete[] Letter_image_Left[i];
	}

	for (int i =0; i<3; i++)
	{
		delete[] Letter_image_Down[i];
	}

	

	delete this;
}