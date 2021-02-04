#include "stdafx.h"
#include "Map.h"

void DrawPoint(float x, float y, float r = 1.0f, float g = 1.0f, float b = 1.0f);

Map::Map(Point right, Point up, Point left, Point down, unsigned int numOfDivision) {

	m_bottomPoint = down;	m_topPoint = up;
	m_leftPoint = left;	m_rightPoint = right;

	m_numOfDivision = numOfDivision;

	m_tiles.resize(numOfDivision, std::vector <Tile*>(numOfDivision));
	
	m_lowerRightPoints.resize(numOfDivision + 1);
	m_lowerLeftPoints.resize(numOfDivision + 1);

	m_upperRightPoints.resize(numOfDivision + 1);
	m_upperLeftPoints.resize(numOfDivision + 1);

	m_upperRightVectors.resize(numOfDivision + 1);
	m_upperLeftVectors.resize(numOfDivision + 1);

	m_upperRightMidPoints.resize(numOfDivision);
	m_upperRightMidVectors.resize(numOfDivision);

	m_upperLeftMidPoints.resize(numOfDivision);
	m_upperLeftMidVectors.resize(numOfDivision);


	FindPerspectivePoints();

	FindDividingPoints();

	FindMidPoints();

	FindVectors();

	DefineTiles();
}

// --------------

void Map::FindPerspectivePoints() {
	struct Line {
	public:
		Line() : m_slope(0.0f), m_const(0.0f) {};

		float m_slope, m_const;
	};

	Line line1; //Low Right Line
	line1.m_slope = (m_bottomPoint.m_y - m_rightPoint.m_y) / (m_bottomPoint.m_x - m_rightPoint.m_x);
	line1.m_const = m_bottomPoint.m_y - line1.m_slope * m_bottomPoint.m_x;

	Line line2; //Up Right Line
	line2.m_slope = (m_topPoint.m_y - m_rightPoint.m_y) / (m_topPoint.m_x - m_rightPoint.m_x);
	line2.m_const = m_rightPoint.m_y - line2.m_slope * m_rightPoint.m_x;

	Line line3; //Up Left Line
	line3.m_slope = (m_topPoint.m_y - m_leftPoint.m_y) / (m_topPoint.m_x - m_leftPoint.m_x);
	line3.m_const = m_leftPoint.m_y - line3.m_slope * m_leftPoint.m_x;

	Line line4; //Low Left Line
	line4.m_slope = (m_bottomPoint.m_y - m_leftPoint.m_y) / (m_bottomPoint.m_x - m_leftPoint.m_x);
	line4.m_const = m_bottomPoint.m_y - line4.m_slope * m_bottomPoint.m_x;

	m_perspectivePoint1.m_x = (line3.m_const - line1.m_const) / (line1.m_slope - line3.m_slope);
	m_perspectivePoint1.m_y = line1.m_slope * m_perspectivePoint1.m_x + line1.m_const;

	m_perspectivePoint2.m_x = (line2.m_const - line4.m_const) / (line4.m_slope - line2.m_slope);
	m_perspectivePoint2.m_y = line2.m_slope * m_perspectivePoint2.m_x + line2.m_const;
}

