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

		Graphics^g;
		Bitmap^Black;
		Bitmap^Blue;
		Bitmap^Green;
		Bitmap^Orange;
		Bitmap^Pink;
		Bitmap^Red;
		Bitmap^White;
		Bitmap^Yellow;
	private: System::Windows::Forms::PictureBox^  pcbTablero;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lblturno;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  lblpjugador;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  lblpmaquina;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmJuego::typeid));
			this->pcbTablero = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblturno = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lblpjugador = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->lblpmaquina = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pcbTablero))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			this->SuspendLayout();
			// 
			// pcbTablero
			// 
			this->pcbTablero->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pcbTablero.Image")));
			this->pcbTablero->Location = System::Drawing::Point(-1, 1);
			this->pcbTablero->Name = L"pcbTablero";
			this->pcbTablero->Size = System::Drawing::Size(1020, 659);
			this->pcbTablero->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pcbTablero->TabIndex = 0;
			this->pcbTablero->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(491, 665);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(45, 81);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(556, 665);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(45, 81);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Visible = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(623, 665);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(45, 81);
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Visible = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(692, 665);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(45, 81);
			this->pictureBox4->TabIndex = 4;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Visible = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(755, 665);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(45, 81);
			this->pictureBox5->TabIndex = 5;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Visible = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(821, 665);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(45, 81);
			this->pictureBox6->TabIndex = 6;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Visible = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(891, 665);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(45, 81);
			this->pictureBox7->TabIndex = 7;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Visible = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(960, 665);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(45, 81);
			this->pictureBox8->TabIndex = 8;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Black;
			this->label1->Location = System::Drawing::Point(9, 675);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 19);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Turno: ";
			// 
			// lblturno
			// 
			this->lblturno->AutoSize = true;
			this->lblturno->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblturno->ForeColor = System::Drawing::Color::Black;
			this->lblturno->Location = System::Drawing::Point(105, 675);
			this->lblturno->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblturno->Name = L"lblturno";
			this->lblturno->Size = System::Drawing::Size(15, 19);
			this->lblturno->TabIndex = 10;
			this->lblturno->Text = L"1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Location = System::Drawing::Point(9, 719);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(95, 19);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Mi Puntaje: ";
			// 
			// lblpjugador
			// 
			this->lblpjugador->AutoSize = true;
			this->lblpjugador->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblpjugador->ForeColor = System::Drawing::Color::Black;
			this->lblpjugador->Location = System::Drawing::Point(133, 719);
			this->lblpjugador->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblpjugador->Name = L"lblpjugador";
			this->lblpjugador->Size = System::Drawing::Size(18, 19);
			this->lblpjugador->TabIndex = 12;
			this->lblpjugador->Text = L"0";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Black;
			this->label5->Location = System::Drawing::Point(230, 719);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(138, 19);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Puntaje Maquina: ";
			// 
			// lblpmaquina
			// 
			this->lblpmaquina->AutoSize = true;
			this->lblpmaquina->Font = (gcnew System::Drawing::Font(L"Maiandra GD", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblpmaquina->ForeColor = System::Drawing::Color::Black;
			this->lblpmaquina->Location = System::Drawing::Point(386, 719);
			this->lblpmaquina->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblpmaquina->Name = L"lblpmaquina";
			this->lblpmaquina->Size = System::Drawing::Size(18, 19);
			this->lblpmaquina->TabIndex = 14;
			this->lblpmaquina->Text = L"0";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &frmJuego::timer1_Tick);
			// 
			// frmJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::Sienna;
			this->ClientSize = System::Drawing::Size(1258, 741);
			this->Controls->Add(this->lblpmaquina);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->lblpjugador);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->lblturno);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pcbTablero);
			this->ForeColor = System::Drawing::Color::Maroon;
			this->Name = L"frmJuego";
			this->Text = L"frmJuego";
			this->Load += gcnew System::EventHandler(this, &frmJuego::frmJuego_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pcbTablero))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		int nEstaciones;
		JuegoC *objControlador = new JuegoC();


	//void priorizar caminos
	private: System::Void frmJuego_Load(System::Object^  sender, System::EventArgs^  e) {

		Black = gcnew Bitmap(this->pictureBox1->Image);
		Blue = gcnew Bitmap(this->pictureBox2->Image);
		Green = gcnew Bitmap(this->pictureBox3->Image);
		Orange = gcnew Bitmap(this->pictureBox4->Image);
		Pink = gcnew Bitmap(this->pictureBox5->Image);
		Red = gcnew Bitmap(this->pictureBox6->Image);
		White = gcnew Bitmap(this->pictureBox7->Image);
		Yellow = gcnew Bitmap(this->pictureBox8->Image);

		Random r;
		//Test
		
		//Prueba de asignar un riel a jugador para ver si cambia el camino mas cortoruta
		objControlador->darRuta(1);//Le damos una ruta a la IA
		objControlador->darRuta(2);	
		String^resp;
		for (int i = 0; i < objControlador->rutaIA.size(); i++) {
			objControlador->JugarIA();
		}
		resp = objControlador->generarStringCaminos();
		//objControlador->obtnerRuta(objControlador->rutaIA.second.first,objControlador->rutaIA.second.second);
		//Genera el string con las respuestas
		/*objControlador->escogerCarta();
		objControlador->RealizarJugada();*/
		auto frm = gcnew Result(resp);
		frm->Show();
		int turnos = 0;

		while (!objControlador->terminoRuta(1,objControlador->rutaIA[0].second.first,objControlador->rutaIA[0].second.second)||
				!objControlador->terminoRuta(1,objControlador->rutaIA[1].second.first,objControlador->rutaIA[1].second.second)) {
			objControlador->JugarIA();
			objControlador->escogerCarta();
			objControlador->escogerCarta();
			objControlador->RealizarJugada();
			turnos++;
		}
	}

	auto escogerImagen(int color) {
		switch (color)
		{
		case 1:
			return Black;
			break;
		case 2:
			return Blue;
			break;
		case 3:
			return Green;
			break;
		case 4:
			return Orange;
			break;
		case 5:
			return Pink;
			break;
		case 6:
			return Red;
			break;
		case 7:
			return White;
			break;
		case 8:
			return Yellow;
			break;
		default:
			break;
		}
	}
	//491; 665 (x;y) 45; 81(w,h)	
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		g = this->CreateGraphics();
		int gWidth = (int)g->VisibleClipBounds.Width;
		int gHeigth = (int)g->VisibleClipBounds.Height;
		BufferedGraphicsContext ^espacioBuffer = BufferedGraphicsManager::Current;
		espacioBuffer->MaximumBuffer = System::Drawing::Size(gWidth + 1, gHeigth + 1);
		BufferedGraphics ^buffer = espacioBuffer->Allocate(g, Drawing::Rectangle(0, 0, gWidth, gHeigth));
		buffer->Graphics->FillRectangle(Brushes::Sienna, Rectangle(0, 0, gWidth, gHeigth));
		int x = 491;
		for (int i = 0; i < objControlador->ManoJugador.size(); i++) {
			auto imagen = escogerImagen(objControlador->ManoJugador[i]);
			buffer->Graphics->DrawImage(imagen, x, 665, 45, 81);
			x += 55;
		}

		int y = 50;
		for (int i = 0; i < objControlador->CartasenMesa.size(); i++) {
			auto imagen = escogerImagen(objControlador->CartasenMesa[i]);
			buffer->Graphics->DrawImage(imagen, 1100, y, 91, 45);
			y += 55;
		}




		buffer->Render(g);
		delete g;
		delete buffer;
	}
};
}