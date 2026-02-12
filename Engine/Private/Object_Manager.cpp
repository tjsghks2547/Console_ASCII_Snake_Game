#include "Object_Manager.h"
#include "Layer.h"
#include "GameObject.h"

CObject_Manager::CObject_Manager()
    :m_iNumLayers(0)
{
}

HRESULT CObject_Manager::Init(_uint _iNumLayers)
{
    m_pLayers = new map<const wstring, CLayer*>[_iNumLayers];

    m_iNumLayers = _iNumLayers;

    return S_OK;
}

void CObject_Manager::Priority_Update(float _fTimeDelta)
{
    for (_uint i = 0; i < m_iNumLayers; i++)
    {
        for (auto& pair : m_pLayers[i])
        {
            pair.second->Priority_Update(_fTimeDelta);
        }
    }

}


void CObject_Manager::Update(float _fTimeDelta)
{
    
    for(_uint i =0; i< m_iNumLayers; i++)
    {
        for(auto& pair : m_pLayers[i]) 
        {
            pair.second->Update(_fTimeDelta);
        }
    }
    
}


void CObject_Manager::Late_Update(float _fTimeDelta)
{
    for (_uint i = 0; i < m_iNumLayers; i++)
    {
        for (auto& pair : m_pLayers[i])
        {
            pair.second->Late_Update(_fTimeDelta);
        }   
    }   

}

void CObject_Manager::Clear(_uint _iLevelIndex)
{

    for(auto& iter : m_pLayers[_iLevelIndex])
    {
        iter.second->Free();
    }
  
    m_pLayers[_iLevelIndex].clear();

}



HRESULT CObject_Manager::Add_GameObejct_To_Layer(_uint _iLevelIndex, const wstring& _LayerName, CGameObject* _pGameObject, void* pArg)
{
   
    // 레이어가 이미 있을때 
    if(m_pLayers[_iLevelIndex].find(_LayerName) != m_pLayers[_iLevelIndex].end())
    {
        (m_pLayers[_iLevelIndex])[_LayerName]->Add_GameObject(_pGameObject);
        
    }


    else
    {
        CLayer* pLayer = CLayer::Create();

        pLayer->Add_GameObject(_pGameObject);
           
        (m_pLayers[_iLevelIndex]).emplace(_LayerName, pLayer);
    
    }



    if (pArg != nullptr)
    {
        Vector2* position = static_cast<Vector2*>(pArg);
        static_cast<CTransform*>(_pGameObject->Find_Component(TEXT("Transform")))->Set_Position(position->x, position->y);
    }


    return S_OK;
}

HRESULT CObject_Manager::Sub_GameObject_To_Layer(_uint _iLevelIndex, const wstring& _LayerName, CGameObject* _pGameObject, void* pArg)
{
    CLayer* pLayer = Find_Layer(_iLevelIndex, _LayerName);

    if (pLayer == nullptr)
        return E_FAIL;
   
    vector<class CGameObject*>& vectorGameObject = pLayer->Get_GameObject_List();

    for (auto iterator = vectorGameObject.begin(); iterator != vectorGameObject.end(); iterator++)
    {
        if (*iterator == _pGameObject)
        {
            vectorGameObject.erase(iterator); // 트러블 슈팅된 부분
            return S_OK;
        }
    }

    return S_OK;
}



CGameObject* CObject_Manager::Find_GameObject_To_Layer(_uint _iLevelIndex, const wstring& _LayerName, const char* _pGameObjectName)
{

    /* 사본객체를 추가할 레이어를 찾자. */
    CLayer* pLayer = Find_Layer(_iLevelIndex, _LayerName);

    if (pLayer == nullptr)
        return nullptr;

    vector<class CGameObject*>& vectorGameObject = pLayer->Get_GameObject_List();

    for(auto& iter : vectorGameObject)
    {
        if(iter->Get_Name() == _pGameObjectName)
        {
            return iter;
        }
    }

    return nullptr;
}


CLayer* CObject_Manager::Find_Layer(_uint iLevelIndex, const wstring& strLayerTag)
{
    auto	iter = m_pLayers[iLevelIndex].find(strLayerTag);

    if (iter == m_pLayers[iLevelIndex].end())
        return nullptr;

    return iter->second;
}



CObject_Manager* CObject_Manager::Create(_uint _iNumLayers)
{
    CObject_Manager* pInstance = new CObject_Manager();

    if(FAILED(pInstance->Init(_iNumLayers)))
    {
        MSG_BOX("Failed to Created Obj_Mgr");
        __debugbreak();
    }

    return pInstance;
}


void CObject_Manager::Free()
{
    for(_uint i=0; i< m_iNumLayers; i++)
    {
        for(auto& pair : m_pLayers[i])
        {
            pair.second->Free();
        }

        m_pLayers[i].clear();
    }
    
    delete[] m_pLayers; 
    delete this; 
}

void CObject_Manager::Destroy()
{
    for (_uint i = 0; i < m_iNumLayers; i++)
    {
        for (auto& pair : m_pLayers[i])
        {
            // 여기서 Free말고 다른거 해야할듯
            pair.second->Free();
        }

        m_pLayers[i].clear();
    }

    delete[] m_pLayers;
    delete this;
}
