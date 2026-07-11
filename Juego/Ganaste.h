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
	/// Resumen de Ganaste
	/// </summary>
	public ref class Ganaste : public System::Windows::Forms::Form
	{
	private:
		SoundPlayer^ player;
	public:
		Ganaste(void)
		{
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//Ganar.wav");
			player->Load();       // Cargar el sonido en memoria
			player->Play(); // Reproducir en bucle
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Ganaste()
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
	private: System::Windows::Forms::Button^ BTNCERRAR;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Ganaste::typeid));
			this->BTNCERRAR = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// BTNCERRAR
			// 
			this->BTNCERRAR->BackColor = System::Drawing::Color::Yellow;
			this->BTNCERRAR->Font = (gcnew System::Drawing::Font(L"Leelawadee", 15.75F, System::Drawing::FontStyle::Bold));
			this->BTNCERRAR->ForeColor = System::Drawing::Color::DarkBlue;
			this->BTNCERRAR->Location = System::Drawing::Point(349, 434);
			this->BTNCERRAR->Margin = System::Windows::Forms::Padding(2);
			this->BTNCERRAR->Name = L"BTNCERRAR";
			this->BTNCERRAR->Size = System::Drawing::Size(370, 39);
			this->BTNCERRAR->TabIndex = 2;
			this->BTNCERRAR->Text = L"PRESIONA PARA CONTINUAR";
			this->BTNCERRAR->UseVisualStyleBackColor = false;
			this->BTNCERRAR->Click += gcnew System::EventHandler(this, &Ganaste::BTNCERRAR_Click);
			// 
			// Ganaste
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1074, 581);
			this->Controls->Add(this->BTNCERRAR);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Ganaste";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &Ganaste::Ganaste_Load);
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

#pragma endregion
	private: System::Void Ganaste_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void BTNCERRAR_Click(System::Object^ sender, System::EventArgs^ e) {
		DetenerMusica();
		this->Close();
	}
	};
}
