#pragma once
#include "Entidad.h"
#include <ctime>  


class Aliado :public Entidad
{
public:
	int tipo;

	Aliado(int x, int y, int tipo) {

		this->x = x;
		this->y = y;
		this->tipo = tipo; // Que varie entre 0 o 1 malos o buenos
	}

	Aliado(Bitmap^ img, int index, bool haciaIzquierda, int startX, int startY, int tipo) {
		ancho = 250;
		alto = 82;
		dx = haciaIzquierda ? -4 : -4;
		int separacionX = 160;
		separacionX = ancho + 10;
		x = startX + index * separacionX;
		y = startY;
		this->tipo = tipo; // 0 para malo, 1 para bueno

	}

	bool DebeEliminarse(int pantallaAncho) {
		return (dx < 0 && x + ancho < 0) || (dx > 0 && x > pantallaAncho);
	}

	void SetX(int newX) {
		x = newX;
	}

	int GetTipo() {
		return tipo;
	}
	int GetAncho() {
		return ancho;
	}

	int GetX() {
		return x;
	}

	int GetDx() {
		return dx;
	}

	void Mover(Graphics^ g) {
		x += dx;
	}

	System::Drawing::Rectangle HitBox() {
		return System::Drawing::Rectangle(x + 3, y + 5, ancho - 4, alto - 10);
	}

	void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
		Bitmap^ img = (tipo == 0) ? img1 : img2; // Seleccionar la imagen correcta
		g->DrawImage(img, Area()); // Dibujar la imagen correspondiente
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Red, HitBox());
	}
};
class AliadosBase {
protected:
	vector<Aliado*> aliados;
	int filaActualIzquierda = 0;
	int filaActualDerecha = 0;

	int cantidadIzquierda[3] = { 1, 1, 1 };
	int cantidadDerecha[3] = { 1, 1, 1 };

	clock_t retrasoSpawnIzquierda;
	clock_t retrasoSpawnDerecha;

public:
	AliadosBase() {
		retrasoSpawnIzquierda = clock();
		retrasoSpawnDerecha = clock();
	}

	virtual ~AliadosBase() {
		for (Aliado* A : aliados)
			delete A;
	}

	bool PosicionOcupada(int x, int y) {
		for (Aliado* a : aliados) {
			if (abs(a->GetX() - x) < 50 && abs(a->GetY() - y) < 50) {
				return true; // La posición está ocupada
			}
		}
		return false;
	}

	vector<Aliado*>& GetLista() {
		return aliados;
	}
};
class AliadosNivel1 : public AliadosBase {
protected:

	int startXIzquierda = 1508;//-160;  // Ahora empiezan desde la izquierda
	int startYIzquierda = 332;
	int startXDerecha = 1508;    // Ahora empiezan desde la derecha
	int startYDerecha = 496;

public:
	AliadosNivel1(Bitmap^ img) : AliadosBase() {}

	void AgregarFila(Bitmap^ img1, Bitmap^ img2, bool haciaIzquierda) {
		int fila = haciaIzquierda ? filaActualIzquierda % 3 : filaActualDerecha % 3;
		int cantidad = haciaIzquierda ? cantidadIzquierda[fila] : cantidadDerecha[fila];

		if (aliados.size() >= 20) return;

		for (int i = 0; i < cantidad; i++) {
			int xPos = (haciaIzquierda ? startXIzquierda : startXDerecha) + i * (120);
			int yPos = haciaIzquierda ? startYIzquierda : startYDerecha;
			int tipoActual = (rand() % 100) < 20 ? 0 : 1; // 20% de probabilidad de ser malo (0), 80% de ser bueno (1)


			int intentos = 0;
			bool posicionLibre = false;

			while (intentos < 10) {

				System::Drawing::Rectangle hitboxNuevo(xPos, yPos, 150, 82);
				bool colisiona = false;

				for (Aliado* a : aliados) {
					if (a->HitBox().IntersectsWith(hitboxNuevo)) {
						colisiona = true;
						break;
					}
				}

				if (!colisiona) {
					posicionLibre = true;
					break; // Sale del loop si la posición está libre
				}

				xPos += 150; // Mueve el enemigo a la derecha
				intentos++;


			}

			// Solo lo agrega si encontró una posición libre
			if (posicionLibre) {
				aliados.push_back(new Aliado(
					(tipoActual == 0) ? img1 : img2,
					i,
					haciaIzquierda,
					xPos,
					yPos,
					tipoActual
				));
			}
		}

		if (haciaIzquierda)
			filaActualIzquierda++;
		else
			filaActualDerecha++;
	}

