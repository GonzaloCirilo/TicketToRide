#pragma once
#include "Result.h"
#include "Structs.h"
#include "ArchiveManager.h"
#include <queue>
#include <functional>
#include <stack>
typedef pair<int, int>ii;
typedef vector<vector<Camino>>Graph;
namespace TicketToRide {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for frmJuego
	/// </summary>
	public ref class frmJuego : public System::Windows::Forms::Form
	{
	public:
		frmJuego(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmJuego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pcbTablero;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmJuego::typeid));
			this->pcbTablero = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pcbTablero))->BeginInit();
			this->SuspendLayout();
			// 
			// pcbTablero
			// 
			this->pcbTablero->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pcbTablero.Image")));
			this->pcbTablero->Location = System::Drawing::Point(-1, 1);
			this->pcbTablero->Name = L"pcbTablero";
			this->pcbTablero->Size = System::Drawing::Size(1024, 683);
			this->pcbTablero->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pcbTablero->TabIndex = 0;
			this->pcbTablero->TabStop = false;
			// 
			// frmJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1014, 661);
			this->Controls->Add(this->pcbTablero);
			this->Name = L"frmJuego";
			this->Text = L"frmJuego";
			this->Load += gcnew System::EventHandler(this, &frmJuego::frmJuego_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pcbTablero))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		int nEstaciones;
	void Djkstra(Graph _grafo,int inicio,vector<int>*links,int jugador) {
		vector<int>distancias = vector<int>(nEstaciones,-1);
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
			int adyacente=-1;
			if (distancias[nodo] >= pesonodo) {
				for (int i = 0; i < _grafo[nodo].size(); i++) {
					//este if es para descartar los caminos repetitivos del mismo peso
					if (adyacente != _grafo[nodo][i].est_llegada ) {
						adyacente = _grafo[nodo][i].est_llegada;
						int peso = _grafo[nodo][i].peso;
						int posiblepeso = pesonodo + peso;
						//se podria gregar otra condicion para que elija el camino con menor varianza de pesos
						if ((distancias[adyacente] == -1 || distancias[adyacente] > posiblepeso ||
							(distancias[adyacente] == posiblepeso && nodosAc[nodo] >= nodosAc[adyacente])
							)&& !obtener_colores(nodo, adyacente, _grafo,jugador).empty()) {
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
	void AsignarRielJugador(Graph* _graph, int local, int destino, string color,int owner) {
		for (int i = 0; i < _graph->at(local).size(); i++) {
			if (_graph->at(local).at(i).est_llegada == destino&&_graph->at(local).at(i).color == color) {
				_graph->at(local).at(i).due�o = owner;
			}
		}
		for (int i = 0; i < _graph->at(destino).size(); i++) {
			if (_graph->at(destino).at(i).est_llegada == local&&_graph->at(destino).at(i).color == color) {
				_graph->at(destino).at(i).due�o = owner;
			}
		}
	}

	//funcion para poblar la pila de caminos a seguir
	void poner_camino(stack<ii>*st, int t, vector<int>links) {
		if (t == -1) {
			st->pop();
			return;
		}
		st->push({ links[t],t });
		poner_camino(st, links[t], links);
	}
	//funcion modificable
	string obtener_colores(int u, int v, Graph _grafo,int jugador) {
		string r = "";
		for (int i = 0; i < _grafo[u].size(); i++) {
			if (_grafo[u][i].est_llegada == v &&(_grafo[u][i].due�o==0||_grafo[u][i].due�o==jugador)) {
				r += ""+_grafo[u][i].color + "||";
			}
		}
		if (!r.empty()) {
			r.pop_back();
			r.pop_back();
		}
		return r;
	}
	//puede variar
	int peso(int u, int v, Graph _grafo) {
		int p;
		for (int i = 0; i < _grafo[u].size(); i++) {
			if (_grafo[u][i].est_llegada == v) {
				p = _grafo[u][i].peso;
				break;
			}
		}
		return p;
	}
	vector<string> split(const string& str, const string& delim)
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
	int mirarmano(string color) {
		int cont = 0;
		//Luego reemplazar este string por el arreglo de manos
		vector < string > s= {"Yellow", "Yellow", "Green","Blue","Blue"};
		for (int i = 0; i < s.size();i++) {
			if (s.at(i) == color)
				cont++;
		}
		return cont;
	}
	//funcion que retorna inicializa un vector con los pesos de los caminos, el color y el puntaje de prioridad
	priority_queue<Camino> obtener_Pesos_Costos(stack<ii>ss,vector<Estacion>estaciones,Graph grafo,int due�o) {
		priority_queue<Camino> pq_caminos;
		int size = ss.size();
		//impresion de caminos(sujeta a cambios)
		for (int i = 0; i < size; i++) {
			auto aux = ss.top(); ss.pop();
			int u = estaciones[aux.first].index;
			int v = estaciones[aux.second].index;
			string colors = obtener_colores(u, v, grafo, 1);//falta marcar que rutas ya tienes despues de ejecutar el djikstra
			String^estacion1 = gcnew String(estaciones[aux.first].nombre.c_str());
			String^estacion2 = gcnew String(estaciones[aux.second].nombre.c_str());
			auto vcolors = split(colors, "||");
			bool completado=false;
			for each (auto c in vcolors)
			{
				int pesoaux = peso(u, v, grafo);
				int cartas_mano_color = mirarmano(c) + 1;
				if (cartas_mano_color - 1 == pesoaux) {
					completado = true;
				}
			}

			for each (auto c in vcolors)
			{
				Camino newCami;
				newCami.color = c;
				newCami.est_salida = u;
				newCami.est_llegada = v;
				int pesoaux = peso(u, v, grafo);
				newCami.peso = pesoaux;
				int cartas_mano_color=mirarmano(c)+1;
				double razon = 1;
				if (c.compare("Any")==0)
					razon = 2;
				newCami.prioridad = (1 / pow((double)vcolors.size(),3))*
									(1 / (double) pesoaux)*
									((double) cartas_mano_color)*
									(1/razon)*
									(!completado);//descartar rutas que ya has completado en tu mano y aun
				pq_caminos.push(newCami);
			}
		}
		return pq_caminos;
	}

	//void priorizar caminos
	private: System::Void frmJuego_Load(System::Object^  sender, System::EventArgs^  e) {
		//Clase que permite la lectura de archivos
		ArchiveManager archm;
		//Carga Estaciones
		vector<Estacion> estaciones = vector<Estacion>();
		nEstaciones = archm.Load_Estaciones(&estaciones);
		//Carga Grafo
		Graph grafo = Graph(nEstaciones);
		archm.Load_Grafo(&grafo, nEstaciones);
		//MessageBox::Show("success");

		//Test
		vector<int>links = vector<int>(nEstaciones, -1);
		//Prueba de asignar un riel a jugador para ver si cambia el camino mas corto
		string a = "Any";
		
		/*AsignarRielJugador(&grafo,2, 33, "Any", 2);
		AsignarRielJugador(&grafo, 31, 9, "Yellow", 2);*/
		AsignarRielJugador(&grafo, 26, 11, "Pink", 1);
		//vertices de inicio y salida
		int s = 0; int t = 33;
		Djkstra(grafo, s, &links,1);
		//pila para recuperar el orden de las aristas
		stack<ii>st;
		st.push({ links[t],t });
		//llenamos la pila
		poner_camino(&st, links[t], links);
		//Genera el string con las respuestas
		String^resp = "";
		auto pq = obtener_Pesos_Costos(st, estaciones, grafo,1);
		pq.pop();
		int size = st.size();
		//impresion de caminos(sujeta a cambios)
		for (int i = 0; i < size; i++) {
			auto aux = st.top(); st.pop();
			int u = estaciones[aux.first].index;
			int v = estaciones[aux.second].index;
			String^colors = gcnew String(obtener_colores(u, v, grafo,1).c_str());
			String^estacion1 = gcnew String(estaciones[aux.first].nombre.c_str());
			String^estacion2 = gcnew String(estaciones[aux.second].nombre.c_str());
			resp += "[Camino " + (i + 1) + ": " + estacion1 + "-" + estacion2 + "] [Peso: " + peso(u, v, grafo) +
				"] [Colores:" + colors + "]" + Environment::NewLine;
		}
		
		auto frm = gcnew Result(resp);
		frm->Show();
	}
	
	};
}
