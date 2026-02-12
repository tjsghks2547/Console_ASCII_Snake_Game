#include "Player.h"
#include "Device.h"
#include "GameInstance.h"
#include "PlayerTail.h"
#include "Client_Defines.h"
#include "Collider.h"
#include "Game_Over.h"



CPlayer::CPlayer()
{
	name = "Player";
}

HRESULT CPlayer::Initialize(GAME_OBJECT_DESC* _desc)
{
	__super::Initialize(_desc);	
	
	Ready_Components();

	image = "@";
	m_pTransform->Set_Position(3.f, 3.f);
	
	const int length = static_cast<int>(strlen(image));

	m_pTransform->Set_Size({ length ,1 });

	
	CPlayerTail* pTail = CPlayerTail::Create();
	CPlayerTail* pTail2 = CPlayerTail::Create();
	CPlayerTail* pTail3 = CPlayerTail::Create();
	CPlayerTail* pTail4 = CPlayerTail::Create();

	// 초기 위치 설정해줘야 할듯 


	//// 앞의 물체의 진행방향을 기준으로 해당 꼬리의 움직임 설계 

	m_dequeTail.push_back(pTail);
	m_dequeTail.push_back(pTail2);	
	m_dequeTail.push_back(pTail3);
	m_dequeTail.push_back(pTail4);

	


	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		TEXT("Tail"),
		pTail,
		nullptr);

	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		TEXT("Tail"),
		pTail2,
		nullptr);


	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		TEXT("Tail"),
		pTail3,
		nullptr);


	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		TEXT("Tail"),
		pTail4,
		nullptr);




	return S_OK;
}

void CPlayer::Priority_Update(float _fTimeDelta)
{


	// W 누르면서 D 누르면 왼쪽에서 오른쪽으로 바로 전환되네
	// 이거 나중에 막기
	

}

void CPlayer::Update(float _fTimeDelta)
{
	m_vPrePos = m_pTransform->Get_Position();	
	m_iPreDir = m_iCurrentDir; 



	// 여기서 움직이기 
	if (GetKeyState('W') & 0x8000 
		&& m_iPreDir != PlayerDir::GO_DOWN
		&& !(GetKeyState('A') & 0x8000)
		&& !(GetKeyState('D') & 0x8000)
		&& !(GetKeyState('S') & 0x8000))
	{
		m_iCurrentDir = PlayerDir::GO_UP;
	}


	if (GetKeyState('S') & 0x8000
		&& m_iPreDir != PlayerDir::GO_UP
		&& !(GetKeyState('A') & 0x8000)
		&& !(GetKeyState('D') & 0x8000)
		&& !(GetKeyState('W') & 0x8000))
	{
		m_iCurrentDir = PlayerDir::GO_DOWN;
	}


	if(GetKeyState('D') & 0x8000 
		&& m_iPreDir != PlayerDir::GO_LEFT
		&& !(GetKeyState('A') & 0x8000)
		&& !(GetKeyState('S') & 0x8000)
		&& !(GetKeyState('W') & 0x8000))
	{
		m_iCurrentDir = PlayerDir::GO_RIGHT;
	}


	if (GetKeyState('A') & 0x8000 
		&& m_iPreDir != PlayerDir::GO_RIGHT
		&& !(GetKeyState('W') & 0x8000)
		&& !(GetKeyState('S') & 0x8000)
		&& !(GetKeyState('D') & 0x8000))
	{
		m_iCurrentDir = PlayerDir::GO_LEFT;
	}


	if (!m_bGameEnd)
	{
		switch (m_iCurrentDir)
		{
		case PlayerDir::GO_RIGHT:
			m_pTransform->Go_Right(_fTimeDelta);
			break;

		case PlayerDir::GO_LEFT:
			m_pTransform->Go_Left(_fTimeDelta);
			break;

		case PlayerDir::GO_UP:
			m_pTransform->Go_Up(_fTimeDelta);
			break;

		case PlayerDir::GO_DOWN:
			m_pTransform->Go_Down(_fTimeDelta);
			break;
		}
	}


	if(m_vPrePos!= m_pTransform->Get_Position())
	{
		m_dequeMoveHistroy.emplace_back(m_vPrePos.x, m_vPrePos.y);

		if(m_dequeMoveHistroy.size() > m_dequeTail.size()) // 한칸정도 더 저장하고 추가될 꼬리 위치 가져오기
		{
			m_dequeMoveHistroy.pop_front();
		}
	}


	int count = min((int)m_dequeTail.size(), (int)m_dequeMoveHistroy.size());

	for (int i = 0; i < count; ++i)
	{
		auto* pTransform =
			static_cast<CTransform*>(m_dequeTail[i]->Find_Component(TEXT("Transform")));

		pTransform->Set_Position(
			m_dequeMoveHistroy[i].first,
			m_dequeMoveHistroy[i].second);
	}

	// @Todo : 해야 될 것들 정리 
	// CollisionMgr과 wall 벽 만들기  - 충돌처리까지 완료 ( 끝 )
	// 맵 파일 불러오기 및 아이템 상호작용 하기 


	// 이펙트 onoff 관련
	if(m_bTailGainEffectOnOff)
	{
		m_fAccDeltaTime += _fTimeDelta;
		
		int index = 1; 
		for (auto& iter : m_dequeTail)
		{
			iter->Set_Color((int)(m_fAccDeltaTime * 15.f * index) % 5);
			
			index++;

		}


		if(m_fAccDeltaTime > 0.5f)
		{
			m_bTailGainEffectOnOff = false;
			m_fAccDeltaTime = 0.f;

			for (auto& iter : m_dequeTail)
			{
				iter->Set_Color(FOREGROUND_BLUE);
			}
			
		}
	}


	// 경험치 MAX일시 초기화 
	if(m_iExp >= 5)
	{
		m_iExp = 0; 
	}

}