	void Mover(Graphics^ g, Bitmap^ img1, Bitmap^ img2, int pantallaAncho) {
		for (int i = 0; i < aliados.size(); i++) {
			aliados[i]->Mover(g);
			if (aliados[i]->DebeEliminarse(pantallaAncho)) {
				delete aliados[i];
				aliados.erase(aliados.begin() + i);
				i--;
			}
		}

		if ((clock() - retrasoSpawnIzquierda) > 4000 && aliados.size() < 11) {
			AgregarFila(img1, img2, true);
			retrasoSpawnIzquierda = clock();
		}

		if ((clock() - retrasoSpawnDerecha) > 4000 && aliados.size() < 11) {
			AgregarFila(img1, img2, false);
			retrasoSpawnDerecha = clock();
		}

	}

	bool Colision(System::Drawing::Rectangle obj) {
		for (Aliado* A : aliados) {
			if (A->HitBox().IntersectsWith(obj)) {
				return true;
			}
		}
		return false;
	}

	void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
		for (Aliado* A : aliados)
			A->Mostrar(g, img1, img2);
	}
};
class AliadosNivel2 : public AliadosBase {
protected:

	int startXIzquierda = 1508; //-160;  // Ahora empiezan desde la izquierda
	int startYIzquierda = 340;
	int startXDerecha = 1508;    // Ahora empiezan desde la derecha
	int startYDerecha = 508;

public:
	AliadosNivel2(Bitmap^ img) : AliadosBase() {}

	void AgregarFila(Bitmap^ img1, Bitmap^ img2, bool haciaIzquierda) {
		int fila = haciaIzquierda ? filaActualIzquierda % 3 : filaActualDerecha % 3;
		int cantidad = haciaIzquierda ? cantidadIzquierda[fila] : cantidadDerecha[fila];

		if (aliados.size() >= 20) return;

		for (int i = 0; i < cantidad; i++) {
			int xPos = (haciaIzquierda ? startXIzquierda : startXDerecha) + i * 120;
			int yPos = haciaIzquierda ? startYIzquierda : startYDerecha;
			int tipoActual = (rand() % 100) < 35 ? 0 : 1; // 35% de probabilidad de ser malo (0), 75% de ser bueno (1)

			int intentos = 0;
			bool posicionLibre = false;

			while (intentos < 10) {

				System::Drawing::Rectangle hitboxNuevo(xPos, yPos, 150, 82);
				bool colisiona = false;

				for (Aliado* a : aliados) {
					if (a->HitBox().IntersectsWith(hitboxNuevo)) {
						colisiona = true;
						break;
					}
				}

				if (!colisiona) {
					posicionLibre = true;
					break; // Sale del loop si la posición está libre
				}

				xPos += 150; // Mueve el enemigo a la derecha
				intentos++;


			}

			// Solo lo agrega si encontró una posición libre
			if (posicionLibre) {
				aliados.push_back(new Aliado(
					(tipoActual == 0) ? img1 : img2,
					i,
					haciaIzquierda,
					xPos,
					yPos,
					tipoActual
				));
			}
		}
		if (haciaIzquierda)
			filaActualIzquierda++;
		else
			filaActualDerecha++;
	}

	void Mover(Graphics^ g, Bitmap^ img1, Bitmap^ img2, int pantallaAncho) {
		for (int i = 0; i < aliados.size(); i++) {
			aliados[i]->Mover(g);
			if (aliados[i]->DebeEliminarse(pantallaAncho)) {
				delete aliados[i];
				aliados.erase(aliados.begin() + i);
				i--;
			}
		}

		if ((clock() - retrasoSpawnIzquierda) > 4000 && aliados.size() < 11) {
			AgregarFila(img1, img2, true);
			retrasoSpawnIzquierda = clock();
		}

		if ((clock() - retrasoSpawnDerecha) > 4000 && aliados.size() < 11) {
			AgregarFila(img1, img2, false);
			retrasoSpawnDerecha = clock();
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
		for (Aliado* A : aliados)
			A->Mostrar(g, img1, img2);
	}

	bool Colision(System::Drawing::Rectangle obj) {
		for (Aliado* A : aliados) {
			if (A->HitBox().IntersectsWith(obj)) {
				return true;
			}
		}
		return false;
	}
};

class AliadoN3 :public Entidad
{
public:
	int tipo;

	AliadoN3(int x, int y, int tipo) {

		this->x = x;
		this->y = y;
		this->tipo = tipo; // Que varie entre 0 o 1 malos o buenos
	}

	AliadoN3(Bitmap^ img, int index, bool haciaIzquierda, int startX, int startY, int tipo) {
		ancho = 255;
		alto = 88;
		dx = haciaIzquierda ? -7 : -7;
		int separacionX = 160;
		separacionX = ancho + 10;
		x = startX + index * separacionX;
		y = startY;
		this->tipo = tipo; // 0 para malo, 1 para bueno

	}

	bool DebeEliminarse(int pantallaAncho) {
		return (dx < 0 && x + ancho < 0) || (dx > 0 && x > pantallaAncho);
	}

	void SetX(int newX) {
		x = newX;
	}

