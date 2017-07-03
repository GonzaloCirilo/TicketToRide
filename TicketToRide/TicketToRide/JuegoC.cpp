#include "JuegoC.h"

const int IA = 1;
const int PLAYER = 2;


JuegoC::JuegoC()
{
	ManoIA= { "Yellow", "Yellow", "Green","Blue","Blue" };
	ArchiveManager archm;
	//Carga Estaciones
	this->estaciones = vector<Estacion>();
	nEstaciones = archm.Load_Estaciones(&estaciones);
	//Carga Grafo
	this->grafo = Graph(nEstaciones);
	archm.Load_Grafo(&grafo, nEstaciones);
}


JuegoC::~JuegoC()
{
}
void JuegoC::obtnerRuta(int s,int t) {
	links = vector<int>(nEstaciones, -1);
	//int s = 0; int t = 33;
	djkstra(s, &links, 1);
	//pila para recuperar el orden de las aristas
	st = stack<ii>();
	st.push({ links[t],t });
	//llenamos la pila
	poner_camino(&st, links[t]);
}
void JuegoC::djkstra(int inicio, vector<int>*links, int jugador) {
	vector<int>distancias = vector<int>(nEstaciones, -1);
	vector<int>nodosAc = vector<int>(nEstaciones, -1);
	priority_queue<ii, vector<ii>, greater<ii>>pq;
	distancias[inicio] = 0;
	nodosAc[inicio] = 1;
	pq.push({ 0,inicio });
	while (!pq.empty())
	{
		int nodo = pq.top().second;
		int pesonodo = pq.top().first;
		pq.pop();
		int adyacente = -1;
		if (distancias[nodo] >= pesonodo) {
			for (int i = 0; i < grafo[nodo].size(); i++) {
				//este if es para descartar los caminos repetitivos del mismo peso
				if (adyacente != grafo[nodo][i].est_llegada) {
					adyacente = grafo[nodo][i].est_llegada;
					int peso = grafo[nodo][i].peso;
					int posiblepeso = pesonodo + peso;
					//se podria gregar otra condicion para que elija el camino con menor varianza de pesos
					if ((distancias[adyacente] == -1 || distancias[adyacente] > posiblepeso ||
						(distancias[adyacente] == posiblepeso && nodosAc[nodo] >= nodosAc[adyacente])
						) && !obtenerColoresDeCamino(nodo, adyacente, IA).empty()) {
						distancias[adyacente] = posiblepeso;
						nodosAc[adyacente] = nodosAc[nodo] + 1;
						links->at(adyacente) = nodo;
						pq.push({ posiblepeso,adyacente });
					}
				}
			}
		}
	}
}
void JuegoC::asignarRielJugador(int local, int destino, string color, int owner) {
	for (int i = 0; i < grafo.at(local).size(); i++) {
		if (grafo.at(local).at(i).est_llegada == destino&&grafo.at(local).at(i).color == color) {
			grafo.at(local).at(i).dueño = owner;
		}
	}
	for (int i = 0; i < grafo.at(destino).size(); i++) {
		if (grafo.at(destino).at(i).est_llegada == local&&grafo.at(destino).at(i).color == color) {
			grafo.at(destino).at(i).dueño = owner;
		}
	}
}

//funcion para poblar la pila de caminos a seguir
void JuegoC::poner_camino(stack<ii>*st, int t) {
	if (t == -1) {
		st->pop();
		return;
	}
	st->push({ links[t],t });
	poner_camino(st, links[t]);
}
//funcion modificable
string JuegoC::obtenerColoresDeCamino(int u, int v, int jugador) {
	string r = "";
	for (int i = 0; i < grafo[u].size(); i++) {
		if (grafo[u][i].est_llegada == v && (grafo[u][i].dueño == 0 || grafo[u][i].dueño == jugador)) {
			r += "" + grafo[u][i].color + "||";
		}
	}
	if (!r.empty()) {
		r.pop_back();
		r.pop_back();
	}
	return r;
}
//puede variar
int JuegoC::peso(int u, int v) {
	int p;
	for (int i = 0; i < grafo[u].size(); i++) {
		if (grafo[u][i].est_llegada == v) {
			p = grafo[u][i].peso;
			break;
		}
	}
	return p;
}
vector<string> JuegoC::split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}
//saber cuantas cartas de un determinado color tiene
int JuegoC::mirarmano(string color) {
	int cont = 0;
	//Luego reemplazar este string por el arreglo de manos
	for (int i = 0; i < ManoIA.size(); i++) {
		if (ManoIA.at(i) == color)
			cont++;
	}
	return cont;
}
bool JuegoC::verificarCaminoCompleto(vector<string>vcolors, int u, int v) {
	bool completado = false;
	for each (auto color in vcolors)
	{
		int pesoaux = peso(u, v);
		if (color != "Any") {
			int cartas_mano_color = mirarmano(color);
			if (cartas_mano_color == pesoaux) {
				completado = true;
			}
		}
		else {
			if (count(ManoIA.begin(), ManoIA.end(), "Yellow") == pesoaux) {
				completado = true;
			}
		}
	}
	return completado;
}

//funcion que retorna inicializa un vector con los pesos de los caminos, el color y el puntaje de prioridad del camino a seguir
priority_queue<Camino> JuegoC::obtener_Pesos_Costos() {
	priority_queue<Camino> pq_caminos;

	stack<ii>ss = st;
	int size = ss.size();
	//impresion de caminos(sujeta a cambios)
	for (int i = 0; i < size; i++) {
		auto aux = ss.top(); ss.pop();
		int u = estaciones[aux.first].index;
		int v = estaciones[aux.second].index;
		string colors = obtenerColoresDeCamino(u, v, IA);
		String^estacion1 = gcnew String(estaciones[aux.first].nombre.c_str());
		String^estacion2 = gcnew String(estaciones[aux.second].nombre.c_str());
		auto vcolors = split(colors, "||");
		bool completado = verificarCaminoCompleto(vcolors, u, v);

		for each (auto c in vcolors)
		{
			Camino newCami;
			newCami.color = c;
			newCami.est_salida = u;
			newCami.est_llegada = v;
			int pesoaux = peso(u, v);
			newCami.peso = pesoaux;
			int cartas_mano_color = mirarmano(c) + 1;
			double razon = 1;
			if (c.compare("Any") == 0)
				razon = 2;
			newCami.prioridad = (1 / pow((double)vcolors.size(), 3))*
				(1 / (double)pesoaux)*
				((double)cartas_mano_color)*
				(1 / razon)*
				(!completado);//descartar rutas que ya has completado en tu mano y aun
			pq_caminos.push(newCami);
		}
	}
	return pq_caminos;
}

String^ JuegoC::generarStringCaminos() {
	String^resp = "";
	int size = st.size();
	//impresion de caminos(sujeta a cambios porque no es necesario)
	for (int i = 0; i < size; i++) {
		auto aux = st.top(); st.pop();
		int u = estaciones[aux.first].index;
		int v = estaciones[aux.second].index;
		String^colors = gcnew String(obtenerColoresDeCamino(u, v, IA).c_str());
		String^estacion1 = gcnew String(estaciones[aux.first].nombre.c_str());
		String^estacion2 = gcnew String(estaciones[aux.second].nombre.c_str());
		resp += "[Camino " + (i + 1) + ": " + estacion1 + "-" + estacion2 + "] [Peso: " + peso(u, v) +
			"] [Colores:" + colors + "]" + Environment::NewLine;
	}
	return resp;
}