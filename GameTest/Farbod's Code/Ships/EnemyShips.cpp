#include "stdafx.h"
#include "EnemyShips.h"

#include <math.h>
#include <limits>
#include "../../App/app.h"

#define ComparePaths(_path1_,_path2_) ((_path1_->m_distance) <= (_path2_->m_distance)) ? (_path1_) : (_path2_) 

#define CalculateDistance(_x1_,_y1_,_x2_,_y2_) sqrtf(powf((_x1_ - _x2_), 2) + powf((_y1_ - _y2_), 2));

EnemyShips::EnemyShips(unsigned int laneX, unsigned int laneY) : Object(laneX, laneY, 800.0f, -1000.0f){
	Object::m_movingTimer = 0.0f;
	Object::m_movingCoolDown = 0.7f;

	m_shootingTimer = 0.0f;
	m_bulletCoolDown = 3.5f;
}

std::vector <EnemyBullet*> EnemyShips::Update(float dt, unsigned int playerTileX, unsigned int playerTileY) {
	std::vector <EnemyBullet*> returnVal;

	if (Object::m_inLane) {
		if (Object::m_distanceInLane < 10.0f) {
			m_inLane = false;
			if (Object::m_laneX == Object::m_map->m_numOfDivision) {
				Object::m_laneX--;
			}
			else if (Object::m_laneY == Object::m_map->m_numOfDivision) {
				Object::m_laneY--;
			}
		}
		m_distanceInLane += m_linearSpeed * (dt / 10);

		if (m_shootingTimer < m_bulletCoolDown) {
			m_shootingTimer += dt;
		}
		else {
			m_shootingTimer = 0;

			returnVal.push_back(new EnemyBullet(Object::m_laneX, Object::m_laneY, m_facingRight, (Object::m_distanceInLane - 30.0f)));
		}

	}

	if (!Object::m_inLane) {
		if (Object::m_movingTimer < Object::m_movingCoolDown) {
			Object::m_movingTimer += dt;
		}
		else {
			Object::m_movingTimer = 0;

			AIDecide(playerTileX, playerTileY);

			Object::m_laneX += Object::m_laneXSpeed;
			Object::m_laneY += Object::m_laneYSpeed;

			Object::m_laneXSpeed = 0;
			Object::m_laneYSpeed = 0;
		}
	}



	return returnVal;
}
   
void EnemyShips::Render() {
	float r = 1.0f, g = 0.0f, b = 0.0f;


	if (Object::m_inLane) {


		if (Object::m_laneX == Object::m_map->m_numOfDivision) {
			m_facingRight = false;
		}
		else if (Object::m_laneY == Object::m_map->m_numOfDivision) {
			m_facingRight = true;
		}

		Point point1, point2, point3, point4, point5;

		Point temp1;
		Vector temp2;



		if (!m_facingRight) {
			temp1 = Object::m_map->m_upperRightMidPoints[Object::m_laneY];
			temp2 = Object::m_map->m_upperRightMidVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane);
			point1.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane - m_height / 2);
			point2.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY];
			temp2.Scale(m_distanceInLane + m_height / 2);
			point3.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY + 1];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY + 1];
			temp2.Scale(m_distanceInLane - m_height / 2);
			point4.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperRightPoints[Object::m_laneY + 1];
			temp2 = Object::m_map->m_upperRightVectors[Object::m_laneY + 1];
			temp2.Scale(m_distanceInLane + m_height / 2);
			point5.Add(temp1, temp2);


			App::DrawLine(point2.m_x, point2.m_y, point3.m_x, point3.m_y, r, g, b);
			App::DrawLine(point2.m_x, point2.m_y, point4.m_x, point4.m_y, r, g, b);
			App::DrawLine(point2.m_x, point2.m_y, point5.m_x, point5.m_y, r, g, b);

			App::DrawLine(point3.m_x, point3.m_y, point4.m_x, point4.m_y, r, g, b);
			App::DrawLine(point3.m_x, point3.m_y, point5.m_x, point5.m_y, r, g, b);

			App::DrawLine(point4.m_x, point4.m_y, point5.m_x, point5.m_y, r, g, b);
		}

		else {
			temp1 = Object::m_map->m_upperLeftMidPoints[Object::m_laneX];
			temp2 = Object::m_map->m_upperLeftMidVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane);
			point1.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane - m_height / 2);
			point2.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX];
			temp2.Scale(m_distanceInLane + m_height / 2);
			point3.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX + 1];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX + 1];
			temp2.Scale(m_distanceInLane - m_height / 2);
			point4.Add(temp1, temp2);

			temp1 = Object::m_map->m_upperLeftPoints[Object::m_laneX + 1];
			temp2 = Object::m_map->m_upperLeftVectors[Object::m_laneX + 1];
			temp2.Scale(m_distanceInLane + m_height / 2);
			point5.Add(temp1, temp2);


			App::DrawLine(point2.m_x, point2.m_y, point3.m_x, point3.m_y, r, g, b);
			App::DrawLine(point2.m_x, point2.m_y, point4.m_x, point4.m_y, r, g, b);
			App::DrawLine(point2.m_x, point2.m_y, point5.m_x, point5.m_y, r, g, b);

			App::DrawLine(point3.m_x, point3.m_y, point4.m_x, point4.m_y, r, g, b);
			App::DrawLine(point3.m_x, point3.m_y, point5.m_x, point5.m_y, r, g, b);

			App::DrawLine(point4.m_x, point4.m_y, point5.m_x, point5.m_y, r, g, b);
		}
	}

	else {
		Tile* pointer = m_map->m_tiles[m_laneX][m_laneY];


		Point point1 = pointer->m_Top;
		Point point2 = pointer->m_Left;
		Point point3 = pointer->m_Bottom;
		Point point4 = pointer->m_Right;

		App::DrawLine(point1.m_x, point1.m_y, point3.m_x, point3.m_y, r, g, b);
		App::DrawLine(point2.m_x, point2.m_y, point4.m_x, point4.m_y, r, g, b);

		App::DrawLine(point1.m_x, point1.m_y, point2.m_x, point2.m_y, r, g, b);
		App::DrawLine(point1.m_x, point1.m_y, point4.m_x, point4.m_y, r, g, b);
		App::DrawLine(point2.m_x, point2.m_y, point3.m_x, point3.m_y, r, g, b);
		App::DrawLine(point3.m_x, point3.m_y, point4.m_x, point4.m_y, r, g, b);

	}
}



