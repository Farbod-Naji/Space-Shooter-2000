#include "stdafx.h"
#include "PlayerBullets.h"
#include "../../App/app.h"

PlayerBullets::PlayerBullets(unsigned int laneX, unsigned int laneY, int laneXSpeed, int laneYSpeed) : Object(laneX, laneY) {
	Object::m_laneXSpeed = laneXSpeed;
	Object::m_laneYSpeed = laneYSpeed;

	if (laneXSpeed > 0) {
		m_facingRight = true;
	}
	else {
		m_facingRight = false;
	}
	Object::m_linearSpeed = 1000.0f;

	Object::m_movingTimer = 0.0f;
	Object::m_movingCoolDown = 0.15f;
}

void PlayerBullets::Update(float dt) {
	if (!m_inLane){
		if ((Object::m_laneX == m_map->m_numOfDivision) || (Object::m_laneY == m_map->m_numOfDivision)) {
			Object::m_inLane = true;
			m_distanceInLane = 5.0f;
		}
		if (Object::m_movingTimer < Object::m_movingCoolDown) {
			Object::m_movingTimer += dt;
		}
		else {	
			Object::m_movingTimer = 0;
			if ( ((Object::m_laneX == ((m_map->m_numOfDivision) - 1)) && (Object::m_laneXSpeed > 0) ) || ( (Object::m_laneY == ((m_map->m_numOfDivision) - 1)) && (Object::m_laneYSpeed > 0)) ){
				Object::m_inLane = true;
				Object::m_laneX += Object::m_laneXSpeed;
				Object::m_laneY += Object::m_laneYSpeed;
				m_distanceInLane = 5.0f;
			}
			else {
				Object::m_laneX += Object::m_laneXSpeed;
				Object::m_laneY += Object::m_laneYSpeed;
			}
		}
	}
	else {
		m_distanceInLane += m_linearSpeed * (dt);
	}
}

void PlayerBullets::Render() {
	if (!m_inLane) {
		Tile* pointer = m_map->m_tiles[m_laneX][m_laneY];

		Point temp1 = pointer->m_TopRight;
		Point temp2 = pointer->m_TopLeft;
		Point temp3 = pointer->m_BottomRight;
		Point temp4 = pointer->m_BottomLeft;
		
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(temp1.m_x, temp1.m_y);
		APP_VIRTUAL_TO_NATIVE_COORDS(temp2.m_x, temp2.m_y);
		APP_VIRTUAL_TO_NATIVE_COORDS(temp3.m_x, temp3.m_y);
		APP_VIRTUAL_TO_NATIVE_COORDS(temp4.m_x, temp4.m_y);
#endif

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.70f, 0.10f); // Yellow
		
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
		if (m_facingRight){
			Point point1, point2, point3, point4;

			Point temp1 = Object::m_map->m_upperRightMidPoints[Object::m_laneY];
			Vector temp2 = Object::m_map->m_upperRightMidVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane);
			point1.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane);
			point2.Add(temp1, temp2);

			temp2.Scale(-30.0f / m_distanceInLane);
			point2.Add(point2, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY + 1];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY + 1];
			temp2.Scale(m_distanceInLane);
			point3.Add(temp1, temp2);

			temp2.Scale(-30.0f / m_distanceInLane);
			point3.Add(point3, temp2);



#if APP_USE_VIRTUAL_RES		
			APP_VIRTUAL_TO_NATIVE_COORDS(point1.m_x, point1.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point2.m_x, point2.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point3.m_x, point3.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point4.m_x, point4.m_y);
#endif

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.70f, 0.10f); // Yellow
			glVertex2f(point1.m_x, point1.m_y);
			glVertex2f(point2.m_x, point2.m_y);
			glVertex2f(point3.m_x, point3.m_y);
			glEnd();

		}

		if (!m_facingRight) {
			Point point1, point2, point3, point4;
		

			Point temp1 = Object::m_map->m_upperLeftMidPoints[Object::m_laneX];
			Vector temp2 = Object::m_map->m_upperLeftMidVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane);
			point1.Add(temp1, temp2);
			
			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane);
			point2.Add(temp1, temp2);

			temp2.Scale(-30.0f / m_distanceInLane);
			point2.Add(point2, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX + 1];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX + 1];
			temp2.Scale(m_distanceInLane);
			point3.Add(temp1, temp2);

			temp2.Scale(-30.0f / m_distanceInLane);
			point3.Add(point3, temp2);

#if APP_USE_VIRTUAL_RES		
			APP_VIRTUAL_TO_NATIVE_COORDS(point1.m_x, point1.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point2.m_x, point2.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point3.m_x, point3.m_y);
			APP_VIRTUAL_TO_NATIVE_COORDS(point4.m_x, point4.m_y);
#endif

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.70f, 0.10f); // Yellow
			glVertex2f(point1.m_x, point1.m_y);
			glVertex2f(point2.m_x, point2.m_y);
			glVertex2f(point3.m_x, point3.m_y);
			glEnd();	
		}

	}
}

float PlayerBullets::CollisionPoint() {
	float returnVal = Object::m_distanceInLane;
	return returnVal;
}