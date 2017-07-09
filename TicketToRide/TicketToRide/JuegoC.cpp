#include "JuegoC.h"

const int IA = 1;
const int PLAYER = 2;

//UDFS support
vector<int>psetIA;
vector<int>psetJugador;

void init(vector<int>*pset) {
	*pset = vector<int>(36);
	for (int i = 0; i < pset->size(); i++) {
		pset->at(i) = i;
	}
}

int findset(int nodo, vector<int>*pset) {
	if (nodo == pset->at(nodo))
		return pset->at(nodo);
	return pset->at(nodo) = findset(pset->at(nodo), pset);
}

bool isSameSet(int a, int b, vector<int>*pset) {
	return findset(a, pset) == findset(b, pset);
}

void unionset(int a, int b, vector<int>*pset) {
	if (!isSameSet(a, b, pset))
		pset->at(findset(a, pset)) = findset(b, pset);
}

JuegoC::JuegoC()
{
	init(&psetIA);
	init(&psetJugador);
	pilaCartas = vector<int>(80);
	for (int i = 1; i <= 8; i++) {
		for (int j = 0; j < 10; j++) {
			pilaCartas[j+(10*(i-1))] = i;
		}
	}
	random_shuffle(pilaCartas.begin(), pilaCartas.end());
	dictionary.insert(make_pair(Colores::Any, 0));
	dictionary.insert(make_pair(Colores::Black, 1));
	dictionary.insert(make_pair(Colores::Blue, 2));
	dictionary.insert(make_pair(Colores::Green, 3));
	dictionary.insert(make_pair(Colores::Orange, 4));
	dictionary.insert(make_pair(Colores::Pink, 5));
	dictionary.insert(make_pair(Colores::Red, 6));
	dictionary.insert(make_pair(Colores::White, 7));
	dictionary.insert(make_pair(Colores::Yellow, 8));
	Random r;
	ManoIA = vector<int>(5);
	for (int i = 0; i < ManoIA.size(); i++) {
		ManoIA[i] = pilaCartas[0];
		pilaCartas.erase(pilaCartas.begin());
	}
	ManoJugador = vector<int>(5);
	for (int i = 0; i < ManoJugador.size(); i++) {
		ManoJugador[i] = pilaCartas[0];
		pilaCartas.erase(pilaCartas.begin());
	}
	CartasenMesa =vector<int>(5);
	for (int i = 0; i < CartasenMesa.size(); i++) {
		CartasenMesa[i] = pilaCartas[0];
		pilaCartas.erase(pilaCartas.begin());
	}
	//{puntaje,{salida,llegada}}
	piladeRutas = { {4, { 0,33 } },{ 10,{ 0,16 }}, {12,{ 11,14 }}, {13,{ 15,32 }}, {12,{ 10,12 }},{8,{1,2}} };
	random_shuffle(piladeRutas.begin(), piladeRutas.end());
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
void JuegoC::darRuta(int Player) {
	if (Player == IA) {
		rutaIA = piladeRutas.front();
		piladeRutas.erase(piladeRutas.begin());
	}
	else {
		if (Player == PLAYER) {
			rutaJugador = piladeRutas.front();
			piladeRutas.erase(piladeRutas.begin());
		}
	}
}
void JuegoC::obtnerRuta(int s,int t) {
	links = vector<int>(nEstaciones, -1);
	djkstra(s, &links, 1);
	//pila para recuperar el orden de las aristas
	st = stack<ii>();
	st.push({ links[t],t });
	//llenamos la pila
	poner_camino(&st, links[t]);
	staux = st;
	links = vector<int>(nEstaciones, -1);
	almostDjkstra(s, &links, t);
	st.push({ links[t],t });
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
void JuegoC::almostDjkstra(int inicio, vector<int>*links, int jugador) {
	auto graphBak = grafo;
	auto sts = st;
	//en este while descartamos el camino mas corto para que el siguiente llamado de la funcion djkstra nos de el segundo camino mas corto
	while (!sts.empty())
	{
		auto aux = sts.top(); sts.pop();
		int u = aux.first, v = aux.second;
		for (int i = 0; i < grafo[u].size(); i++) {
			if (grafo[u][i].est_llegada == v) {
				grafo[u][i].dueño = PLAYER;
			}
		}

		djkstra(inicio, links, jugador);
	}

	grafo = graphBak;
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
	if (owner == IA) {
		unionset(local, destino, &psetIA);
	}
	else {
		unionset(local, destino, &psetJugador);
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
//Obtiene el peso de la arista
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
	for (int i = 0; i < ManoIAs.size(); i++) {
		if (ManoIAs.at(i) == color || ManoIAs.at(i)==Colores::Any)
			cont++;
	}
	return cont;
}
bool JuegoC::verificarCaminoCompleto(vector<string>vcolors, int u, int v) {
	bool completado = false;
	ManoIAs.clear();
	for (int i = 0; i < ManoIA.size(); i++) {
		ManoIAs.push_back(colorIndexToString(ManoIA.at(i)));
	}
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
			if (count(ManoIAs.begin(), ManoIAs.end(), Colores::Any) >= pesoaux ||
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Black) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Blue) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Green) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Orange) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Pink) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Red) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::White) >= pesoaux || 
				count(ManoIAs.begin(), ManoIAs.end(), Colores::Yellow) >= pesoaux) {
				completado = true;
			}
		}
	}
	return completado;
}

