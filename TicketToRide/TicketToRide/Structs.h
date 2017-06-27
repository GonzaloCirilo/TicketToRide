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

//static class Colores {
//public:
//	static string Any;
//	static string Blue;
//	static string Black;
//	static string Green;
//	static string Orange;
//	static string Pink;
//	static string Red;
//	static string White;
//	static string Yellow;
//};
//
//const string Colores::Any = "Any";
//const string Colores::Blue = "Blue";
//const string Colores::Black = "Black";
//const string Colores::Green = "Green";
//const string Colores::Orange = "Orange";
//const string Colores::Pink = "Pink";
//const string Colores::Red = "Red";
//const string Colores::White = "White";
//const string Colores::Yellow = "Yellow";