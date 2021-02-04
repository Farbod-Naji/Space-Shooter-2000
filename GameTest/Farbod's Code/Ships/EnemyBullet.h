#pragma once
#include "../Object.h"

class EnemyBullet : public Object
{
public:
	EnemyBullet(unsigned int laneX, unsigned int laneY, bool facingRight, float distance);

	void Update(float dt);

	void Render();

	const bool IsStopped() { return m_hitTheWall; };
private:

	bool m_facingRight;

	float CollisionPoint() override;

	bool m_hitTheWall;

};