	int GetTipo() {
		return tipo;
	}
	int GetAncho() {
		return ancho;
	}

	int GetX() {
		return x;
	}

	int GetDx() {
		return dx;
	}

	void Mover(Graphics^ g) {
		x += dx;
	}

	System::Drawing::Rectangle HitBox() {
		return System::Drawing::Rectangle(x + 3, y + 5, ancho - 4, alto - 10);
	}

	void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
		Bitmap^ img = (tipo == 0) ? img1 : img2; // Seleccionar la imagen correcta
		g->DrawImage(img, Area()); // Dibujar la imagen correspondiente
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Red, HitBox());
	}
};
class AliadosBaseN3 {
protected:
	vector<AliadoN3*> aliados;
	int filaActualIzquierda = 0;
	int filaActualDerecha = 0;

	int cantidadIzquierda[3] = { 1, 1, 1 };
	int cantidadDerecha[3] = { 1, 1, 1 };

	clock_t retrasoSpawnIzquierda;
	clock_t retrasoSpawnDerecha;

public:
	AliadosBaseN3() {
		retrasoSpawnIzquierda = clock();
		retrasoSpawnDerecha = clock();
	}

	virtual ~AliadosBaseN3() {
		for (AliadoN3* A : aliados)
			delete A;
	}

	bool PosicionOcupada(int x, int y) {
		for (AliadoN3* a : aliados) {
			if (abs(a->GetX() - x) < 50 && abs(a->GetY() - y) < 50) {
				return true; // La posición está ocupada
			}
		}
		return false;
	}

	vector<AliadoN3*>& GetLista() {
		return aliados;
	}
};
class AliadosNivel3 : public AliadosBaseN3 {
protected:

	int startXIzquierda = 1508; //-160;  // Ahora empiezan desde la izquierda
	int startYIzquierda = 308;
	int startXDerecha = 1508;    // Ahora empiezan desde la derecha
	int startYDerecha = 484;

public:
	AliadosNivel3(Bitmap^ img) : AliadosBaseN3() {}

	void AgregarFila(Bitmap^ img1, Bitmap^ img2, bool haciaIzquierda) {
		int fila = haciaIzquierda ? filaActualIzquierda % 3 : filaActualDerecha % 3;
		int cantidad = haciaIzquierda ? cantidadIzquierda[fila] : cantidadDerecha[fila];

		if (aliados.size() >= 20) return;

		for (int i = 0; i < cantidad; i++) {
			int xPos = (haciaIzquierda ? startXIzquierda : startXDerecha) + i * 120;
			int yPos = haciaIzquierda ? startYIzquierda : startYDerecha;
			int tipoActual = (rand() % 100) < 45 ? 0 : 1; // 45% de probabilidad de ser malo (0), 55% de ser bueno (1)

			int intentos = 0;
			bool posicionLibre = false;

			while (intentos < 10) {

				System::Drawing::Rectangle hitboxNuevo(xPos, yPos, 150, 82);
				bool colisiona = false;

				for (AliadoN3* a : aliados) {
					if (a->HitBox().IntersectsWith(hitboxNuevo)) {
						colisiona = true;
						break;
					}
				}

				if (!colisiona) {
					posicionLibre = true;
					break; // Sale del loop si la posición está libre
				}

				xPos += 150; // Mueve el enemigo a la derecha
				intentos++;


			}

			// Solo lo agrega si encontró una posición libre
			if (posicionLibre) {
				aliados.push_back(new AliadoN3(
					(tipoActual == 0) ? img1 : img2,
					i,
					haciaIzquierda,
					xPos,
					yPos,
					tipoActual
				));
			}
		}
		if (haciaIzquierda)
			filaActualIzquierda++;
		else
			filaActualDerecha++;
	}

	void Mover(Graphics^ g, Bitmap^ img1, Bitmap^ img2, int pantallaAncho) {
		for (int i = 0; i < aliados.size(); i++) {
			aliados[i]->Mover(g);
			if (aliados[i]->DebeEliminarse(pantallaAncho)) {
				delete aliados[i];
				aliados.erase(aliados.begin() + i);
				i--;
			}
		}

		if ((clock() - retrasoSpawnIzquierda) > 4000 && aliados.size() < 11) {
			AgregarFila(img1, img2, true);
			retrasoSpawnIzquierda = clock();
		}

		if ((clock() - retrasoSpawnDerecha) > 4000 && aliados.size() < 11) {
			AgregarFila(img1, img2, false);
			retrasoSpawnDerecha = clock();
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
		for (AliadoN3* A : aliados)
			A->Mostrar(g, img1, img2);
	}

	bool Colision(System::Drawing::Rectangle obj) {
		for (AliadoN3* A : aliados) {
			if (A->HitBox().IntersectsWith(obj)) {
				return true;
			}
		}
		return false;
	}
};