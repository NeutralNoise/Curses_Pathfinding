#ifndef VEC2_H
#define VEC2_H
#include <math.h>
struct Vec2
{
	int x;
	int y;
	double lenght;

	Vec2() {

	}

	Vec2(int x, int y) {
		this->x = x;
		this->y = y;
		lenght = 0.0;
	}

	bool operator==(Vec2 other) {
		if ((this->x == other.x) && (this->y == other.y)) {
			return true;
		}
		return false;
	}

	bool operator!=(Vec2 other) {
		if(*this == other)
            return false;

		return true;
	}

	Vec2 operator-(const Vec2& other) {
		Vec2 newPos;
		newPos.x = this->x - other.x;
		newPos.y = this->y - other.y;
		newPos.lenght = sqrt((((other.x + this->x) * 2) + ((other.y + this->y) * 2)));
		return newPos;
	}

	Vec2 operator-(const int& other) {
		Vec2 newPos;
		newPos.x = this->x - other;
		newPos.y = this->y - other;
		newPos.lenght = sqrt((((other + this->x) * 2) + ((other + this->y) * 2)));
		return newPos;
	}

	Vec2 operator+(const Vec2& other) {
		Vec2 newPos;
		newPos.x = this->x + other.x;
		newPos.y = this->y + other.y;
		newPos.lenght = sqrt((((other.x + this->x) * 2) + ((other.y + this->y) * 2)));
		return newPos;
	}

	Vec2 operator+(const int& other) {
		Vec2 newPos;
		newPos.x = this->x + other;
		newPos.y = this->y + other;
		newPos.lenght = sqrt((((other + this->x) * 2) + ((other + this->y) * 2)));
		return newPos;
	}

	Vec2 operator=(const Vec2& other) {
		this->x = other.x;
		this->y = other.y;
		this->lenght = other.lenght;

		return *this;
	}

};

#endif //VEC2_H