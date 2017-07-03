#pragma once
#include <string>
//nEstaciones puede cambiar dependiendo del mapa
#define nESTACIONES 36

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
	bool operator<(const Camino& rhs) const
	{
		return prioridad < rhs.prioridad;
	}
};
