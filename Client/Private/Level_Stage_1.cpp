#include "Level_Stage_1.h"
#include "GameInstance.h"
#include "Client_Defines.h"
#include "Level_Logo.h"
#include "Device.h"
#include "Layer.h"

#pragma region UI 
#include "Game_ExpBar.h"
#include "Speed_Up.h"
#pragma endregion 

#pragma region Actor include
#include "Player.h"
#include "Wall.h"
#include "Ground.h"
#include "TailPlus_Item.h"
#include "Monster_Tower.h"
#include "Boss_Monster.h"
#include "Attack_item.h"
#pragma endregion 



using namespace Client;

CLevel_Stage_1::CLevel_Stage_1()
{


}

CLevel_Stage_1::~CLevel_Stage_1()
{


}

HRESULT CLevel_Stage_1::Initialize()
{


	if (FAILED(Ready_Layer_Player(TEXT("Player"))))
	{
		MSG_BOX("Failed to Ready Layer Player ");
		__debugbreak();
	}

	if (FAILED(Ready_Layer_Structure(TEXT("Structure"))))
	{
		MSG_BOX("Failed to Ready Layer Structure ");
		__debugbreak();
	}

	if (FAILED(Ready_Layer_Item(TEXT("Item"))))
	{
		MSG_BOX("Failed to Ready Layer Item ");
		__debugbreak();
	}

	if (FAILED(Ready_Layer_Monster(TEXT("Monster"))))
	{
		MSG_BOX("Failed to Ready Layer Monster ");
		__debugbreak();
	}


	if (FAILED(Ready_Layer_UI(TEXT("UI"))))	
	{
		MSG_BOX("Failed to Ready Layer UI ");	
		__debugbreak();	
	}
	
	m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TAIL);
	m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BULLET);
	m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	m_pGameInstance->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::OBJECT);

	m_pGameInstance->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::OBJECT);
	m_pGameInstance->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BULLET);
	m_pGameInstance->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);

	m_pGameInstance->CheckGroup(GROUP_TYPE::OBJECT, GROUP_TYPE::BULLET);

	m_pGameInstance->CheckGroup(GROUP_TYPE::TAIL, GROUP_TYPE::BULLET);

	Load_Map("Map1.txt");

	return S_OK;
}

Vector2 CLevel_Stage_1::GetRandomPos(int minX, int maxX, int minY, int maxY)
{
	return {
		minX + rand() % (maxX - minX + 1),
		minY + rand() % (maxY - minY + 1)
	};
}



void CLevel_Stage_1::Update(float _fTimeDelta)
{
	m_fItemAccDeltaTime += *(m_pGameInstance->Get_DeltaTime_ptr());
	m_fTowerAccDeltaTime += *(m_pGameInstance->Get_DeltaTime_ptr());
	m_fAttack_ItemAccDeltaTime += *(m_pGameInstance->Get_DeltaTime_ptr());

	//플레이어찾기 
	CPlayer* pPlayer = static_cast<CPlayer*>(m_pGameInstance->Find_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("Player"), "Player"));


	if(m_pGameInstance->GetKeyEnter(VK_RETURN) && pPlayer->Get_GameStatus())
	{
		m_pGameInstance->Reset();
		m_pGameInstance->Set_Level(LEVEL_LOGO, CLevel_Logo::Create());
		return;
	}
	

#pragma region 꼬리 길어지는 아이템

	if(m_pGameInstance->Find_Layer(LEVEL_STAGE_1, TEXT("Item"))!= nullptr)
	{
		m_iCurrentTailItemCount = m_pGameInstance->Find_Layer(LEVEL_STAGE_1, TEXT("Item"))->Get_GameObject_List().size();
	}
	
	// 여기서 렌덤으로 아이템 생성되도록 2초에 1개씩  + 최대개수 제한하기.
	if(m_fItemAccDeltaTime >=2.f && m_iCurrentTailItemCount <= 20)
	{
		// 여기에 하나 추가해야할점이  해당 위치에 뭐가 있을 시 소환못하게 해야할듯
		GAME_OBJECT_DESC desc = {};
		

		// y는 41이였음 x는 230 
		Vector2 Position = GetRandomPos(3, 160, 2, 40);
		desc.x = Position.x; 
		desc.y = Position.y;

		int index = m_pDevice->Get_ScreenSize().x * Position.y + Position.x;
		
		if (m_pDevice->Get_Frame()->charInfoArray[index].Char.AsciiChar == ' ')
		{
			m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
				TEXT("Item"),
				CTailPlus_Item::Create(&desc),
				nullptr);
		}

		else
			int a = 4; 

		m_fItemAccDeltaTime = 0.f;
	}