//funcion que retorna inicializa un vector con los pesos de los caminos, el color y el puntaje de prioridad de cada camino perteneciente a la ruta
priority_queue<Camino> JuegoC::priorizarCaminos() {
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
//Retorna la información del camino mas corto
String^ JuegoC::generarStringCaminos() {
	String^resp = "";
	int size = st.size();
	auto sts = st;
	//impresion de caminos(sujeta a cambios porque no es necesario)
	for (int i = 0; i < size; i++) {
		auto aux = sts.top(); sts.pop();
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

bool compare(int i, int j) { return (i>j); }
auto JuegoC::definirColorMenosImporMano(int peso) {//El peso nos ayuda a escoger el color mas cercano que tengamos para completar ese camino
	auto sts = priorizarCaminos();
	int size = sts.size();
	vector<bool>vcolorUtilizados = vector<bool>(9);
	for (int i = 0; i < size; i++) {
		auto aux = sts.top(); sts.pop();
		vcolorUtilizados[dictionary[aux.color]] = 1;
	}
	vector<int>CantidadCartasPorColorNoUsadas = vector<int>(9);
	for (int i = 0; i < ManoIA.size(); i++) {
		if(vcolorUtilizados[ManoIA[i]]==0)
			CantidadCartasPorColorNoUsadas[ManoIA[i]] += 1;
	}


	sort(CantidadCartasPorColorNoUsadas.begin(),CantidadCartasPorColorNoUsadas.end(),compare);
 	int max = 0;
	vector<int> color;
	for (int i = 0; i < CantidadCartasPorColorNoUsadas.size(); i++) {
		if (CantidadCartasPorColorNoUsadas[i] < peso && vcolorUtilizados[i]==0) {
			color.push_back(i);
		}
	}
	return color;
}

string JuegoC::colorIndexToString(int i) {
	switch (i) {
	case 0:
		return Colores::Any; break;
	case 1:
		return Colores::Black; break;
	case 2:
		return Colores::Blue; break;
	case 3:
		return Colores::Green; break;
	case 4:
		return Colores::Orange; break;
	case 5:
		return Colores::Pink; break;
	case 6:
		return Colores::Red; break;
	case 7:
		return Colores::White; break;
	case 8:
		return Colores::Yellow; break;
	}
}

bool JuegoC::hayEnMesa(string color,int *pos) {
	vector<string>CartasenMesas;
	for (int i = 0; i < CartasenMesa.size(); i++){
		CartasenMesas.push_back(colorIndexToString(CartasenMesa[i]));
	}

	for (int i = 0; i < CartasenMesas.size(); i++) {
		if (color == CartasenMesas[i]) {
			*pos = i;
			return true;
		}
	}
	return false;
}
void JuegoC::cogerCarta(int color, int pos) {
	CartasenMesa.erase(CartasenMesa.begin() + pos);
	ManoIA.push_back(color);
	Random r;
	CartasenMesa.push_back(pilaCartas[0]);
	pilaCartas.erase(pilaCartas.begin());
}
void JuegoC::escogerCarta() {
	auto pq = priorizarCaminos();
	bool escogio = false;
	while (!pq.empty()) {
		auto caminoP = pq.top(); pq.pop();
		int pos = -1;//falta cuando la prioridad sea cero
		if (caminoP.color != Colores::Any) {
			if (hayEnMesa(caminoP.color, &pos)) {
				escogio = true;
				cogerCarta(dictionary[caminoP.color], pos);
				break;
			}
			else {
				continue;
			}
		}
		else {
			
			auto color = definirColorMenosImporMano(caminoP.peso);
			if (color.size()==0)continue;
			bool roto = false;
			for (int j = 0; j < color.size(); j++) {
				if (hayEnMesa(colorIndexToString(color[j]), &pos)) {
					cogerCarta(color[j], pos);
					escogio = true;
					roto = true;
					break;
				}
			}
			if (roto == true)break;
		}
	}
	if (escogio == false) {
		cogerCarta(CartasenMesa[0], 0);
		escogio = true;
	}
}
//llamar esta funcion cada vez que se agarre una carta del tablero
void JuegoC::ReponerCartaTablero() {
	Random r;
	CartasenMesa.push_back(r.Next(0, 9));
}
bool JuegoC::CumploCosto(Camino c) {
	bool r = false;
	vector<int>CartasEnManoIA = vector<int>(9);
	for (int i = 0; i < ManoIA.size(); i++) {
		CartasEnManoIA[ManoIA[i]] += 1;
	}
	if (CartasEnManoIA[dictionary[c.color]] >= c.peso)
		r = true;
	return r;
}
bool JuegoC::CumploCosto(string color,int peso) {
	bool r = false;
	vector<int>CartasEnManoIA = vector<int>(9);
	for (int i = 0; i < ManoIA.size(); i++) {
		CartasEnManoIA[ManoIA[i]] += 1;
	}
	if (CartasEnManoIA[dictionary[color]] >= peso)
		r = true;
	return r;
}
void JuegoC::eliminarCartas(int jugador, int color, int peso) {
	if (jugador == IA) {
		for (int i = 0; i < ManoIA.size(); i++) {
			if (peso == 0)break;
			if (ManoIA[i] == color) {
				pilaCartas.push_back(ManoIA[i]);
				ManoIA.erase(ManoIA.begin() + i);
				peso--;
			}
		}
	}
	else {
		if (jugador == PLAYER) {
			for (int i = 0; i < ManoJugador.size(); i++) {
				if (peso == 0)break;
				if (ManoJugador[i] == color) {
					pilaCartas.push_back(ManoIA[i]);
					ManoJugador.erase(ManoJugador.begin() + i);
					peso--;
				}
			}
		}
	}
	random_shuffle(pilaCartas.begin(), pilaCartas.end());
}
bool JuegoC::verCaminoDueño(int u,int v) {
	int p;
	bool r = false;
	for (int i = 0; i < grafo[u].size(); i++) {
		if (grafo[u][i].est_llegada == v) {
			p = grafo[u][i].dueño;
			if (p == IA) {
				 r= true;
			}
		}
	}
	return r;
}
void JuegoC::RealizarJugada() {
	auto pq = priorizarCaminos();
	bool jugo = false;
	while (!pq.empty() && jugo == false) {
		auto aux = pq.top(); pq.pop();
		if (!verCaminoDueño(aux.est_llegada, aux.est_salida)) {
			if (aux.color != Colores::Any) {
				if (CumploCosto(aux)) {
					asignarRielJugador(aux.est_salida, aux.est_llegada, aux.color, IA);
					eliminarCartas(IA, dictionary[aux.color], aux.peso);
					jugo = true;
				}
			}
			else {
				//iteramos sobre los colores
				for (int i = 1; i < 9; i++) {

					if (CumploCosto(colorIndexToString(i), aux.peso)) {
						asignarRielJugador(aux.est_salida, aux.est_llegada, Colores::Any, IA);
						eliminarCartas(IA, i, aux.peso);
						jugo = true;
						break;
					}
				}
			}
		}
	}
}

bool JuegoC::terminoRuta(int owner) {
	return owner == IA ? isSameSet(rutaIA.second.first, rutaIA.second.second, &psetIA) :
								isSameSet(rutaJugador.second.first, rutaJugador.second.second, &psetJugador);
	/*auto sts = staux;
	bool predicade = true;
	while(!sts.empty()){
		auto aux = sts.top(); sts.pop();
		int u = aux.first, v = aux.second;
		int p;
		for (int i = 0; i < grafo[u].size(); i++) {
			if (grafo[u][i].est_llegada == v) {
				p = grafo[u][i].dueño;
				if (p == PLAYER||p==0) {
					predicade = false;
				}
			}
		}
	}
	return predicade;*/
}


