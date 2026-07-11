#include "MenuJuego.h"
#include "Ribbit.h"
#include "Presentacion.h"
#include "Dependencias.h"
using namespace Juego;


int main() {

    
    Presentacion^ presentacion = gcnew Presentacion();
    presentacion->Show();
    _sleep(2000);
    presentacion->Close();
    Application::Run(gcnew Ribbit());
    Application::Run(gcnew MenuJuego());

    return 0;
}
