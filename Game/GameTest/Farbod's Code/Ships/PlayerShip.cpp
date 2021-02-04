#include "stdafx.h"
#include "PlayerShip.h"
#include "../../App/app.h"

void DrawPoint(float x, float y);


Map* Object::m_map;

PlayerShip::PlayerShip() : Object (0,0) {
	m_canShoot = true;
	m_shottingTimer = 0.0;
	m_bulletCoolDownTimer = 0.5f;
}

void PlayerShip::Update(float dt) {
	//check so it does not leave the outer outline of the platfrom
	if ((Object::m_laneX == 0) && (Object::m_laneXSpeed < 0)) {
		Object::m_laneXSpeed = 0;
	}
	if ((Object::m_laneY == 0) && (Object::m_laneYSpeed < 0)) {
		Object::m_laneYSpeed = 0;
	}

	//check so it does not leave the inter outline of the platfrom
	if ((Object::m_laneX == (Object::m_map->m_numOfDivision - 1)) && (Object::m_laneXSpeed > 0)) {
		Object::m_laneXSpeed = 0;
	}
	if ((Object::m_laneY == (Object::m_map->m_numOfDivision - 1)) && (Object::m_laneYSpeed > 0)) {
		Object::m_laneYSpeed = 0;
	}

	m_laneX += m_laneXSpeed;
	m_laneY += m_laneYSpeed;
	
	m_laneXSpeed = 0;
	m_laneYSpeed = 0;
	
	if (!m_canShoot){
  		m_shottingTimer += dt;
		if (m_shottingTimer > m_bulletCoolDownTimer) {
 			m_shottingTimer = 0.0f;
			m_canShoot = true;
		}
	}

	return ;
}

std::vector <PlayerBullets *> PlayerShip::Shoot() {
	std::vector <PlayerBullets*> returnVal;
	
	if (m_canShoot) {
		returnVal.push_back(new PlayerBullets(Object::m_laneX + 1, Object::m_laneY, 1, 0));
		returnVal.push_back(new PlayerBullets(Object::m_laneX, Object::m_laneY + 1, 0, 1));
		m_canShoot = false;
	}

	return returnVal;
}

float PlayerShip::CollisionPoint() {
	return -1000000000;
}

void PlayerShip::Render() {
	if (!m_inLane){
		Tile* pointer = m_map->m_tiles[m_laneX][m_laneY];

		Point temp1 = pointer->m_BottomRight;
		Point temp2 = pointer->m_Right;
		Point temp3 = pointer->m_Top;
		Point temp4 = pointer->m_Left;
		Point temp5 = pointer->m_BottomLeft;
		Point temp6 = pointer->m_Center;

		#if APP_USE_VIRTUAL_RES		
			APP_VIRTUAL_TO_NATIVE_COORDS(temp1.m_x, temp1.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(temp2.m_x, temp2.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(temp3.m_x, temp3.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(temp4.m_x, temp4.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(temp5.m_x, temp5.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(temp6.m_x, temp6.m_y);
		#endif

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.70f, 0.10f); // Yellow
		glVertex2f(temp1.m_x, temp1.m_y);
		glVertex2f(temp2.m_x, temp2.m_y);
		glVertex2f(temp3.m_x, temp3.m_y);
		glVertex2f(temp6.m_x, temp6.m_y);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.70f, 0.10f); // Yellow
		glVertex2f(temp3.m_x, temp3.m_y);
		glVertex2f(temp4.m_x, temp4.m_y);
		glVertex2f(temp5.m_x, temp5.m_y);
		glVertex2f(temp6.m_x, temp6.m_y);
		glEnd();
	}
	return;
}