#pragma once
#include <vector>

#include "../Object.h"
#include "EnemyBullet.h"



class EnemyShips : public Object
{
public:
	EnemyShips(unsigned int laneX, unsigned int laneY);
	
	std::vector <EnemyBullet*> Update(float dt, unsigned int playerTileX, unsigned int playerTileY);

	void Render();

	float CollisionPoint() override;

private:
	
	void AIDecide(unsigned int playerTileX, unsigned int playerTileY);

	bool m_facingRight;

	float m_bulletCoolDown;
	float m_shootingTimer;

	float m_height = 40.0f;
};

