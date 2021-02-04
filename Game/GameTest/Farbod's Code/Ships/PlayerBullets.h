#pragma once
#include "../Object.h"

class PlayerBullets : public Object
{
public:
	PlayerBullets(unsigned int laneX, unsigned int laneY, int laneXSpeed, int laneYSpeed);

	void Update(float dt);

	void Render();

	float CollisionPoint() override;

private:
	
	bool m_facingRight;
};

