#include "Event_Manager.h"
#include "GameObject.h"
#include "GameInstance.h"

CEvent_Manager::CEvent_Manager()
{
    m_pGameInstance = m_pGameInstance->GetInstance();
}

CEvent_Manager::~CEvent_Manager()
{
}



void CEvent_Manager::Update()
{
    // 여기서 먼저 해줘야겠네. 

    _uint iLevelIndex;
   

    for(int i=0; i<m_vecDelete.size(); i++)
    {
        iLevelIndex = m_vecDelete[i].first->iLevelIndex;
        const wstring& LayerTag = m_vecDelete[i].first->strLayerTag;


        m_pGameInstance->Sub_GameObject_To_Layer(iLevelIndex, LayerTag, m_vecDelete[i].second);
        m_vecDelete[i].second->Free(); 
    }

    for (int i = 0; i < m_vecDelete.size(); i++)
    {
        delete m_vecDelete[i].first;
    }

    m_vecDelete.clear(); 

}

HRESULT CEvent_Manager::Add_DeleteObject(Event_DeleInfo* _Desc, CGameObject* _pGameObject)
{

    m_vecDelete.emplace_back(make_pair(_Desc,_pGameObject));

    //m_pGameInstance->Sub_GameObject_To_Layer(_iLevelIndex,_strLayerName, _pGameObject); // 아 이게 update로 가야하네.
    return S_OK;
}


CEvent_Manager* CEvent_Manager::Create()
{
    CEvent_Manager* pInstance = new CEvent_Manager();

    if(pInstance == nullptr)
    {
        return nullptr;
    }

    return pInstance; 
}

void CEvent_Manager::Free()
{
    m_vecDelete.clear(); 

    delete this; 
}
