#include "CollisionMgr.h"
#include "GameObject.h"

CCollision_Manager::CCollision_Manager()
	:m_arrCheck{}
{
}

CCollision_Manager::~CCollision_Manager()
{
}


HRESULT CCollision_Manager::Initialize()
{

	return S_OK;
}


void CCollision_Manager::Update()
{
	for(UINT iRow =0; iRow < (UINT)GROUP_TYPE::GROUP_END; iRow++)
	{
		
		for(UINT iCol = iRow; iCol <(UINT)GROUP_TYPE::GROUP_END; ++iCol)
		{
			if(m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}


void CCollision_Manager::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	
	const vector<CGameObject*>& vecLeft  = m_arrObjCollider[(UINT)_eLeft];
	const vector<CGameObject*>& vecRight = m_arrObjCollider[(UINT)_eRight];

	
	map<ULONGLONG, bool>::iterator iter; 

	for(size_t i=0; i< vecLeft.size(); i++)
	{
		////충돌체 create 안한거 거르기.(즉 CreateCollider를 보유하지않은것들)
		if (vecLeft[i]->Find_Component(TEXT("Com_Collider")) == nullptr)
		{
			continue; // i가 증가해서 다음으로감
		}


		for(size_t j=0; j< vecRight.size(); j++)
		{
			CCollider* pLeftCol =  static_cast<CCollider*>(vecLeft[i]->Find_Component(TEXT("Com_Collider")));
			CCollider* pRightCol = static_cast<CCollider*>(vecRight[j]->Find_Component(TEXT("Com_Collider")));


			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID; 

			ID.Left_id = pLeftCol->Get_ID();
			ID.Right_id = pRightCol->Get_ID();
			ID.ID;

			iter = m_mapCoIinfo.find(ID.ID);

			if (vecLeft[i] == vecRight[j])
			{
				continue; // 다시 증감자 문으로 감. 아래로 안가고 
			}


			// 충돌 정보가 미 등록 상태인 경우 등록 (충돌하지 않았다로) 즉 처음 맵에 insert 되는 경우
			
			if(m_mapCoIinfo.end() == iter)
			{
				m_mapCoIinfo.insert(make_pair(ID.ID, false));
				iter = m_mapCoIinfo.find(ID.ID);
			}


			if(isCollision(pLeftCol,pRightCol))
			{
				if (iter->second)
				{
					// 지금도 충돌중인데 이전에도 충돌하고 있는 경우
					vecLeft[i]->OnCollision(vecRight[j]);
					vecRight[j]->OnCollision(vecLeft[i]);
				}
				else
				{
					// 이전에는 충돌하지 않았다.
					vecLeft[i]->OnCollisionEnter(vecRight[j]);
					vecRight[j]->OnCollisionEnter(vecLeft[i]);
					iter->second = true;
				}
			}
			

			else
			{
				// 현재 충돌 안할 경우
				if(iter->second)
				{
					// 이전에는 충돌하고 있었다.
					vecLeft[i]->OnCollisionExit(vecRight[j]);
					vecRight[j]->OnCollisionExit(vecLeft[i]);
					iter->second = false;
				}
			}

		}
	}

}

bool CCollision_Manager::isCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	bool leftResult = _pLeftCol->Intersect(_pRightCol);
	bool rightResult = _pRightCol->Intersect(_pLeftCol);

	return leftResult || rightResult;	
}

CGameObject* CCollision_Manager::Find_GameObject(GROUP_TYPE _GroupType, CGameObject* _pGameObject)
{

	for (auto& iter : m_arrObjCollider[(UINT)_GroupType])
	{
		if (iter == _pGameObject)
			return _pGameObject;
	}


	return nullptr;
}


HRESULT CCollision_Manager::Add_ObjCollider(GROUP_TYPE _GroupType, CGameObject* _pGameObject)
{
	if (_pGameObject == nullptr || (UINT)_GroupType >= (UINT)GROUP_TYPE::GROUP_END)
		return E_FAIL;

	if (Find_GameObject(_GroupType, _pGameObject) == nullptr)
	{
		m_arrObjCollider[(UINT)_GroupType].push_back(_pGameObject);	
	}


	return E_NOTIMPL;
}

HRESULT CCollision_Manager::Sub_ObjCollider(GROUP_TYPE _GroupType, CGameObject* _pGameObject)
{
	if (_pGameObject == nullptr || (UINT)_GroupType >= (UINT)GROUP_TYPE::GROUP_END)
		return E_FAIL;


	if (m_arrObjCollider[(UINT)_GroupType].size() > 0)
	{

		for (auto iter = m_arrObjCollider[(UINT)_GroupType].begin(); iter != m_arrObjCollider[(UINT)_GroupType].end();)
		{
			if (*iter == _pGameObject)
			{
				m_arrObjCollider[(UINT)_GroupType].erase(iter);
				return S_OK;
			}

			else
				iter++;
		}
	}

	return S_OK;
}



void CCollision_Manager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용 

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if(iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft; 
	}

	if(m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}

	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}


}




CCollision_Manager* CCollision_Manager::Create()
{
	CCollision_Manager* pInstance = new CCollision_Manager(); 

	if(pInstance == nullptr)
	{
		MSG_BOX("Failed to Created : Collision_Manager");
		__debugbreak(); 
	}

	return pInstance;

}


void CCollision_Manager::Free()
{





	delete this;
}