void Map::FindDividingPoints() {
	Vector distance;

	//line along the lower right line
	distance.Substract(m_rightPoint, m_bottomPoint);
	distance.Scale(1.0f / m_numOfDivision);


	Point temp;

	for (unsigned int i = 0; i <= m_numOfDivision; i++) {
		temp = m_bottomPoint;
		temp.m_x += distance.m_x * i;
		temp.m_y += distance.m_y * i;
		m_lowerRightPoints[i] = temp;
	}

	//lines along the lower left line
	distance.Substract(m_leftPoint, m_bottomPoint);
	distance.Scale(1.0f / m_numOfDivision);

	for (unsigned int i = 0; i <= m_numOfDivision; i++) {
		temp = m_bottomPoint;
		temp.m_x += distance.m_x * i;
		temp.m_y += distance.m_y * i;
		m_lowerLeftPoints[i] = temp;
	}

	//lines along the upper right line
	distance.Substract(m_topPoint, m_rightPoint);
	distance.Scale(1.0f / m_numOfDivision);

	for (unsigned int i = 0; i <= m_numOfDivision; i++) {
		temp = m_rightPoint;
		temp.m_x += distance.m_x * i;
		temp.m_y += distance.m_y * i;
		m_upperRightPoints[i] = temp;
	}
	
	//lines along the upper left line
	distance.Substract(m_topPoint, m_leftPoint);
	distance.Scale(1.0f / m_numOfDivision);

	for (unsigned int i = 0; i <= m_numOfDivision; i++) {
		temp = m_leftPoint;
		temp.m_x += distance.m_x * i;
		temp.m_y += distance.m_y * i;
		m_upperLeftPoints[i] = temp;
	}
}

void Map::FindMidPoints() {
	Vector displacement, temp;
	displacement.Substract(m_topPoint, m_rightPoint); //point in top left direction
	displacement.Scale(1 / (2.0f * m_numOfDivision));
	for (unsigned int i = 0; i < m_numOfDivision ; i++) {
		temp = displacement;
		temp.Scale((float)i * 2 + 1.0f);
		temp.Add(temp, m_rightPoint);
		m_upperRightMidPoints[i] = temp;
	}

	displacement.Substract(m_topPoint, m_leftPoint); //point in top Right direction
	displacement.Scale(1 / (2.0f * m_numOfDivision));
	for (unsigned int i = 0; i < m_numOfDivision; i++) {
		temp = displacement;
		temp.Scale((float)i * 2 + 1.0f);
		temp.Add(temp, m_leftPoint);
		m_upperLeftMidPoints[i] = temp;
	}

}

void Map::FindVectors() {
	Vector temp;
	for (unsigned int i = 0; i < m_upperRightPoints.size(); i++) {	// these Vectors are pointing outward and are used to find the position of the objects when they leave the arena
		temp.Substract(m_perspectivePoint1, m_upperRightPoints[i]);
		temp.Scale(1.0f / GetLenght(temp));
		m_upperRightVectors[i] = temp;
	}

	for (unsigned int i = 0; i < m_upperRightMidPoints.size(); i++) {
		temp.Substract(m_perspectivePoint1, m_upperRightMidPoints[i]);
		temp.Scale(1.0f / GetLenght(temp));
		m_upperRightMidVectors[i] = temp;
	}

	for (unsigned int i = 0; i < m_upperLeftPoints.size(); i++) {
		temp.Substract(m_perspectivePoint2, m_upperLeftPoints[i]);
		temp.Scale(1 / GetLenght(temp));
		m_upperLeftVectors[i] = temp;
	}

	for (unsigned int i = 0; i < m_upperLeftMidPoints.size(); i++) {
		temp.Substract(m_perspectivePoint2, m_upperLeftMidPoints[i]);
		temp.Scale(1.0f / GetLenght(temp));
		m_upperLeftMidVectors[i] = temp;
	}

	return ;
}