void CPlayer::Late_Update(float _fTimeDelta)
{

	m_pGameInstance->Add_RenderGroup(RENDER_GROUP::RG_ACTOR, this);

}

HRESULT CPlayer::Render()
{
	Vector2 ScreenSize = m_pDevice->Get_ScreenSize();


	// 화면에 그릴 문자열 길이 ( x가 가로 , y가 세로 )
	const int length = static_cast<int>(strlen(image));
	const int index = (ScreenSize.x * m_pTransform->Get_Position().y) + m_pTransform->Get_Position().x;

	for (int i = 0; i < length; ++i)
	{
		/*if (m_pTransform->Get_Position().x + i <0
			|| (m_pTransform->Get_Position().x + i) > ScreenSize.x
			|| (m_pTransform->Get_Position().y) + i < 0)
			continue;*/

	
		m_pDevice->Get_Frame()->charInfoArray[index + i].Char.AsciiChar = image[i];
		m_pDevice->Get_Frame()->charInfoArray[index + i].Attributes = (WORD)Color::Red;
	}

	return S_OK;
}

HRESULT CPlayer::Ready_Components()
{
	m_pCollider = CCollider::Create(this);
	m_mapComponents.emplace(TEXT("Com_Collider"), m_pCollider);

	//m_pColliderCom->Set_Collider_Name("Player");
	m_pGameInstance->Add_ObjCollider(GROUP_TYPE::PLAYER, this);

	return S_OK;
}

void CPlayer::OnCollisionEnter(CGameObject* _pOther)
{
	if(_pOther->Get_Name() == "Wall")
	{
		// 여기서 게임종료 
		m_pGameInstance->Add_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("UI"), CGame_Over::Create(),nullptr);
		m_bGameEnd = true; 

	}


	if (_pOther->Get_Name() == "TailPlus_Item")
	{
		// 여기서 꼬리추가
		CPlayerTail* pTail = CPlayerTail::Create();	
		m_dequeTail.push_back(pTail);

		m_bTailGainEffectOnOff = true; 

		m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
			TEXT("Tail"),
			pTail,
			nullptr);

		m_iExp++;
	
	}

	if (_pOther->Get_Name() == "Monster_Tower")
	{
		// 여기서 게임종료 
		m_pGameInstance->Add_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("UI"), CGame_Over::Create(), nullptr);
		m_bGameEnd = true;
	}
	
	if (_pOther->Get_Name() == "Tail")
	{
		// 여기서 게임종료 
		m_pGameInstance->Add_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("UI"), CGame_Over::Create(), nullptr);
		m_bGameEnd = true;
	}


	int a = 4;
}

void CPlayer::OnCollision(CGameObject* _pOther)
{

	int a = 4;
}

void CPlayer::OnCollisionExit(CGameObject* _pOther)
{
	int a = 4; 
}



CPlayer* CPlayer::Create(GAME_OBJECT_DESC* _desc)
{
	CPlayer* pInstance = new CPlayer();

	if(FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : Player");
		__debugbreak();
	}

	return pInstance;
}


void CPlayer::Free()
{

	// 삭제하고 한번더 삭제되서 문제가 발생함
	//m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("BackGround"), this);	
	//m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::PLAYER, this);			


	//int size = m_dequeTail.size();
	//// 꼬리 다 정리해야함
	//for(int i=0; i< size; i++)
	//{
	//	m_dequeTail[i]->Free();
	//}

	m_pGameInstance->Sub_ObjCollider(GROUP_TYPE::PLAYER, this); 
	m_pGameInstance->Sub_GameObject_To_Layer(m_pGameInstance->Get_CurrentLevelIndex(), TEXT("Player"), this);


	__super::Free();

	delete this; 
}

