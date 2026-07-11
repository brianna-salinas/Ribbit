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
	/// Resumen de Perdiste
	/// </summary>
	public ref class Perdiste : public System::Windows::Forms::Form
	{
	private:
		bool volverAlMenu;
		bool salirDelJuego; // true cuando se eligi� "CERRAR JUEGO" (Application::Exit ya fue llamado)
		SoundPlayer^ player;


	public:
		Perdiste() {
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//Gameover.wav");
			volverAlMenu = false;
			salirDelJuego = false;
			player->Load();       // Cargar el sonido en memoria
			player->Play(); // Reproducir

		}


		bool GetVolverAlMenu() {
			return volverAlMenu;
		}

		bool GetSalirDelJuego() {
			return salirDelJuego;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
		/// </summary>
		~Perdiste()
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
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ BTNCERRAR;
	protected:


	private:
		/// <summary>
		/// Variable del dise�ador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necesario para admitir el Dise�ador. No se puede modificar
		/// el contenido de este m�todo con el editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Perdiste::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->BTNCERRAR = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::PaleTurquoise;
			this->button1->Font = (gcnew System::Drawing::Font(L"Leelawadee", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::DarkBlue;
			this->button1->Location = System::Drawing::Point(163, 418);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(223, 42);
			this->button1->TabIndex = 0;
			this->button1->Text = L"JUGAR OTRA VEZ";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Perdiste::button1_Click);
			// 
			// BTNCERRAR
			// 
			this->BTNCERRAR->BackColor = System::Drawing::Color::PaleTurquoise;
			this->BTNCERRAR->Font = (gcnew System::Drawing::Font(L"Leelawadee", 15.75F, System::Drawing::FontStyle::Bold));
			this->BTNCERRAR->ForeColor = System::Drawing::Color::DarkBlue;
			this->BTNCERRAR->Location = System::Drawing::Point(678, 418);
			this->BTNCERRAR->Margin = System::Windows::Forms::Padding(2);
			this->BTNCERRAR->Name = L"BTNCERRAR";
			this->BTNCERRAR->Size = System::Drawing::Size(229, 42);
			this->BTNCERRAR->TabIndex = 1;
			this->BTNCERRAR->Text = L"CERRAR JUEGO";
			this->BTNCERRAR->UseVisualStyleBackColor = false;
			this->BTNCERRAR->Click += gcnew System::EventHandler(this, &Perdiste::BTNCERRAR_Click);
			// 
			// Perdiste
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1074, 581);
			this->Controls->Add(this->BTNCERRAR);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Perdiste";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &Perdiste::Perdiste_Load);
			this->ResumeLayout(false);

		}


		void DetenerMusica()
		{
			if (player != nullptr) {
				player->Stop();  // Detener la m�sica
				delete player;   // Liberar memoria
				player = nullptr;
			}
		}

		void OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
		{
			DetenerMusica(); // Detiene la m�sica

		}

#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		volverAlMenu = true; //  Cambia la variable a `true`
		this->Close();  //  Cierra "Perdiste"
	}
	private: System::Void BTNCERRAR_Click(System::Object^ sender, System::EventArgs^ e) {
		salirDelJuego = true; // Marcar ANTES de Exit para que MenuJuego sepa que no debe volver a mostrarse
		Application::Exit(); // Cierra toda la aplicaci�n

	}
	private: System::Void Perdiste_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}