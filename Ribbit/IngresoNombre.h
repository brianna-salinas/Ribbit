#pragma once
#include <string>

namespace Juego {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class IngresoNombre : public System::Windows::Forms::Form
	{
	public:
		String^ nombreJugador;

		IngresoNombre(void)
		{
			InitializeComponent();
		}

	protected:
		~IngresoNombre()
		{
			if (components)
			{
				delete components;
			}
		}

	private:

		System::Windows::Forms::TextBox^ txtNombre;
		System::Windows::Forms::Button^ btnAceptar;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(IngresoNombre::typeid));
			this->txtNombre = (gcnew System::Windows::Forms::TextBox());
			this->btnAceptar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// txtNombre
			// 
			this->txtNombre->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 11.25F, System::Drawing::FontStyle::Bold));
			this->txtNombre->Location = System::Drawing::Point(130, 114);
			this->txtNombre->MaxLength = 10;
			this->txtNombre->Name = L"txtNombre";
			this->txtNombre->Size = System::Drawing::Size(200, 27);
			this->txtNombre->TabIndex = 1;
			this->txtNombre->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnAceptar
			// 
			this->btnAceptar->BackColor = System::Drawing::Color::Green;
			this->btnAceptar->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 11.25F, System::Drawing::FontStyle::Bold));
			this->btnAceptar->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnAceptar->Location = System::Drawing::Point(155, 159);
			this->btnAceptar->Name = L"btnAceptar";
			this->btnAceptar->Size = System::Drawing::Size(149, 37);
			this->btnAceptar->TabIndex = 2;
			this->btnAceptar->Text = L"Aceptar";
			this->btnAceptar->UseVisualStyleBackColor = false;
			this->btnAceptar->Click += gcnew System::EventHandler(this, &IngresoNombre::btnAceptar_Click);
			// 
			// IngresoNombre
			// 
			this->BackColor = System::Drawing::Color::PaleGreen;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(474, 266);
			this->Controls->Add(this->txtNombre);
			this->Controls->Add(this->btnAceptar);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"IngresoNombre";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &IngresoNombre::IngresoNombre_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		// Evento cuando se presiona Aceptar
		void btnAceptar_Click(System::Object^ sender, System::EventArgs^ e)
		{
			nombreJugador = txtNombre->Text;
			if (String::IsNullOrWhiteSpace(nombreJugador)) {
				MessageBox::Show("Por favor, ingrese un nombre válido.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			this->Close(); // Cierra el formulario
		}
	private: System::Void IngresoNombre_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
