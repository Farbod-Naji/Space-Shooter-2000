#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet(unsigned int laneX, unsigned int laneY, bool facingRight, float distance) : Object(laneX, laneY, distance, -700.0f) {
	Object::m_laneX = laneX;
	Object::m_laneY = laneY;

	m_facingRight = facingRight;

	Object::m_distanceInLane = distance;

	if (m_facingRight) {
		Object::m_laneXSpeed = 0;
		Object::m_laneYSpeed = -1;
	}
	else if (!m_facingRight) {
		Object::m_laneXSpeed = -1;
		Object::m_laneYSpeed = 0;
	}

	Object::m_movingTimer = 0.0f;
	Object::m_movingCoolDown = 0.1f;

	m_hitTheWall = false;

	//Object::m_linearSpeed = -700.0f;
}

void EnemyBullet::Update(float dt) {
	if (Object::m_inLane) {
		Object::m_distanceInLane += Object::m_linearSpeed * (dt);
		if (Object::m_distanceInLane < 20.0f) {
			Object::m_inLane = false; 
			if (m_facingRight) {
				Object::m_laneY--;
			}
			if (!m_facingRight) {
				Object::m_laneX--;
			}
		}
	}
	else {
		if (Object::m_movingTimer < Object::m_movingCoolDown) {
			Object::m_movingTimer += dt;
		}
		else {
			Object::m_movingTimer = 0;
			if ((Object::m_laneX == 0 && !m_facingRight) || (Object::m_laneY == 0 && m_facingRight)) {
				m_hitTheWall = true;
			}
			if (Object::m_laneX != 0) {
				Object::m_laneX += Object::m_laneXSpeed;
			} 
			if (Object::m_laneY != 0){ 
				Object::m_laneY += Object::m_laneYSpeed;
			}
		}
	}

	return ;
}

void EnemyBullet::Render() {
	if (!m_inLane) {
		Tile* pointer = m_map->m_tiles[m_laneX][m_laneY];

		Point temp1 = pointer->m_BottomRight;
		Point temp2 = pointer->m_BottomLeft;
		Point temp3 = pointer->m_TopRight;
		Point temp4 = pointer->m_TopLeft;

#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(temp1.m_x, temp1.m_y);
		APP_VIRTUAL_TO_NATIVE_COORDS(temp2.m_x, temp2.m_y);
		APP_VIRTUAL_TO_NATIVE_COORDS(temp3.m_x, temp3.m_y);
		APP_VIRTUAL_TO_NATIVE_COORDS(temp4.m_x, temp4.m_y);
#endif

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f); // Yellow

		if (m_facingRight) {
			glVertex2f(temp1.m_x, temp1.m_y);
			glVertex2f(temp2.m_x, temp2.m_y);
			glVertex2f(temp3.m_x, temp3.m_y);
		}
		else {
			glVertex2f(temp1.m_x, temp1.m_y);
			glVertex2f(temp2.m_x, temp2.m_y);
			glVertex2f(temp4.m_x, temp4.m_y);
		}
		glEnd();
	}
	else {
		if (!m_facingRight) {
			Point point1, point2, point3, point4;

			Point temp1 = Object::m_map->m_upperRightMidPoints[Object::m_laneY];
			Vector temp2 = Object::m_map->m_upperRightMidVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane);
			point1.Add(temp1, temp2);

			temp2.Scale(-30.0f / m_distanceInLane);
			point4.Add(point1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane);
			point2.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY + 1];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY + 1];
			temp2.Scale(m_distanceInLane);
			point3.Add(temp1, temp2);

#if APP_USE_VIRTUAL_RES		
			APP_VIRTUAL_TO_NATIVE_COORDS(point1.m_x, point1.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point2.m_x, point2.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point3.m_x, point3.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point4.m_x, point4.m_y);
#endif

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f); // Yellow
			//glVertex2f(point1.m_x, point1.m_y);
			glVertex2f(point2.m_x, point2.m_y);
			glVertex2f(point3.m_x, point3.m_y);
			glVertex2f(point4.m_x, point4.m_y);
			glEnd();

		}

		if (m_facingRight) {
			Point point1, point2, point3, point4;


			Point temp1 = Object::m_map->m_upperLeftMidPoints[Object::m_laneX];
			Vector temp2 = Object::m_map->m_upperLeftMidVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane);
			point1.Add(temp1, temp2);

			temp2.Scale(-30.0f / m_distanceInLane);
			point4.Add(point1, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane);
			point2.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX + 1];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX + 1];
			temp2.Scale(m_distanceInLane);
			point3.Add(temp1, temp2);

#if APP_USE_VIRTUAL_RES		
			APP_VIRTUAL_TO_NATIVE_COORDS(point1.m_x, point1.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point2.m_x, point2.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point3.m_x, point3.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point4.m_x, point4.m_y);
#endif

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.0f, 0.0f); // Yellow
//			glVertex2f(point1.m_x, point1.m_y);
			glVertex2f(point2.m_x, point2.m_y);
			glVertex2f(point3.m_x, point3.m_y);
			glVertex2f(point4.m_x, point4.m_y);
			glEnd();
		}

	}
}

float EnemyBullet::CollisionPoint() {
	float returnVal = Object::m_distanceInLane;
	return returnVal;
}


