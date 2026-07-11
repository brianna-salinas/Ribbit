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
	/// Resumen de Ribbit
	/// </summary>
	public ref class Ribbit : public System::Windows::Forms::Form
	{
	private:
		SoundPlayer^ player;
	public:
		Ribbit(void)
		{
			InitializeComponent();

			player = gcnew SoundPlayer("img//musica//menu.wav");
			player->Load();       // Cargar el sonido en memoria
			player->PlayLooping(); // Reproducir en bucle
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Ribbit()
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
	private: System::Windows::Forms::Button^ btnEmpezar;
	protected:

	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Ribbit::typeid));
			this->btnEmpezar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnEmpezar
			// 
			this->btnEmpezar->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->btnEmpezar, L"btnEmpezar");
			this->btnEmpezar->ForeColor = System::Drawing::Color::Chartreuse;
			this->btnEmpezar->Name = L"btnEmpezar";
			this->btnEmpezar->UseVisualStyleBackColor = false;
			this->btnEmpezar->Click += gcnew System::EventHandler(this, &Ribbit::btnEmpezar_Click);
			// 
			// Ribbit
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->btnEmpezar);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Ribbit";
			this->Load += gcnew System::EventHandler(this, &Ribbit::Ribbit_Load);
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
	private: System::Void btnEmpezar_Click(System::Object^ sender, System::EventArgs^ e) {
		DetenerMusica();
		this->Close();
	}
	private: System::Void Ribbit_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
