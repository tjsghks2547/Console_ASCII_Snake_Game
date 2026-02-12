#pragma once

#include "Engine_Defines.h"
#include "Engine_Macro.h"

BEGIN(Engine)

class ENGINE_DLL CInput_Manager
{
	struct KeyState
	{
		// 현재 키가 눌렸는지.
		bool isKeyDown = false;

		// 이전에 키가 눌렸는지.
		bool wasKeyDown = false;
	};

private:
	CInput_Manager();
	~CInput_Manager(); 


public:
	HRESULT Init(); 
	void Priority_Update(float _fTimeDelta);
	void Update(float _fTimeDelta);
	void Late_Update(float _fTimeDelta);
	void SavePreviousInputStates();

	// 입력 확인 함수.	
	// 이전에 입력이 안됐는데, 현재 입력이 됐으면 1번 호출.	
	bool GetKeyEnter(int keyCode);

	// 이전에 입력이 됐는데, 현재 입력이 취소됐으면 1번 호출.
	bool GetKeyRelease(int keyCode);

	// 현재 눌려있으면 반복 호출.
	bool GetKeyPressed(int keyCode);

private:
	// 키 상태 저장용 배열.
	KeyState keyStates[255] = { };	


public:
	static CInput_Manager* Create(); 
	void Free(); 


};

END