#pragma endregion 

	

#pragma region 포탑 타워 생산 
	if (m_pGameInstance->Find_Layer(LEVEL_STAGE_1, TEXT("Tower")) != nullptr)
	{
		m_iCurrentTowerCount = m_pGameInstance->Find_Layer(LEVEL_STAGE_1, TEXT("Tower"))->Get_GameObject_List().size();
	}


	// 여기서 렌덤으로 아이템 생성되도록 2초에 1개씩  + 최대개수 제한하기.
	if (m_fTowerAccDeltaTime >= 2.f && m_iCurrentTowerCount <= 8)
	{
		// 여기에 하나 추가해야할점이  해당 위치에 뭐가 있을 시 소환못하게 해야할듯
		GAME_OBJECT_DESC desc = {};

		
		// y는 41이였음 x는 230 
		Vector2 Position = GetRandomPos(10, 180, 10, 40);
		desc.x = Position.x;
		desc.y = Position.y;

		int index = m_pDevice->Get_ScreenSize().x * Position.y + Position.x;

		if (m_pDevice->Get_Frame()->charInfoArray[index].Char.AsciiChar == ' ')
		{
			m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
				TEXT("Tower"),
				CMonster_Tower::Create(&desc),
				nullptr);
		}

		else
			int a = 4;

		m_fTowerAccDeltaTime = 0.f;
	}
	
#pragma endregion 



#pragma region 공격 아이템 
	if (m_pGameInstance->Find_Layer(LEVEL_STAGE_1, TEXT("Item_Attack")) != nullptr)
	{
		m_iCurrentAttack_ItemCount = m_pGameInstance->Find_Layer(LEVEL_STAGE_1, TEXT("Item_Attack"))->Get_GameObject_List().size();
	}

	// 여기서 렌덤으로 아이템 생성되도록 2초에 1개씩  + 최대개수 제한하기.
	if (m_fAttack_ItemAccDeltaTime >= 3.f && m_iCurrentAttack_ItemCount <= 10)
	{
		// 여기에 하나 추가해야할점이  해당 위치에 뭐가 있을 시 소환못하게 해야할듯
		GAME_OBJECT_DESC desc = {};


		// y는 41이였음 x는 230 
		Vector2 Position = GetRandomPos(3, 160, 20, 30);
		desc.x = Position.x;
		desc.y = Position.y;

		int index = m_pDevice->Get_ScreenSize().x * Position.y + Position.x;

		if (m_pDevice->Get_Frame()->charInfoArray[index].Char.AsciiChar == ' ')
		{
			m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
				TEXT("Item_Attack"),
				CAttack_item::Create(&desc),
				nullptr);
		}

		else
			int a = 4;

		m_fAttack_ItemAccDeltaTime = 0.f;
	}

#pragma endregion 


}



void CLevel_Stage_1::Late_Update()
{

	//여기서 렌더그룹에 넣는역할이였음. 



}

