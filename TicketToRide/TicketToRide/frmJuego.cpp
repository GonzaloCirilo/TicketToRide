#include "frmJuego.h"
using namespace TicketToRide;

[STAThread]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew frmJuego());

}

