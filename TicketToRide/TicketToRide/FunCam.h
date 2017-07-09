#pragma once
#include"JuegoC.h"
using namespace System::Drawing;

typedef vector<int>vi;
typedef vector<vi>cam;

class FunCam
{
public:
	vector<cam>caminos;
	vi camino_en_coordenadas;
	int x, y;


public:
	FunCam() {
		this->caminos = vector<cam>(55);
		//this->camino_en_coordenadas = vi(20);
		this->x = 0; this->y = 0;
	}

	void Dibujar(Graphics^gr) {
		for (int i = 0; i < this->camino_en_coordenadas.size(); i += 2) {
			gr->FillEllipse(Brushes::Purple, camino_en_coordenadas[i], this->camino_en_coordenadas[i + 1], 5, 5);
		}
	};
	void dibujar_punto(int x, int y) {
		this->camino_en_coordenadas.push_back(x);
		this->camino_en_coordenadas.push_back(y);
	};
	void quitar_punto(Graphics gr) {};
	void terminar_camino() {};


};