#pragma once


#define CalcDistance(_point1_,_point2_) sqrtf( powf(_point1_.m_x - _point2_.m_x, 2) + powf(_point1_.m_y - _point2_.m_y, 2) )

#define GetLenght(_vec_) sqrtf( powf(_vec_.m_x , 2) + powf(_vec_.m_y , 2) )

struct Point {
public:
	Point(float x = 0.0f, float y = 0.0f) : m_x(x), m_y(y) {};
	
	float m_x, m_y;

	template <class T = Point, class U = Point>
	void Add(T Data1, U Data2) {
		m_x = Data1.m_x + Data2.m_x;
		m_y = Data1.m_y + Data2.m_y;
	}

	template <class T = Point, class U = Point>
	void Substract(T Data1, U Data2) {
		m_x = Data1.m_x - Data2.m_x;
		m_y = Data1.m_y - Data2.m_y;
	}

	void Scale(float scale) {
		m_x *= scale;
		m_y *= scale;
	}
};

typedef Point Vector;
