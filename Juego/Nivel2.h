#pragma once
#include "Juego.h"
#include "ElegirRana.h"
#include "Perdiste.h"
#include "Ganaste.h"


#pragma comment(lib, "winmm.lib") // Librer�a para reproducir sonidos

namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;


	public ref class Nivel2 : public Form {
		ControladorNivel2^ juego;
		int contadorTeclasUp;
		int contadorTeclasDown;
		Keys ultimaTeclaPresionada;
		System::Windows::Forms::Label^ lblContadorUp;
		System::Windows::Forms::Timer^ temporizador; // **Nuevo temporizador independiente**
		bool teclaArribaPresionada = false;
		bool teclaAbajoPresionada = false;
		bool nivelCompletado = false; // Solo true si se lleg� al puntaje de victoria (no al cerrar con la X)
		clock_t tiempoInicio;  // **Ahora correctamente inicializado**
		String^ nombreJugador; // ** Guardar el nombre del jugador**
		int tiempoRestante;

	private:
		SoundPlayer^ musicaNivel;
		clock_t ultimoSonidoPaso;

	public:
		Nivel2(String^ nombreJugador, int skin) {
			InitializeComponent();
			PlaySound(L"img//musica//Nivel2.wav", NULL, SND_ASYNC | SND_LOOP);

			mciSendString(L"open \"img//musica//Salto.wav\" type waveaudio alias salto", NULL, 0, NULL);
			mciSendString(L"open \"img//musica//Recolectar.wav\" type waveaudio alias recolectar", NULL, 0, NULL);


			ultimoSonidoPaso = 0;
			tiempoRestante = 275;
			this->nombreJugador = nombreJugador; // **Guardar el nombre en la clase**
			tiempoInicio = std::clock(); // **Reiniciar el tiempo al abrir**

			// ** Pasar el nombre al ControladorJuego**
			juego = gcnew ControladorNivel2(4, 300, nombreJugador, skin); // PASAR SKIN

			// **Crear temporizador independiente**
			temporizador = gcnew System::Windows::Forms::Timer();
			temporizador->Interval = 1000; // **Cada 1 segundo**
			temporizador->Tick += gcnew System::EventHandler(this, &Nivel2::Temporizador_Tick);
			temporizador->Start();

			contadorTeclasUp = 0;
			contadorTeclasDown = 0;
			ultimaTeclaPresionada = Keys::None;
		}

	protected:
		~Nivel2() {
			DetenerMusica();

			if (clock->Enabled) {
				clock->Stop();
			}
			if (components) {
				delete components;
			}
			//delete juego;
		}

	private:
		void DetenerMusica() {
			if (musicaNivel != nullptr) {
				mciSendString(L"stop musica", NULL, 0, NULL);
				mciSendString(L"close musica", NULL, 0, NULL);

			}
		}


	private: System::Windows::Forms::Timer^ clock;
	private: System::ComponentModel::IContainer^ components;

	private:
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Nivel2::typeid));
			this->clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// clock
			// 
			this->clock->Enabled = true;
			this->clock->Interval = 33;
			this->clock->Tick += gcnew System::EventHandler(this, &Nivel2::clock_Tick);
			// 
			// Nivel2
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1508, 844);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Nivel2";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Nivel2::Nivel2_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Nivel2::Nivel2_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Nivel2::Nivel2_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Nivel2::Nivel2_KeyUp);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Nivel2::Nivel2_MouseMove);
			this->ResumeLayout(false);

		}




		Void Nivel2_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			if (clock->Enabled) {
				clock->Stop();

				PlaySound(NULL, NULL, SND_PURGE);
				mciSendString(L"stop salto", NULL, 0, NULL);
				mciSendString(L"close salto", NULL, 0, NULL);
				mciSendString(L"stop recolectar", NULL, 0, NULL);
				mciSendString(L"close recolectar", NULL, 0, NULL);
			}
			delete juego; // La decisi�n de avanzar o no depende solo de "nivelCompletado", ya no hace falta leer "juego" ac�

			DetenerMusica();

			if (nivelCompletado) {
				// Se lleg� al puntaje de victoria: avanzar al siguiente nivel
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
			}
			else {
				// Se qued� sin vidas, se acab� el tiempo, o se cerr� la ventana manualmente
				// sin completar el nivel: en todos esos casos NO se debe avanzar.
				this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			}
		}

		// **TEMPORIZADOR - Reduce el tiempo cada segundo**
		Void Temporizador_Tick(Object^ sender, EventArgs^ e) {
			if (tiempoRestante > 0) {
				tiempoRestante--; // Reducir tiempo

			}

			// **Si el tiempo se acaba, el jugador pierde autom�ticamente**

			if (tiempoRestante == 0) {
				temporizador->Stop();
				juego->SetJugadorVidas(0); // Restar todas las vidas

				if (juego->GetJugadorVidas() > 0) {
					MessageBox::Show("Error: Las vidas no se actualizaron correctamente", "Debug");
				}

				// **Soluci�n: Marcar como perdido y cerrar**
				this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->Close();
			}

		}

		Void clock_Tick(Object^ sender, EventArgs^ e) {
			Graphics^ g = this->CreateGraphics();
			BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
			BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

			// DIBUJAR EL FONDO
			bf->Graphics->DrawImage(this->BackgroundImage, 0, 0, this->ClientSize.Width, this->ClientSize.Height);
			juego->Mover(bf->Graphics, 1);
			juego->Mostrar(bf->Graphics);
			bf->Render(g);

			//  **VERIFICAR SI GAN� EL NIVEL**
			if (juego->GetPuntaje() >= 40) {
				clock->Stop();
				this->Hide();  // Ocultar el nivel

				//  Mostrar la ventana de "Ganaste"
				Ganaste^ ganasteForm = gcnew Ganaste();
				ganasteForm->ShowDialog();

				//  Cerrar el nivel actual y permitir continuar al siguiente
				nivelCompletado = true; // Solo aqu� se considera realmente "ganado"
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
				this->Close();
			}

			// **VERIFICAR SI PERDI� (VIDAS == 0)**
			if (juego->GetJugadorVidas() == 0) {
				clock->Stop();
				temporizador->Stop(); // **Detener el temporizador tambi�n**
				this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				this->Close();
			}
		}





		Void Nivel2_KeyDown(Object^ sender, KeyEventArgs^ e) {
			clock_t tiempoActual = std::clock();

			if (e->KeyCode == Keys::Up && !teclaArribaPresionada) {
				teclaArribaPresionada = true;
				juego->MovimientoJugador(true, e->KeyCode);
				mciSendString(L"play salto from 0", NULL, 0, NULL); // Reproducir desde el inicio
				ultimoSonidoPaso = tiempoActual;
			}
			else if (e->KeyCode == Keys::Down && !teclaAbajoPresionada) {
				teclaAbajoPresionada = true;
				juego->MovimientoJugador(true, e->KeyCode);
				mciSendString(L"play salto from 0", NULL, 0, NULL);
				ultimoSonidoPaso = tiempoActual;
			}
			else {
				juego->MovimientoJugador(true, e->KeyCode);
			}

			if (e->KeyCode == Keys::Space) {
				mciSendString(L"play recolectar from 0", NULL, 0, NULL);
			}

			if (((tiempoActual - ultimoSonidoPaso) / (double)CLOCKS_PER_SEC) >= 0.5) {
				mciSendString(L"play salto", NULL, 0, NULL);
				ultimoSonidoPaso = tiempoActual;
			}

			juego->VerificarColisionConRanita(e->KeyCode);
		}

		Void Nivel2_KeyUp(Object^ sender, KeyEventArgs^ e) {
			if (e->KeyCode == Keys::Up) {
				teclaArribaPresionada = false;
			}
			else if (e->KeyCode == Keys::Down) {
				teclaAbajoPresionada = false;
			}
			juego->MovimientoJugador(false, e->KeyCode);
		}

		Void Nivel2_MouseMove(Object^ sender, MouseEventArgs^ e) {
			//this->Text = "X: " + e->X + " Y: " + e->Y;
		}

	private: System::Void Nivel2_Load(System::Object^ sender, System::EventArgs^ e) {}
	};
}