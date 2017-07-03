#pragma once
#include <vector>
#include <string>
#include "Structs.h"
#include "ArchiveManager.h"
#include <queue>
#include <functional>
#include <stack>
#include <algorithm>
typedef pair<int, int>ii;
typedef vector<vector<Camino>>Graph;
class JuegoC
{
private:
	std::vector<std::string>ManoIA;
	vector<int>links;
	stack<ii>st;
	void djkstra(int inicio, vector<int>* links, int jugador);
	void poner_camino(stack<ii>* st, int t);
	int mirarmano(string color);
	bool verificarCaminoCompleto(vector<string> vcolors, int u, int v);
public:
	Graph grafo;
	std::vector<Estacion>estaciones;
	int nEstaciones;
	JuegoC();
	~JuegoC();
	void obtnerRuta(int s, int t);
	void asignarRielJugador(int local, int destino, string color, int owner);
	string obtenerColoresDeCamino(int u, int v, int jugador);
	int peso(int u, int v);
	vector<string> split(const string & str, const string & delim);
	priority_queue<Camino> obtener_Pesos_Costos();
	String ^ generarStringCaminos();
};

