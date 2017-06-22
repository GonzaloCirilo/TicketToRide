#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <gcroot.h>
#include "Structs.h"
using namespace System;
using namespace std;
class ArchiveManager
{
public:
	ifstream arch;
public:
	ArchiveManager();
	~ArchiveManager();
	int Load_Estaciones(vector<Estacion>* _estaciones);
	void Load_Grafo(vector<vector<Camino>> *_grafo, int nEstaciones);
};

