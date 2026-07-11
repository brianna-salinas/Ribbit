#pragma once

namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;
	/// <summary>
	/// Resumen de Presentacion
	/// </summary>
	public ref class Presentacion : public System::Windows::Forms::Form
	{
	private:
		SoundPlayer^ player;

	public:
		Presentacion(void)
		{
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//opening.wav");
			player->Load();       // Cargar el sonido en memoria
			player->PlayLooping(); // Reproducir en bucle
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Presentacion()
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
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Presentacion::typeid));
			this->SuspendLayout();
			// 
			// Presentacion
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1059, 541);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Presentacion";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &Presentacion::Presentacion_Load);
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
	private: System::Void Presentacion_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
