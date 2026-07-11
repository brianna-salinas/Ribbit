#pragma once
#include "Dependencias.h"

class Entidad {
protected:
	int x, y;
	int dx, dy;
	int alto, ancho;
	int IDx;
public:
	Entidad() {
		x = y = 0;
		dx = dy = 0;
		ancho = alto = 0;
		IDx = 0;
	}

	void SetDx(int value) {
		dx = value;
	}
	void SetDy(int value) {
		dy = value;
	}

	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}

	System::Drawing::Rectangle Area() {
		return System::Drawing::Rectangle(x, y, ancho, alto);
	}
	System::Drawing::Rectangle NextArea() {
		return System::Drawing::Rectangle(x + dx, y + dy, ancho, alto);
	}

	System::Drawing::Rectangle HitBox() {
		return System::Drawing::Rectangle(x + ancho / 4, y + alto / 3 - 5, ancho / 2, alto * 2 / 3);
	}

	System::Drawing::Rectangle NextHitBox() {
		return System::Drawing::Rectangle(x + ancho / 4 + dx, y + alto / 3 - 5 + dy, ancho / 2, alto * 2 / 3);
	}

	// Por polimorfismo ya que tendran la misma funcion pero hara distinta cosas
	virtual void Mover(Graphics^ g) {
		x += dx;
		y += dy;
	}
	virtual void Mostrar(Graphics^ g, Bitmap^ img) {
		g->FillRectangle(Brushes::Black, Area());
	}

};