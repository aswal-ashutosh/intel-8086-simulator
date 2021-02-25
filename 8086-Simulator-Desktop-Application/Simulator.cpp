#include "Simulator.h"

wxIMPLEMENT_APP(Simulator);

Simulator::Simulator()
{

}

Simulator::~Simulator()
{

}

bool Simulator::OnInit()
{
	mainWindow = new MainFrame();
	mainWindow->Show();
	return true;
}