Tile* Map::FindTilePoints(unsigned int i, unsigned int j) {
	Tile* pointer = new Tile(i, j);

	Point Bottom = m_bottomPoint;
	Point Top = m_bottomPoint;
	Point Right = m_bottomPoint;
	Point Left = m_bottomPoint;

	Point otherEnd;
	Vector displacement;

	//	------------

	displacement.Substract(m_rightPoint, m_bottomPoint); //in the up right direction
	displacement.Scale(1.0f / m_numOfDivision);

	displacement.Scale((float)i);

	Bottom.Add(Bottom, displacement);
	Left.Add(Left, displacement);

	//	------------

	displacement.Substract(m_rightPoint, m_bottomPoint); //in the up right direction
	displacement.Scale(1.0f / m_numOfDivision);

	displacement.Scale((float)i + 1.0f);

	Top.Add(Top, displacement);
	Right.Add(Right, displacement);

	//	------------
	//	------------
	displacement.Substract(m_topPoint, m_leftPoint); //in the up Right direction
	displacement.Scale(1.0f / m_numOfDivision);
	displacement.Scale((float)i);
	otherEnd = m_leftPoint;
	otherEnd.Add(otherEnd, displacement);

	displacement.Substract(otherEnd, Bottom);//in the up Left direction
	displacement.Scale(1.0f / m_numOfDivision);

	displacement.Scale((float)j);
	Bottom.Add(Bottom, displacement);

	//	------------
	displacement.Substract(m_topPoint, m_leftPoint); //in the up right direction
	displacement.Scale(1.0f / m_numOfDivision);
	displacement.Scale((float)i);
	otherEnd = m_leftPoint;
	otherEnd.Add(otherEnd, displacement);

	displacement.Substract(otherEnd, Left);
	displacement.Scale(1.0f / m_numOfDivision);

	displacement.Scale((float)j + 1.0f);
	Left.Add(Left, displacement);

	//	------------
	displacement.Substract(m_topPoint, m_leftPoint); //in the up right direction
	displacement.Scale(1.0f / m_numOfDivision);
	displacement.Scale((float)i + 1.0f);
	otherEnd = m_leftPoint;
	otherEnd.Add(otherEnd, displacement);

	displacement.Substract(otherEnd, Right);
	displacement.Scale(1.0f / m_numOfDivision);

	displacement.Scale((float)j);
	Right.Add(Right, displacement);

	//	------------
	displacement.Substract(m_topPoint, m_leftPoint); //in the up right direction
	displacement.Scale(1.0f / m_numOfDivision);
	displacement.Scale((float)i + 1.0f);
	otherEnd = m_leftPoint;
	otherEnd.Add(otherEnd, displacement);

	displacement.Substract(otherEnd, Top);
	displacement.Scale(1.0f / m_numOfDivision);

	displacement.Scale((float)j + 1.0f);
	Top.Add(Top, displacement);

	pointer->m_Bottom = Bottom;
	pointer->m_Left = Left;
	pointer->m_Top = Top;
	pointer->m_Right = Right;

	pointer->CalcAvgs();

	return pointer;
}

void Map::DefineTiles() {
	Vector Displacement;
	for (unsigned int i = 0; i < m_numOfDivision; i++) {
		for (unsigned int j = 0; j < m_numOfDivision; j++) {
			m_tiles[i][j] = FindTilePoints(i, j);
		}
	}
}

// ---------------

void Map::Render() {
	for (unsigned int i = 0; i < m_lowerLeftPoints.size(); i++) {
		App::DrawLine(m_lowerRightPoints[i].m_x, m_lowerRightPoints[i].m_y, m_perspectivePoint2.m_x, m_perspectivePoint2.m_y, 0.0f, 0.0f, 0.8f);
		App::DrawLine(m_lowerLeftPoints[i].m_x, m_lowerLeftPoints[i].m_y, m_perspectivePoint1.m_x, m_perspectivePoint1.m_y, 0.0f, 0.0f, 0.8f);
	}
	App::DrawLine(m_bottomPoint.m_x, m_bottomPoint.m_y, m_perspectivePoint1.m_x, m_perspectivePoint1.m_y);
	App::DrawLine(m_leftPoint.m_x, m_leftPoint.m_y, m_perspectivePoint1.m_x, m_perspectivePoint1.m_y);
	App::DrawLine(m_bottomPoint.m_x, m_bottomPoint.m_y, m_perspectivePoint2.m_x, m_perspectivePoint2.m_y);
	App::DrawLine(m_rightPoint.m_x, m_rightPoint.m_y, m_perspectivePoint2.m_x, m_perspectivePoint2.m_y);
	return;
}


Map::~Map() {
	for (unsigned int i = 0; i < m_numOfDivision; i++) {
		for (unsigned int j = 0; j < m_numOfDivision; j++) {
			delete m_tiles[i][j];
		}
	}
	m_tiles.clear();
}