void EnemyShips::AIDecide(unsigned int playerTileX, unsigned int playerTileY) {

	enum PossiblePaths {
		m_UpperRight,
		m_UpperLeft,
		m_LowerRight,
		m_LowerLeft,
	};

	struct Path {
		Path(PossiblePaths path) {
			m_path = path;
			m_distance = 1000000.0f;
		}
		float m_distance;
		PossiblePaths m_path;
	};


	std::vector <Path*> list;
	list.push_back(new Path(m_UpperRight));
	list.push_back(new Path(m_UpperLeft));
	list.push_back(new Path(m_LowerRight));
	list.push_back(new Path(m_LowerLeft));

	if (Object::m_laneX != (Object::m_map->m_numOfDivision - 1)) {
		list[0]->m_distance = CalculateDistance((float)(Object::m_laneX + 1), (float)(Object::m_laneY), (float)(playerTileX), (float)(playerTileY));
	}
	if (Object::m_laneY != (Object::m_map->m_numOfDivision - 1)) {
		list[1]->m_distance = CalculateDistance((float)(Object::m_laneX), (float)(Object::m_laneY + 1), (float)(playerTileX), (float)(playerTileY));
	}
	if (Object::m_laneY != 0) {
		list[2]->m_distance = CalculateDistance((float)(Object::m_laneX), (float)(Object::m_laneY - 1), (float)(playerTileX), (float)(playerTileY));
	}
	if (Object::m_laneX != 0) {
		list[3]->m_distance = CalculateDistance((float)(Object::m_laneX - 1), (float)(Object::m_laneY), (float)(playerTileX), (float)(playerTileY));
	}




	Path* bestPath1 = ((list[2]->m_distance) <= (list[3]->m_distance)) ? (list[2]) : (list[3]);
	Path* bestPath2 = ((list[0]->m_distance) <= (list[1]->m_distance)) ? (list[0]) : (list[1]);

	Path* bestPathFinal = ((bestPath1->m_distance) <= (bestPath2->m_distance)) ? (bestPath1) : (bestPath2);

	if (bestPathFinal->m_path == m_UpperRight) {
		Object::m_laneXSpeed = 1;
	}
	else if (bestPathFinal->m_path == m_UpperLeft) {
		Object::m_laneYSpeed = 1;
	}
	else if (bestPathFinal->m_path == m_LowerRight) {
		Object::m_laneYSpeed = -1;
	}
	else if (bestPathFinal->m_path == m_LowerLeft) {
		Object::m_laneXSpeed = -1;
	}

	for (unsigned int i = 0; i < list.size(); i++) {
		delete list[i];
	}
}

float EnemyShips::CollisionPoint() {
	float returnVal = Object::m_distanceInLane;
	returnVal -= m_height;
	return returnVal;
}
