#pragma once
#include <Windows.h>
namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class HistoriaFinal : public System::Windows::Forms::Form
	{
	private:
		PictureBox^ fondoImagen;
		System::Windows::Forms::Button^ buttonContinuar;
		int skinSeleccionada = 1;
		SoundPlayer^ player;
	public:
		HistoriaFinal()
		{
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//HistoriasFinal.wav");
			player->Load();       // Cargar el sonido en memoria
			player->PlayLooping(); // Reproducir en bucle
			ConfigurarFondo();
		}

	protected:
		~HistoriaFinal()
		{
			if (player != nullptr) {
				player->Stop();  // Detener sonido
				delete player;   // Liberar memoria
				player = nullptr;
			}

			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->fondoImagen = (gcnew System::Windows::Forms::PictureBox());
			this->buttonContinuar = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fondoImagen))->BeginInit();
			this->SuspendLayout();
			// 
			// fondoImagen
			// 
			this->fondoImagen->Dock = System::Windows::Forms::DockStyle::Fill;
			this->fondoImagen->Location = System::Drawing::Point(0, 0);
			this->fondoImagen->Name = L"fondoImagen";
			this->fondoImagen->Size = System::Drawing::Size(1300, 800);
			this->fondoImagen->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->fondoImagen->TabIndex = 0;
			this->fondoImagen->TabStop = false;
			this->fondoImagen->Click += gcnew System::EventHandler(this, &HistoriaFinal::fondoImagen_Click);
			// 
			// buttonContinuar
			// 
			this->buttonContinuar->BackColor = System::Drawing::Color::White;
			this->buttonContinuar->Font = (gcnew System::Drawing::Font(L"Tahoma", 18, System::Drawing::FontStyle::Bold));
			this->buttonContinuar->ForeColor = System::Drawing::Color::Black;
			this->buttonContinuar->Location = System::Drawing::Point(990, 620);
			this->buttonContinuar->Name = L"buttonContinuar";
			this->buttonContinuar->Size = System::Drawing::Size(200, 60);
			this->buttonContinuar->TabIndex = 1;
			this->buttonContinuar->Text = L"CONTINUAR";
			this->buttonContinuar->UseVisualStyleBackColor = false;
			this->buttonContinuar->Click += gcnew System::EventHandler(this, &HistoriaFinal::buttonContinuar_Click);
			// 
			// HistoriaFinal
			// 
			this->ClientSize = System::Drawing::Size(1300, 800);
			this->Controls->Add(this->fondoImagen);
			this->Controls->Add(this->buttonContinuar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"HistoriaFinal";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fondoImagen))->EndInit();

			//  Asegurar que los botones estén al frente
			this->buttonContinuar->BringToFront();

			this->ResumeLayout(false);

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


#pragma endregion

		/// <summary>
		/// Método para cambiar la imagen según el índice
		/// </summary>
		void ConfigurarFondo()
		{
			// Rutas de las imágenes
			String^ imagen4 = "img/Historia/H_final.png";
			fondoImagen->Image = Image::FromFile(imagen4);
		}

	private:
		System::Void buttonContinuar_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();  // Cierra la ventana
		}

	private: System::Void fondoImagen_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
