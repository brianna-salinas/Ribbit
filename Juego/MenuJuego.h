#pragma once
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include "Instrucciones.h"
#include "Creditos.h"
#include "Salir.h"
#include "ElegirRana.h"
#include "IngresoNombre.h"
#include "Historia.h"
#include "HistoriaFinal.h"
#include "CargandoNivel.h"
#include "Perdiste.h"
#include "Regalo.h"
#include "AbrirRegalo.h"
#include "GanasteJuego.h"


namespace Juego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MenuJuego
	/// </summary>
	public ref class MenuJuego : public System::Windows::Forms::Form
	{

	public:
		int skinSeleccionado = 1; // Valor predeterminado
		Form^ juego = nullptr;

	public:
		Historia^ miHistoria = nullptr;

	public:
		MenuJuego(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MenuJuego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnIntrucciones;
	private: System::Windows::Forms::Button^ bntCreditos;
	private: System::Windows::Forms::Button^ btnSalir;



	protected:

	protected:

	protected:
	private: System::Windows::Forms::Button^ btnJugar;
	protected:


	private: System::Void btnJugar_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		btnJugar->Size = System::Drawing::Size(110, 50);
	}

	private: System::Void btnJugar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		btnJugar->Size = System::Drawing::Size(120, 60);
	}

	private: System::Void btnJugar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btnJugar->BackColor = Color::Lime;
	}

	private: System::Void btnJugar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btnJugar->BackColor = Color::Green;
	}

	protected:

	protected:

	private:

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MenuJuego::typeid));
			this->btnJugar = (gcnew System::Windows::Forms::Button());
			this->btnIntrucciones = (gcnew System::Windows::Forms::Button());
			this->bntCreditos = (gcnew System::Windows::Forms::Button());
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnJugar
			// 
			this->btnJugar->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnJugar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnJugar.BackgroundImage")));
			this->btnJugar->Font = (gcnew System::Drawing::Font(L"Tahoma", 20.25F, System::Drawing::FontStyle::Bold));
			this->btnJugar->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->btnJugar->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
			this->btnJugar->Location = System::Drawing::Point(391, 192);
			this->btnJugar->Margin = System::Windows::Forms::Padding(2);
			this->btnJugar->Name = L"btnJugar";
			this->btnJugar->Size = System::Drawing::Size(270, 40);
			this->btnJugar->TabIndex = 0;
			this->btnJugar->Text = L"JUGAR";
			this->btnJugar->UseVisualStyleBackColor = false;
			this->btnJugar->Click += gcnew System::EventHandler(this, &MenuJuego::btnJugar_Click);
			// 
			// btnIntrucciones
			// 
			this->btnIntrucciones->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnIntrucciones->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnIntrucciones.BackgroundImage")));
			this->btnIntrucciones->Font = (gcnew System::Drawing::Font(L"Tahoma", 20.25F, System::Drawing::FontStyle::Bold));
			this->btnIntrucciones->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->btnIntrucciones->Location = System::Drawing::Point(391, 236);
			this->btnIntrucciones->Margin = System::Windows::Forms::Padding(2);
			this->btnIntrucciones->Name = L"btnIntrucciones";
			this->btnIntrucciones->Size = System::Drawing::Size(270, 41);
			this->btnIntrucciones->TabIndex = 1;
			this->btnIntrucciones->Text = L"INSTRUCCIONES";
			this->btnIntrucciones->UseVisualStyleBackColor = false;
			this->btnIntrucciones->Click += gcnew System::EventHandler(this, &MenuJuego::btnIntrucciones_Click);
			// 
			// bntCreditos
			// 
			this->bntCreditos->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->bntCreditos->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bntCreditos.BackgroundImage")));
			this->bntCreditos->Font = (gcnew System::Drawing::Font(L"Tahoma", 20.25F, System::Drawing::FontStyle::Bold));
			this->bntCreditos->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->bntCreditos->Location = System::Drawing::Point(391, 281);
			this->bntCreditos->Margin = System::Windows::Forms::Padding(2);
			this->bntCreditos->Name = L"bntCreditos";
			this->bntCreditos->Size = System::Drawing::Size(270, 39);
			this->bntCreditos->TabIndex = 2;
			this->bntCreditos->Text = L"CREDITOS";
			this->bntCreditos->UseVisualStyleBackColor = false;
			this->bntCreditos->Click += gcnew System::EventHandler(this, &MenuJuego::bntCreditos_Click);
			// 
			// btnSalir
			// 
			this->btnSalir->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnSalir->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSalir.BackgroundImage")));
			this->btnSalir->Font = (gcnew System::Drawing::Font(L"Tahoma", 20.25F, System::Drawing::FontStyle::Bold));
			this->btnSalir->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->btnSalir->Location = System::Drawing::Point(391, 324);
			this->btnSalir->Margin = System::Windows::Forms::Padding(2);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(270, 40);
			this->btnSalir->TabIndex = 3;
			this->btnSalir->Text = L"SALIR";
			this->btnSalir->UseVisualStyleBackColor = false;
			this->btnSalir->Click += gcnew System::EventHandler(this, &MenuJuego::btnSalir_Click);
			// 
			// MenuJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1059, 541);
			this->Controls->Add(this->btnSalir);
			this->Controls->Add(this->bntCreditos);
			this->Controls->Add(this->btnIntrucciones);
			this->Controls->Add(this->btnJugar);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximizeBox = false;
			this->Name = L"MenuJuego";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &MenuJuego::MenuJuego_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

		Void btnJugar_Click(System::Object^ sender, System::EventArgs^ e) {
			// Limpiar objetos de una partida anterior por si quedaron sin liberar
			if (juego != nullptr) { delete juego; juego = nullptr; }
			if (miHistoria != nullptr) { delete miHistoria; miHistoria = nullptr; }

			// Crear ventana para ingresar nombre
			IngresoNombre^ ingresoNombreForm = gcnew IngresoNombre();
			ingresoNombreForm->ShowDialog();

			if (!String::IsNullOrWhiteSpace(ingresoNombreForm->nombreJugador)) {
				String^ nombreJugador = ingresoNombreForm->nombreJugador;
				delete ingresoNombreForm;

				//  **NIVEL 1**
				Regalo^ skin1 = gcnew Regalo();
				skin1->ShowDialog();
				if (skin1->DialogResult == System::Windows::Forms::DialogResult::OK) {
					// Solo mostrar la animaci�n de abrir el regalo si se apret� "ABRIR AHORA"
					AbrirRegalo^ RegaloSkin1 = gcnew AbrirRegalo(1);
					RegaloSkin1->ShowDialog();
					delete RegaloSkin1;
				}
				delete skin1;

				miHistoria = gcnew Historia(1);
				miHistoria->ShowDialog();

				CargandoNivel^ cargando1 = gcnew CargandoNivel(1);
				cargando1->ShowDialog();
				delete cargando1;

				skinSeleccionado = miHistoria->GetSkinSeleccionada();
				delete miHistoria; miHistoria = nullptr;

				juego = gcnew Nivel1(nombreJugador, skinSeleccionado);
				juego->DialogResult = System::Windows::Forms::DialogResult::None;  //  Reiniciar el estado antes de mostrar
				juego->ShowDialog();

				// Si el jugador gan�, continuar al siguiente nivel
				if (juego->DialogResult == System::Windows::Forms::DialogResult::OK) {
					delete juego; juego = nullptr; // Ya le�mos el resultado de Nivel1, no hace falta conservarlo

					// **NIVEL 2**
					Regalo^ skin2 = gcnew Regalo();
					skin2->ShowDialog();
					if (skin2->DialogResult == System::Windows::Forms::DialogResult::OK) {
						// Solo mostrar la animaci�n de abrir el regalo si se apret� "ABRIR AHORA"
						AbrirRegalo^ RegaloSkin2 = gcnew AbrirRegalo(2);
						RegaloSkin2->ShowDialog();
						delete RegaloSkin2;
					}
					delete skin2;

					miHistoria = gcnew Historia(2);
					miHistoria->ShowDialog();

					CargandoNivel^ cargando2 = gcnew CargandoNivel(2);
					cargando2->ShowDialog();
					delete cargando2;

					skinSeleccionado = miHistoria->GetSkinSeleccionada();
					delete miHistoria; miHistoria = nullptr;

					juego = gcnew Nivel2(nombreJugador, skinSeleccionado);
					juego->ShowDialog();

					//  Si el jugador gan� Nivel 2, continuar a Nivel 3
					if (juego->DialogResult == System::Windows::Forms::DialogResult::OK) {
						delete juego; juego = nullptr; // Ya le�mos el resultado de Nivel2, no hace falta conservarlo

						// **NIVEL 3**
						Regalo^ skin3 = gcnew Regalo();
						skin3->ShowDialog();
						if (skin3->DialogResult == System::Windows::Forms::DialogResult::OK) {
							// Solo mostrar la animaci�n de abrir el regalo si se apret� "ABRIR AHORA"
							AbrirRegalo^ RegaloSkin3 = gcnew AbrirRegalo(3);
							RegaloSkin3->ShowDialog();
							delete RegaloSkin3;
						}
						delete skin3;

						miHistoria = gcnew Historia(3);
						miHistoria->ShowDialog();

						CargandoNivel^ cargando3 = gcnew CargandoNivel(3);
						cargando3->ShowDialog();
						delete cargando3;

						skinSeleccionado = miHistoria->GetSkinSeleccionada();
						delete miHistoria; miHistoria = nullptr;

						juego = gcnew Nivel3(nombreJugador, skinSeleccionado);
						juego->ShowDialog();

						//  **Si gan� Nivel 3, mostrar GANASTE FINAL**
						if (juego->DialogResult == System::Windows::Forms::DialogResult::OK) {
							HistoriaFinal^ FinalRanas = gcnew HistoriaFinal();
							FinalRanas->ShowDialog();
							delete FinalRanas;
							GanasteJuego^ ganasteFinal = gcnew GanasteJuego();
							ganasteFinal->ShowDialog();
							delete ganasteFinal;
						}
					}
				}

				//  **Si el jugador perdi� en cualquier nivel, mostrar "Perdiste"**
				if (juego->DialogResult == System::Windows::Forms::DialogResult::Cancel) {
					Perdiste^ perdisteForm = gcnew Perdiste();
					this->Hide();
					perdisteForm->ShowDialog();

					bool salir = perdisteForm->GetSalirDelJuego();
					bool volver = perdisteForm->GetVolverAlMenu();
					delete perdisteForm;

					//  Si eligi� "CERRAR JUEGO": la app ya se est� cerrando (Application::Exit),
					//  no tocar "this" (MenuJuego) porque puede estar siendo desechado.
					if (salir) {
						delete juego; juego = nullptr;
						return;
					}

					//  Si elige volver al men�, detener aqu�
					if (volver) {
						delete juego; juego = nullptr;
						this->Show();
						return;
					}
				}

				// **Cuando termina el juego, volver al men� principal**
				delete juego; juego = nullptr;
				this->Show();
			}
			else {
				delete ingresoNombreForm;
			}
		}

		Void btnIntrucciones_Click(Object^ sender, EventArgs^ e) {
			Instrucciones^ frm = gcnew Instrucciones();
			this->Visible = false;
			frm->ShowDialog();
			delete frm;
			this->Visible = true;
		}
		Void bntCreditos_Click(Object^ sender, EventArgs^ e) {
			Creditos^ frm = gcnew Creditos();
			this->Visible = false;
			frm->ShowDialog();
			delete frm;
			this->Visible = true;

		}
		Void btnSalir_Click(Object^ sender, EventArgs^ e) {
			Salir^ frm = gcnew Salir();
			this->Visible = false;
			frm->ShowDialog();
			delete frm;
			this->Visible = true;
		}


	private: System::Void MenuJuego_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};

};