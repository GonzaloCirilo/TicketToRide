#pragma once
#include <vector>
#include <string>
#include "Structs.h"
#include "ArchiveManager.h"
#include <queue>
#include <functional>
#include <stack>
#include <algorithm>
#include <map>
typedef pair<int, int>ii;
typedef vector<vector<Camino>>Graph;
class JuegoC
{
private:
	std::vector<int>ManoIA;
	vector<string>ManoIAs;
	vector<int>links;//vector para el tracking del camino que toma al ejecutar djkstra
	stack<ii>st;
	void djkstra(int inicio, vector<int>* links, int jugador);
	void poner_camino(stack<ii>* st, int t);
	int mirarmano(string color);
	bool verificarCaminoCompleto(vector<string> vcolors, int u, int v);
public:
	Graph grafo;
	std::vector<Estacion>estaciones;
	vector<int>ManoJugador;
	vector<int>CartasenMesa;
	int nEstaciones;
	std::map<string, int> dictionary;
	JuegoC();
	~JuegoC();
	void obtnerRuta(int s, int t);
	void asignarRielJugador(int local, int destino, string color, int owner);
	string obtenerColoresDeCamino(int u, int v, int jugador);
	int peso(int u, int v);
	vector<string> split(const string & str, const string & delim);
	priority_queue<Camino> priorizarCaminos();
	String ^ generarStringCaminos();
	string colorIndexToString(int i);
	bool hayEnMesa(string color,int*pos);
	void escogerCarta();
};

