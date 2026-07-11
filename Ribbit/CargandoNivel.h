#pragma once

namespace Juego {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class CargandoNivel : public Form {
	private:
		Timer^ timer;
		PictureBox^ pictureBox;
		int nivel;
		SoundPlayer^ player;

	public:
		CargandoNivel(int nivelActual) {
			nivel = nivelActual;
			this->Text = "Cargando...";
			this->Size = System::Drawing::Size(1075, 580); // Ajusta el tamaño según tu imagen
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = Color::Black;

			//Music

			player = gcnew SoundPlayer("img//musica//intercepto.wav");
			player->Load();       // Cargar el sonido en memoria
			player->PlayLooping(); // Reproducir en bucle

			// Crear PictureBox para la imagen
			pictureBox = gcnew PictureBox();
			pictureBox->SizeMode = PictureBoxSizeMode::StretchImage;
			pictureBox->Dock = DockStyle::Fill; // Ocupa toda la ventana
			pictureBox->Image = ObtenerImagenNivel(nivel); // Asignar imagen
			this->Controls->Add(pictureBox);

			// Timer para cerrar la ventana después de 2 segundos
			timer = gcnew Timer();
			timer->Interval = 2000; // 2 segundos
			timer->Tick += gcnew EventHandler(this, &CargandoNivel::CerrarVentana);
			timer->Start();
		}

	private:
		// Método para obtener la imagen del nivel
		Image^ ObtenerImagenNivel(int nivel) {
			String^ ruta = "";
			switch (nivel) {
			case 1: ruta = "img/Ventanas/cargando1.png"; break;
			case 2: ruta = "img/Ventanas/cargando2.png"; break;
			case 3: ruta = "img/Ventanas/cargando3.png"; break;

			}
			return Image::FromFile(ruta);
		}

		~CargandoNivel()
		{

			if (player != nullptr) {
				player->Stop();  // Detener sonido
				delete player;   // Liberar memoria
				player = nullptr;
			}

		}


		// Método para cerrar la ventana
		void CerrarVentana(Object^ sender, EventArgs^ e) {
			timer->Stop();
			this->Close();
		}

		void DetenerMusica()
		{
			if (player != nullptr) {
				player->Stop();  // Detener la música
				delete player;   // Liberar memoria
				player = nullptr;
			}
		}

		 void OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
		{
			DetenerMusica(); // Detiene la música

		}

	private: System::Void InitializeComponent() {
		this->SuspendLayout();
		// 
		// CargandoNivel
		// 
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->ClientSize = System::Drawing::Size(1074, 581);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Name = L"CargandoNivel";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Load += gcnew System::EventHandler(this, &CargandoNivel::CargandoNivel_Load);
		this->ResumeLayout(false);

	}
	private: System::Void CargandoNivel_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	};
}
