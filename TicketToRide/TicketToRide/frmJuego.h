#pragma once
#include "Result.h"
#include "Structs.h"
#include "ArchiveManager.h"
#include "JuegoC.h"
#include <queue>
#include <functional>
#include <stack>
#include <algorithm>
#include <utility>
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
	
	void priorizarCartas(priority_queue<Camino>pilacaminos) {

	}

	//void priorizar caminos
	private: System::Void frmJuego_Load(System::Object^  sender, System::EventArgs^  e) {
		
		//Test
		JuegoC *objControlador = new JuegoC();
		//Prueba de asignar un riel a jugador para ver si cambia el camino mas corto
		objControlador->asignarRielJugador(2, 33, Colores::Any, 2);
		objControlador->asignarRielJugador(31, 9, Colores::Yellow, 2);
		objControlador->obtnerRuta(0, 33);
		//vertices de inicio y salida
		
		
		auto pq = objControlador->priorizarCaminos();
		//pq.pop();
		//Genera el string con las respuestas
		objControlador->escogerCarta();
		String^resp = objControlador->generarStringCaminos();
		auto frm = gcnew Result(resp);
		frm->Show();
	}
	
	};
}
