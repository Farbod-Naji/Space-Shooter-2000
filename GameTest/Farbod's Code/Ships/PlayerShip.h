#pragma once

#include "../Object.h"
#include "PlayerBullets.h"

class PlayerShip : public Object
{
public:
	class PlayerShip();

	void Update(float dt);

	void Render();

	std::vector <PlayerBullets *> Shoot();

	float CollisionPoint() override;

private:
	float m_shottingTimer;
	float m_bulletCoolDownTimer;
	
	bool m_canShoot;
};

