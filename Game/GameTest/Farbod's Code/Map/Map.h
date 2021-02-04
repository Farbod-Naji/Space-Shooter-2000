#pragma once
#include "../Points_Vectors.h"
#include <vector>

#include "../App/App.h"
#include "../Points_Vectors.h"
#include "Tile.h"


struct Map {
public:
	Map(Point right, Point up, Point left, Point down, unsigned int numOfDivision);
	
	void Render();

	Point m_rightPoint, m_topPoint, m_leftPoint, m_bottomPoint;
	unsigned int m_numOfDivision;

	Point m_perspectivePoint1, m_perspectivePoint2;

	std::vector <Point> m_lowerRightPoints;
	std::vector <Point> m_lowerLeftPoints;

	std::vector <Point> m_upperRightPoints;
	std::vector <Point> m_upperLeftPoints;

	std::vector <Vector> m_upperRightVectors;
	std::vector <Vector> m_upperLeftVectors;

	std::vector <std::vector <Tile*>> m_tiles;

	std::vector <Point> m_upperRightMidPoints;
	std::vector <Vector> m_upperRightMidVectors;

	std::vector <Point> m_upperLeftMidPoints;
	std::vector <Vector> m_upperLeftMidVectors;

	~Map();

private:
	void FindPerspectivePoints();
	void FindDividingPoints();

	void FindMidPoints();
	void FindVectors();


	Tile* FindTilePoints(unsigned int i, unsigned int j);
	void DefineTiles();
};