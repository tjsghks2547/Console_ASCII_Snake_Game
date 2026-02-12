#include "Input_Manager.h"

CInput_Manager::CInput_Manager()
{

}

CInput_Manager::~CInput_Manager()
{

}


HRESULT CInput_Manager::Init()
{
	
	return S_OK;
}

void CInput_Manager::Priority_Update(float _fTimeDelta)
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown
			= (GetAsyncKeyState(ix) & 0x8000) > 0 ? true : false;
	}
}


void CInput_Manager::Update(float _fTimeDelta)
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown
			= (GetAsyncKeyState(ix) & 0x8000) > 0 ? true : false;
	}


}


void CInput_Manager::SavePreviousInputStates()
{
	// 현재 입력 값을 이전 입력 값으로 저장.
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].wasKeyDown
			= keyStates[ix].isKeyDown;
	}
}



void CInput_Manager::Late_Update(float _fTimeDelta)
{
	SavePreviousInputStates();
}

bool CInput_Manager::GetKeyEnter(int keyCode)
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].wasKeyDown;
}

bool CInput_Manager::GetKeyRelease(int keyCode)
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].wasKeyDown;
}

bool CInput_Manager::GetKeyPressed(int keyCode)
{
	return keyStates[keyCode].isKeyDown;	
}



CInput_Manager* CInput_Manager::Create()
{
	CInput_Manager* pInstance = new CInput_Manager(); 

	if(FAILED(pInstance->Init()))
	{
		MSG_BOX("Failed to Created : InputManager");
		__debugbreak(); 
	}

	return pInstance; 

}

void CInput_Manager::Free()
{
	delete this; 
}