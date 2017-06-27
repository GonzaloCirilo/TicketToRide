#include "ArchiveManager.h"



ArchiveManager::ArchiveManager()
{
}


ArchiveManager::~ArchiveManager()
{
}


int ArchiveManager::Load_Estaciones(vector<Estacion>* _estaciones)
{
	char*nArchivoEtaciones = "Estaciones_US.csv";
	arch.open(nArchivoEtaciones);
	string linea;
	string index, nombre;
	Estacion est;
	while (getline(arch, linea)) {
		stringstream ss(linea);
		getline(ss, index, ',');
		getline(ss, nombre, ',');
		est.index = atoi(index.c_str());
		est.nombre = nombre;
		_estaciones->push_back(est);
	}
	arch.close();
	return _estaciones->size();
}
vector<string> ArchiveManager::split(const string& str, const string& delim)
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

void ArchiveManager::Load_Grafo(vector<vector<Camino>> *_grafo, int nEstaciones)
{
	char* nArchivoGrafo = "Grafo_US.csv";
	arch.open(nArchivoGrafo);
	string aux;
	string linea;
	string color;
	Camino cam;
	int i = 0,j = 0;
	while (getline(arch, linea)) {
		stringstream ss(linea);
		i = 0;
		do {
			getline(ss, aux, ',');
			if (aux == "----") { i++; continue; }
			vector<string> cams = split(aux, "||");
			for (int k = 1; k < cams.size(); k++) {
				cam.est_salida = j;
				cam.est_llegada = i;
				cam.peso = atoi(cams[0].c_str());
				cam.color = cams[k];
				cam.dueño = 0;
				//_grafo.[j].push_back(cam);
				_grafo->at(j).push_back(cam);
			}

			i++;
		} while (i<nEstaciones);
		j++;
	}
	arch.close();
}
