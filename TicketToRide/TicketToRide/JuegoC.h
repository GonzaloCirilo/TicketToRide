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
typedef pair<int, ii>iii;
typedef vector<vector<Camino>>Graph;
class JuegoC
{
private:
	std::vector<int>ManoIA;
	vector<string>ManoIAs;
	vector<int>links;//vector para el tracking del camino que toma al ejecutar djkstra
	stack<ii>st;
	stack<ii>staux;
	void djkstra(int inicio, vector<int>* links, int jugador);
	void almostDjkstra(int inicio, vector<int>* links, int jugador);
	void poner_camino(stack<ii>* st, int t);
	int mirarmano(string color);
	bool verificarCaminoCompleto(vector<string> vcolors, int u, int v);
	void cogerCarta(int color, int pos);
	auto definirColorMenosImporMano(int peso);
	string obtenerColoresDeCamino(int u, int v, int jugador);
public:
	Graph grafo;
	std::vector<Estacion>estaciones;
	vector<int>ManoJugador;
	vector<int>CartasenMesa;
	int nEstaciones;
	std::map<string, int> dictionary;
	iii rutaIA, rutaJugador;
	vector<iii> piladeRutas;
	vector<int>pilaCartas;
	JuegoC();
	~JuegoC();
	void darRuta(int Player);
	void obtnerRuta(int s, int t);
	void asignarRielJugador(int local, int destino, string color, int owner);
	int peso(int u, int v);
	vector<string> split(const string & str, const string & delim);
	priority_queue<Camino> priorizarCaminos();
	String ^ generarStringCaminos();
	string colorIndexToString(int i);
	bool hayEnMesa(string color,int *pos);
	void escogerCarta();
	void ReponerCartaTablero();
	bool CumploCosto(Camino c);
	bool CumploCosto(string color, int peso);
	void eliminarCartas(int jugador, int color, int peso);
	bool verCaminoDueño(int u, int v);
	void RealizarJugada();
	bool terminoRuta(int owner);
};

