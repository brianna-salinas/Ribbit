#pragma once

namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class AbrirRegalo : public Form {
	private:
		Timer^ timer;
		PictureBox^ pictureBox;
		int regalo;
		SoundPlayer^ player;

	public:
		AbrirRegalo(int RegaloSkin) {
			regalo = RegaloSkin;

			this->Text = "EL REGALO HA SIDO ABIERTO";
			this->Size = System::Drawing::Size(1075, 580); // Ajusta el tamaño según tu imagen
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = Color::Black;

			//Music

			player = gcnew SoundPlayer("img//musica//Abrirregalo.wav");
			player->Load();       // Cargar el sonido en memoria
			player->Play(); // Reproducir en bucle

			// Crear PictureBox para la imagen
			pictureBox = gcnew PictureBox();
			pictureBox->SizeMode = PictureBoxSizeMode::StretchImage;
			pictureBox->Dock = DockStyle::Fill; // Ocupa toda la ventana
			pictureBox->Image = ObtenerImagenNivel(regalo); // Asignar imagen
			this->Controls->Add(pictureBox);

			// Timer para cerrar la ventana después de 2.3 segundos
			timer = gcnew Timer();
			timer->Interval = 2300; // 2.3 segundos
			timer->Tick += gcnew EventHandler(this, &AbrirRegalo::CerrarVentana);
			timer->Start();
		}

	private:
		// Método para obtener la imagen del nivel
		Image^ ObtenerImagenNivel(int regalo) {
			String^ ruta = "";
			switch (regalo) {
			case 1: ruta = "img/Ventanas/SKIN1.png"; break;
			case 2: ruta = "img/Ventanas/SKIN2.png"; break;
			case 3: ruta = "img/Ventanas/SKIN3.png"; break;

			}
			return Image::FromFile(ruta);
		}

		~AbrirRegalo()
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
		// AbrirRegalo
		// 
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->ClientSize = System::Drawing::Size(1074, 581);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Name = L"AbrirRegalo";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Load += gcnew System::EventHandler(this, &AbrirRegalo::AbrirRegalo_Load);
		this->ResumeLayout(false);

	}
	private: System::Void AbrirRegalo_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	};
}
