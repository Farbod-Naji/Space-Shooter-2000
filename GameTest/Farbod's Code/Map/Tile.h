#pragma once
#include "../Points_Vectors.h"

struct Tile
{
	Tile(unsigned int tileNumberX = -1, unsigned int tileNumberY = -1) { m_TileNumberX = tileNumberX; m_TileNumberY = tileNumberY; };
	
	unsigned int m_TileNumberX = 0, m_TileNumberY = 0;

	Point m_Center, m_Top, m_Left, m_Right, m_Bottom;
	Point m_TopLeft, m_TopRight, m_BottomLeft, m_BottomRight;

	void CalcAvgs() {
		Point temp;
		temp.m_x = (m_Left.m_x + m_Right.m_x) / 2.0f;
		temp.m_y = (m_Top.m_y + m_Bottom.m_y) / 2.0f;
		m_Center = temp;

		temp.Add(m_Top, m_Right);
		temp.Scale(1 / 2.0f);
		m_TopRight = temp;

		temp.Add(m_Top, m_Left);
		temp.Scale(1 / 2.0f);
		m_TopLeft = temp;

		temp.Add(m_Bottom, m_Left);
		temp.Scale(1 / 2.0f);
		m_BottomLeft = temp;

		temp.Add(m_Bottom, m_Right);
		temp.Scale(1 / 2.0f);
		m_BottomRight = temp;
	}
};

