#pragma once

#include "GameObject.h"	


enum PlayerDir
{
	NONE = -1,
	GO_RIGHT,
	GO_LEFT,
	GO_UP,
	GO_DOWN,
};

BEGIN(Engine)
class CCollider;
END


class CPlayer final: public CGameObject
{
private:
	CPlayer();
	virtual ~CPlayer() = default;



public:
	
	virtual HRESULT Initialize(GAME_OBJECT_DESC* _desc) override;


	virtual void Priority_Update(float _fTimeDelta) override;
	virtual void Update(float _fTimeDelta) override;
	virtual void Late_Update(float _fTimeDelta) override;
	virtual HRESULT Render() override;


public:
	HRESULT Ready_Components();

	virtual void OnCollisionEnter(CGameObject* _pOther) override;
	virtual void OnCollision(CGameObject* _pOther) override;
	virtual void OnCollisionExit(CGameObject* _pOther) override;

	void Set_GameStatue(bool _OnOff) { m_bGameEnd = _OnOff; }
	bool Get_GameStatus() { return m_bGameEnd; }
	int Get_Exp() { return m_iExp; }

private:
	
	int m_iPreDir = -1; 
	int m_iCurrentDir = -1; 
	// ²¿¸®µé 
	deque<class CPlayerTail*> m_dequeTail;
	deque<pair<int, int>> m_dequeMoveHistroy; 
	
	Vector2 m_vPrePos = { 0,0 };

	CCollider* m_pCollider = nullptr; 

	bool m_bGameEnd = false; 

	bool m_bTailGainEffectOnOff = false; 

	float m_fAccDeltaTime = 0.f; 

	int m_iExp = 0; 



public:
	static CPlayer* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override; 



};



