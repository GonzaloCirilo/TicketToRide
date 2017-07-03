#pragma once
#include <string>
class Carta
{
public:
	int color;
	std::string imagen;
	int x, y, w, h;
	Carta();
	Carta(int _x, int _y, int _w, int _h);
	~Carta();
};

