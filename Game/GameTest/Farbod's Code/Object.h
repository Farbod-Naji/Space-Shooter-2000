#pragma once
#include <vector>
#include "Map/Map.h"

class Object
{
public:
	
	//spawn in the cubes
	Object(unsigned int laneX, unsigned int laneY) : m_laneX(laneX), m_laneY(laneY), m_inLane(false) {};

	//spawn in the lane
	Object(unsigned int laneX, unsigned int laneY, float distance, float speed) : m_laneX(laneX), m_laneY(laneY), m_distanceInLane(distance), m_linearSpeed(speed), m_inLane(true){};

	virtual float CollisionPoint() = 0;

	static void DefineMap(Map* inputMap) { m_map = inputMap; }


	const void GetTilePosition(unsigned int& LaneX, unsigned int& LaneY) { LaneX = m_laneX; LaneY = m_laneY; }

	const bool IsInLane() { return m_inLane; }

	const float GetLinearDistance() { return m_distanceInLane; }


	void SetPosition(unsigned int laneX, unsigned int laneY) { m_laneX = laneX; m_laneY = laneY; }

	void SetSpeed(int laneSpeedX, int laneSpeedY) { m_laneXSpeed = laneSpeedX;  m_laneYSpeed = laneSpeedY; };

	void SetSpeed(float linearSpeed) { m_linearSpeed = linearSpeed; }

	void Update();

	bool EqualLanes(const Object& otherObject) const {	//values: check if the object in the same lane
		if ((m_laneX == otherObject.m_laneX) && (m_laneY == otherObject.m_laneY)) {
			return true;
		}
		return false;
	}

	bool EqualLanes(const Object* otherObject) const {	//pointers: check if the object in the same lane
		if ((m_laneX == otherObject->m_laneX) && (m_laneY == otherObject->m_laneY)) {
			return true;
		}
		return false;
	}

	bool operator==(const Object& otherObject) const {	//EqualLanes: check if the object in the same Lane/cubic
		return EqualLanes(otherObject);
	}

	bool operator==(const Object* otherObject) const {	//EqualLanes: check if the object in the same Lane/cubic
		return EqualLanes(otherObject);
	}

protected:
	static Map* m_map;

	bool m_inLane; 

	//for when it is inside the cubic area 
	unsigned int m_laneX, m_laneY;
	int m_laneXSpeed = 0, m_laneYSpeed = 0;	
	float m_movingCoolDown, m_movingTimer;

	//for when it is outside the cubic area and in the lanes
	float m_distanceInLane;
	float m_linearSpeed; 


};

