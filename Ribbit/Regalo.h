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
	/// Resumen de Regalo
	/// </summary>
	public ref class Regalo : public System::Windows::Forms::Form
	{
	private:
		SoundPlayer^ player;
	public:
		Regalo(void)
		{
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//Regalo.wav");
			player->Load(); // Cargar el sonido en memoria
			player->Play(); // Reproducir 
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
		/// </summary>
		~Regalo()
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

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Regalo::typeid));
			this->BTNCERRAR = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// BTNCERRAR
			// 
			this->BTNCERRAR->BackColor = System::Drawing::Color::Gold;
			this->BTNCERRAR->Font = (gcnew System::Drawing::Font(L"Leelawadee UI", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTNCERRAR->ForeColor = System::Drawing::Color::Maroon;
			this->BTNCERRAR->Location = System::Drawing::Point(413, 437);
			this->BTNCERRAR->Margin = System::Windows::Forms::Padding(2);
			this->BTNCERRAR->Name = L"BTNCERRAR";
			this->BTNCERRAR->Size = System::Drawing::Size(241, 39);
			this->BTNCERRAR->TabIndex = 4;
			this->BTNCERRAR->Text = L"ABRIR AHORA";
			this->BTNCERRAR->UseVisualStyleBackColor = false;
			this->BTNCERRAR->Click += gcnew System::EventHandler(this, &Regalo::BTNCERRAR_Click);
			// 
			// Regalo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1074, 581);
			this->Controls->Add(this->BTNCERRAR);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Regalo";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &Regalo::Regalo_Load);
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
	private: System::Void BTNCERRAR_Click(System::Object^ sender, System::EventArgs^ e) {
		// Marca expl�citamente que el regalo se abri� a prop�sito (bot�n), y no cerrando con la X
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
	private: System::Void Regalo_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}