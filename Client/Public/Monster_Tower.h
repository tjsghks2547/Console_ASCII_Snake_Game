#pragma once

#include "GameObject.h"	

BEGIN(Engine)
class CCollider;
END

class CMonster_Tower final : public CGameObject
{
	enum Tower_Rotation
	{
		Tower_Up,
		Tower_Down,
		Tower_Right,
		Tower_Left,
	};


private:
	CMonster_Tower();
	virtual ~CMonster_Tower() = default;

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
	int   m_iImage_Size = 2;

	char* Letter_image_Up[2];
	char* Letter_image_Right[2];
	char* Letter_image_Left[2];
	char* Letter_image_Down[3];


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
	static CMonster_Tower* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;



};



