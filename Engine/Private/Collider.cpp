#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
    :m_iID(g_iNextID++)
{
}


CCollider::~CCollider()
{

}

HRESULT CCollider::Initialize(CGameObject* pOwner)
{

    m_pGameObejct = pOwner; 

    return S_OK;    
}

bool CCollider::Intersect(CCollider* pCollider)
{
    //여기서 자기자신 부모 GameObject를 알고 있어야하네. 
    
    CTransform* pTransfrom      = static_cast<CTransform*>(m_pGameObejct->Find_Component(TEXT("Transform"))); 
    CTransform* pOtherTransfrom = static_cast<CTransform*>(pCollider->Get_Owner()->Find_Component(TEXT("Transform")));


    Vector2 Position = pTransfrom->Get_Position();
    Vector2 Size     = pTransfrom->Get_Size();

    Vector2 otherPosition = pOtherTransfrom->Get_Position();   
    Vector2 otherSize     = pOtherTransfrom->Get_Size();
    


    return (Position.x < otherPosition.x + otherSize.x) &&
        (Position.x + Size.x > otherPosition.x) &&
        (Position.y < otherPosition.y + otherSize.y) &&
        (Position.y + Size.y > otherPosition.y);
  
}


CCollider* CCollider::Create(CGameObject* pOwner)
{
    CCollider* pInstance = new CCollider();
    
    if(FAILED(pInstance->Initialize(pOwner)))
    {
        MSG_BOX("Failed to Created : Collider");
        __debugbreak();
    }

    return pInstance; 
}

void CCollider::Free()
{

    delete this;
}
