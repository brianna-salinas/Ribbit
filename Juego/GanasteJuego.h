#pragma once
#include <conio.h>
#include <stdlib.h>
namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	/// <summary>
	/// Summary for GanasteJuego
	/// </summary>
	public ref class GanasteJuego : public System::Windows::Forms::Form
	{
	private:
		SoundPlayer^ player;
	public:
		GanasteJuego(void)
		{
			InitializeComponent();
			player = gcnew SoundPlayer("img//musica//GanasteJuego.wav");
			player->Load();       // Cargar el sonido en memoria
			player->Play(); // Reproducir 
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GanasteJuego()
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

	protected:

	private:
 
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
 
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GanasteJuego::typeid));
			this->BTNCERRAR = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// BTNCERRAR
			// 
			this->BTNCERRAR->BackColor = System::Drawing::Color::DarkBlue;
			this->BTNCERRAR->Font = (gcnew System::Drawing::Font(L"Leelawadee", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTNCERRAR->ForeColor = System::Drawing::Color::White;
			this->BTNCERRAR->Location = System::Drawing::Point(949, 482);
			this->BTNCERRAR->Margin = System::Windows::Forms::Padding(2);
			this->BTNCERRAR->Name = L"BTNCERRAR";
			this->BTNCERRAR->Size = System::Drawing::Size(45, 38);
			this->BTNCERRAR->TabIndex = 3;
			this->BTNCERRAR->Text = L">>>";
			this->BTNCERRAR->UseVisualStyleBackColor = false;
			this->BTNCERRAR->Click += gcnew System::EventHandler(this, &GanasteJuego::BTNCERRAR_Click);
			// 
			// GanasteJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1074, 581);
			this->Controls->Add(this->BTNCERRAR);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"GanasteJuego";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &GanasteJuego::GanasteJuego_Load);
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
	private: System::Void GanasteJuego_Load(System::Object^ sender, System::EventArgs^ e) {

	}
    private: System::Void BTNCERRAR_Click(System::Object^ sender, System::EventArgs^ e) {
	    player->Stop();
	    this->Close();
    }
};
}
