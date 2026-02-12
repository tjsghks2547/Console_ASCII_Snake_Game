#include "Renderer.h"
#include "GameObject.h"

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}

HRESULT CRenderer::Initialize()
{


	return S_OK;
}




HRESULT CRenderer::Add_RenderGroup(RENDER_GROUP eRenderGroupID, CGameObject* pGameObject)
{
	if (pGameObject == nullptr || eRenderGroupID >= RG_END)
	{
		__debugbreak(); 
		return E_FAIL;
	}

	m_RenderObjects[eRenderGroupID].push_back(pGameObject);


	return S_OK;
}



HRESULT CRenderer::Render()
{

	if (FAILED(Render_BackGround()))
	{
		__debugbreak();
		return E_FAIL;
	}


	if (FAILED(Render_Actor()))
	{
		__debugbreak();
		return E_FAIL; 
	}

	if (FAILED(Render_UI()))
	{
		__debugbreak();
		return E_FAIL;
	}


	return S_OK;
}


HRESULT CRenderer::Render_BackGround()
{
	for (auto& pRenderObject : m_RenderObjects[RG_BACKGROUND])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;
	}

	m_RenderObjects[RG_BACKGROUND].clear();

	return S_OK;
}

HRESULT CRenderer::Render_Actor()
{
	for (auto& pRenderObject : m_RenderObjects[RG_ACTOR])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL; 
	}

	m_RenderObjects[RG_ACTOR].clear();	

	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	for (auto& pRenderObject : m_RenderObjects[RG_UI])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;

	}

	m_RenderObjects[RG_UI].clear();	

	return S_OK;	
}


CRenderer* CRenderer::Create()
{
	CRenderer* pInstance = new CRenderer(); 

	if(FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : Renderer");
		delete pInstance;

		__debugbreak();
	
	}

	return pInstance;
}


void CRenderer::Free()
{
	delete this; 
}