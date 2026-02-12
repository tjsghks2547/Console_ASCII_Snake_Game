#pragma once

#include "GameObject.h"	

BEGIN(Engine)
class CCollider;
END

class CBoss_Monster final : public CGameObject
{
	enum Tower_Rotation
	{
		Tower_Up,
		Tower_Down,
		Tower_Right,
		Tower_Left,
	};


private:
	CBoss_Monster();
	virtual ~CBoss_Monster() = default;

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

private:
	CCollider* m_pCollider;

private:
	bool  m_bSetGreen = false;
	int   m_iImage_Size = 15;
	int   m_iHp = 3; 
	char* Letter_image[100];

	bool   m_bBossHurtEnter = false;
	float  m_fBossHurtCool = 0.f; 
	


	deque<class CTower_projectile*> m_dequeBullet;

	int m_iCurrentTowerHead = 0;
	int m_iPreTowerHead = 0;
	int m_iRandomMoveNumber = 0;


	float m_fAccumulatedTimeDelta = 0.f;
	float m_fBulletAccumulatedTimeDelta = 0.f;


	int GetRandomX(int minX, int maxX)
	{
		return {
			minX + rand() % (maxX - minX + 1),
		};
	}

private:
	bool m_bDead = false;

public:
	static CBoss_Monster* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;



};