void CLevel_Stage_1::Load_Map(const char* filename)
{
	// 파일로드 
	// 최종 파일 경로 만들기 ("../Assets/filename")

	char path[2048] = {};
	sprintf_s(path, 2048, "../Map/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt"); // 열기 실패하면 file에 nullptr가 들어감


	// 예외 처리 
	if (!file)
	{
		// 표준 오류 콘솔 활용
		std::cerr << "Failed to opent map file";

		// 디버스 모드에서 중단점으로 중단해주는 기능
		__debugbreak();
	}

	// 맵 읽기 

	// 맵 크기 파악 : File Position 포인터를 파일의 끝으로 이동 
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기. 
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1]; // null 문자 때문에 +1


	// 데이터 읽기. 
	size_t readSize = fread(data, sizeof(char), fileSize, file);


	// Test: 읽어온 데이터 임시로 출력.  
	//std::cout << data; 


	// 읽어온 문자열을 분석(파싱-parcing)해서 출력.
	// 인덱스를 사용해 한문자씩 읽기. 

	int index = 0;

	// 객체를 생성할 위치 값
	Vector2 position;



	while (true)
	{
		// 종료조건
		if (index >= fileSize)
		{
			break;
		}

		// 캐릭터 읽기
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			//std::cout << "\n"
			// y좌표는 하나 늘리고 , x 좌표 초기화
			++position.y;
			position.x = 0;
			continue;
		}

		/*
		 # : 벽 (Wall)
		 . : 바닥 (Ground)
		 p : 플레이어 (Player)
		 b : 박스(Box)
		 t : 타겟(Target)

		 */

		 // 한 문자씩 처리
		switch (mapCharacter)
		{
		case '#':
			//std::cout << "#";
			m_pGameInstance->Add_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("Structure"), CWall::Create(), &position);
			break;

		case '1':
			//m_pGameInstance->Add_GameObject_To_Layer(LEVEL_STAGE_1, TEXT("Structure"), CGround::Create(), &position);
			break;

		case '5':
		{
			int a = 4; 
		}
			//std::cout << "P";
			//플레이어도 이동가능함.
			//플레이어도 옮겨졌을 때 그 밑에 땅이 있어야함.

			//AddNewActor(new Player(position));
			//AddNewActor(new Ground(position));
			break;

		case 'b':
			//std::cout << "B";
			// 박스는 이동 가능함. 
			// 박스가 옮겨졌을 때 그 밑에 땅이 있어야함.
			//AddNewActor(new Box(position));
			//AddNewActor(new Ground(position));
			break;

		case 't':
			//std::cout << "T";
			//AddNewActor(new Target(position));
			//AddNewActor(new Ground(position));
			//targetScore++;
			break;

		default:
			break;
		}

		// x 좌표 증가 처리
		++position.x;
	}


	// 사용한 버퍼 해제.
	delete[] data;


	// 파일이 정상적으로 열렸으면 닫기. 
	fclose(file);







}

HRESULT CLevel_Stage_1::Ready_Layer_Player(const wchar_t* pLayerTag)	
{

	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		pLayerTag,
		CPlayer::Create(),
		nullptr);

	return S_OK;
}

HRESULT CLevel_Stage_1::Ready_Layer_Item(const wchar_t* pLayerTag)
{
	/*m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		pLayerTag,
		CTailPlus_Item::Create(),
		nullptr);*/


	return S_OK;	
}

HRESULT CLevel_Stage_1::Ready_Layer_Monster(const wchar_t* pLayerTag)
{

	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		pLayerTag,
		CBoss_Monster::Create(),	
		nullptr);

	return S_OK;	
}

HRESULT CLevel_Stage_1::Ready_Layer_UI(const wchar_t* pLayerTag)
{
	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		pLayerTag,
		CGame_ExpBar::Create(),
		nullptr);

	m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
		pLayerTag,
		CSpeed_Up::Create(),
		nullptr);



	return S_OK;
}

HRESULT CLevel_Stage_1::Ready_Layer_Structure(const wchar_t* pLayerTag)
{

	//m_pGameInstance->Add_GameObject_To_Layer(LEVEL::LEVEL_STAGE_1,
	//	pLayerTag,
	//	CMonster_Tower::Create(),
	//	nullptr);


		
	return S_OK;
}


CLevel_Stage_1* CLevel_Stage_1::Create()
{
	CLevel_Stage_1* pInstance = new CLevel_Stage_1();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : Level_Stage_1");
		__debugbreak();
	}
	return pInstance;

}

void CLevel_Stage_1::Free()
{
	__super::Free();

	delete this;
}