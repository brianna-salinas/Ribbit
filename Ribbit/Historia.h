#pragma once
#include "ElegirRana.h"
#include "Nivel1.h"
#include <Windows.h>
namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class Historia : public System::Windows::Forms::Form
	{
	private:
		PictureBox^ fondoImagen;
		System::Windows::Forms::Button^ buttonContinuar;
		System::Windows::Forms::Button^ buttonElegirSkin;
		int imagenFondoIndex;
		int skinSeleccionada = 1;
		SoundPlayer^ player;
	public:
		Historia(int index)
		{
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//Historias.wav");
			player->Load();       // Cargar el sonido en memoria
			player->PlayLooping(); // Reproducir en bucle
			imagenFondoIndex = index;
			ConfigurarFondo();
		}
		int GetSkinSeleccionada() {
			return skinSeleccionada;
		}

	protected:
		~Historia()
		{
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
			this->buttonElegirSkin = (gcnew System::Windows::Forms::Button());
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
			this->fondoImagen->Click += gcnew System::EventHandler(this, &Historia::fondoImagen_Click_1);
			// 
			// buttonContinuar
			// 
			this->buttonContinuar->BackColor = System::Drawing::Color::White;
			this->buttonContinuar->Font = (gcnew System::Drawing::Font(L"Tahoma", 18, System::Drawing::FontStyle::Bold));
			this->buttonContinuar->ForeColor = System::Drawing::Color::Black;
			this->buttonContinuar->Location = System::Drawing::Point(980, 600);
			this->buttonContinuar->Name = L"buttonContinuar";
			this->buttonContinuar->Size = System::Drawing::Size(200, 60);
			this->buttonContinuar->TabIndex = 1;
			this->buttonContinuar->Text = L"CONTINUAR";
			this->buttonContinuar->UseVisualStyleBackColor = false;
			this->buttonContinuar->Click += gcnew System::EventHandler(this, &Historia::buttonContinuar_Click);
			// 
			// buttonElegirSkin
			// 
			this->buttonElegirSkin->BackColor = System::Drawing::Color::White;
			this->buttonElegirSkin->Font = (gcnew System::Drawing::Font(L"Tahoma", 18, System::Drawing::FontStyle::Bold));
			this->buttonElegirSkin->ForeColor = System::Drawing::Color::Black;
			this->buttonElegirSkin->Location = System::Drawing::Point(980, 680);
			this->buttonElegirSkin->Name = L"buttonElegirSkin";
			this->buttonElegirSkin->Size = System::Drawing::Size(200, 60);
			this->buttonElegirSkin->TabIndex = 2;
			this->buttonElegirSkin->Text = L"ELEGIR SKIN";
			this->buttonElegirSkin->UseVisualStyleBackColor = false;
			this->buttonElegirSkin->Click += gcnew System::EventHandler(this, &Historia::buttonElegirSkin_Click);
			// 
			// Historia
			// 
			this->ClientSize = System::Drawing::Size(1300, 800);
			this->Controls->Add(this->fondoImagen);
			this->Controls->Add(this->buttonContinuar);
			this->Controls->Add(this->buttonElegirSkin);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Historia";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &Historia::Historia_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fondoImagen))->EndInit();

			//  Asegurar que los botones est�n al frente
			this->buttonContinuar->BringToFront();
			this->buttonElegirSkin->BringToFront();

			this->ResumeLayout(false);

		}
#pragma endregion

		/// <summary>
		/// M�todo para cambiar la imagen seg�n el �ndice
		/// </summary>
		void ConfigurarFondo()
		{
			// Rutas de las im�genes
			String^ imagen1 = "img/Historia/H_nivel1.png";
			String^ imagen2 = "img/Historia/H_nivel2.png";
			String^ imagen3 = "img/Historia/H_nivel3.png";

			// Aplicar imagen seg�n el �ndice
			try {
				switch (imagenFondoIndex)
				{
				case 1:
					fondoImagen->Image = Image::FromFile(imagen1);
					break;
				case 2:
					fondoImagen->Image = Image::FromFile(imagen2);
					break;
				case 3:
					fondoImagen->Image = Image::FromFile(imagen3);
					break;
				default:
					fondoImagen->Image = Image::FromFile(imagen1); // Por defecto, la primera imagen
					break;
				}
			}
			catch (...) {
				// Evita errores si no encuentra la imagen
			}
		}

	private:
		System::Void buttonContinuar_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();  // Cierra la ventana
		}


		System::Void buttonElegirSkin_Click(System::Object^ sender, System::EventArgs^ e) {
			ElegirRana^ elegirRanaForm = gcnew ElegirRana(imagenFondoIndex + 1);

			System::Windows::Forms::DialogResult resultado = elegirRanaForm->ShowDialog();

			if (resultado == System::Windows::Forms::DialogResult::OK) {
				this->skinSeleccionada = elegirRanaForm->GetSkinSeleccionada();
				this->Hide();
			}
			delete elegirRanaForm;
		}

	private: System::Void fondoImagen_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void fondoImagen_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Historia_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};

}