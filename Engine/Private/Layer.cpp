#include "Layer.h"
#include "GameObject.h"

CLayer::CLayer()
{
}

void CLayer::Priority_Update(float _fTimeDelta)
{
	for(auto& iter : m_vecGameObject)
	{
		iter->Priority_Update(_fTimeDelta);
	}
}

void CLayer::Update(float _fTimeDelta)
{
	for (auto& iter : m_vecGameObject)
	{
		iter->Update(_fTimeDelta);
	}
}

void CLayer::Late_Update(float _fTimeDelta)
{
	for (auto& iter : m_vecGameObject)
	{
		iter->Late_Update(_fTimeDelta);
	}
}

HRESULT CLayer::Add_GameObject(CGameObject* _pGameObject)
{
	m_vecGameObject.emplace_back(_pGameObject);

	return S_OK;
}

CLayer* CLayer::Create()
{
	CLayer* pInstance = new CLayer(); 

	return pInstance;
}

void CLayer::Free()
{
	for(auto& iter : m_vecGameObject)
	{
		iter->Free();
	}

	m_vecGameObject.clear();
	
	delete this; 

}


