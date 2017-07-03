#pragma once
#include <string>
#include "Riel.h"
#include <vector>
struct Estacion
{
	int index;
	std::string nombre;
};

struct Camino {
	int est_salida;
	int est_llegada;
	std::string color;
	int peso;
	int dueño;
	double prioridad;
	std::vector<Riel>Arreglo_Riel;
	bool operator<(const Camino& rhs) const
	{
		return prioridad < rhs.prioridad;
	}
};

struct Colores
{
	static const std::string Yellow;
	static const std::string Green;
	static const std::string Blue;
	static const std::string Black;
	static const std::string Red;
	static const std::string White;
	static const std::string Any;
	static const std::string Pink;
	static const std::string Orange;
};

struct IndexColores
{
	static const int Yellow = 8;
	static const int Green = 3;
	static const int Blue = 2;
	static const int Black = 1;
	static const int Red = 6;
	static const int White = 7;
	static const int Any = 0;
	static const int Pink = 5;
	static const int Orange = 4;
};