#include "GameObject.h"
#include "Component.h"
#include "GameInstance.h"
#include "Device.h"


CGameObject::CGameObject(const char* _name)
	:name(_name)
{

}

CGameObject::~CGameObject()
{
}


HRESULT CGameObject::Initialize(GAME_OBJECT_DESC* _desc)
{
	m_pGameInstance = CGameInstance::GetInstance();
	m_pDevice = m_pGameInstance->Get_Device_Ptr();

	m_pTransform = CTransform::Create();
	if (m_pTransform == nullptr)
		return E_FAIL; 

	
	m_mapComponents.emplace(TEXT("Transform"), m_pTransform);
	

	return S_OK; 
}

void CGameObject::Priority_Update(float _fTimeDelta)
{
	
}


void CGameObject::Update(float _fTimeDelta)
{


}

void CGameObject::Late_Update(float _fTimeDelta)
{


}
 
HRESULT CGameObject::Render()
{
	

	return S_OK;
}

CComponent* CGameObject::Find_Component(const wstring& _CommponentName)
{
	if(m_mapComponents.find(_CommponentName) != m_mapComponents.end())
	{
		return m_mapComponents[_CommponentName];
	}

	MSG_BOX("Failed to Find : _CommponentName");

	return nullptr;
}


CGameObject* CGameObject::Create(GAME_OBJECT_DESC* _desc, const char* _name)
{
	CGameObject* pInstance = new CGameObject(_name);	

	if(FAILED(pInstance->Initialize(_desc)))
	{
		MSG_BOX("Failed to Created : CGameObject");		
		delete pInstance;
		__debugbreak(); 
	}

	return pInstance; 

}

void CGameObject::Free()
{
	//delete[] name; 

	//delete[] image;	
	
	for(auto& pair : m_mapComponents)
	{
		// Todo : 이거 해줘야함.
		pair.second->Free();
	}

	m_mapComponents.clear();
	
}





