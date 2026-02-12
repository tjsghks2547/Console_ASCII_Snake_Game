#pragma once

#include "Component.h"



BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
private:
	CTransform();
	virtual ~CTransform(); 

public:
	virtual HRESULT Initialize() override;

public:
	void Go_Right(float _fTimedelta); 
	void Go_Right_Up_Diagonal(float _fTimedelta);	
	void Go_Right_Down_Diagonal(float _fTimedelta);
	
	void Go_Left(float _fTimedelta);
	void Go_Left_Up_Diagonal(float _fTimedelta);
	void Go_Left_Down_Diagonal(float _fTimedelta);
	void Go_Up(float _fTimedelta);
	void Go_Down(float _fTimedelta);
	void Set_Speed(float _fSpeed) { m_fSpeedPerSec = _fSpeed; }

	void Set_Size(Vector2 _size) { m_vSize= _size; }
	Vector2 Get_Size() { return m_vSize; }
	Vector2 Get_Dir() { return m_vDir; }
	void	Set_Dir(int _xDir, int _yDir) { m_vDir.x = _xDir, m_vDir.y = _yDir; }
	Vector2 Get_Position() { return m_vPosition; }
	void    Set_Position(float _x, float _y);
	void    Set_Position(int _x, int _y);

private:

	Vector2 m_vSize = { 0,0 };
	Vector2 m_vPosition = { 0,0 };
	Vector2 m_vDir      = { 0,0 };
	
	float   m_fPosition_x = 0.f; 
	float   m_fPosition_y = 0.f;

	
	float   m_fSpeedPerSec = { 15.f };

public:
	static CTransform* Create();
	virtual void Free() override; 

};

END