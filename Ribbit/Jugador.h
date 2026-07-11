#pragma once
#include "Entidad.h"
#include <chrono>

enum SpriteJugador {
	CaminarAbajo,
	CaminarArriba,
	CaminarIzquierda,
	CaminarDerecha,
	Morir,
};

class JugadorBase : public Entidad {
protected:
	static int vidas; // variable estatica compartida entre todos los niveles
	SpriteJugador accion;
	bool sobrePlataforma = false;
	clock_t tiempoBloqueo = 0; // Tiempo de bloqueo del movimiento
	// Nota: JugadorBase es una clase NATIVA (no ref class), por eso no puede tener
	// un Bitmap^ como miembro. La imagen del coraz�n se precarga en el Controlador
	// de cada nivel (que s� es ref class) y se pasa como par�metro a Mostrar().

public:
	JugadorBase(Bitmap^ img, int v) {
		if (vidas == 0) {
			vidas = 4; // Inicializa con 4 vidas solo si es la primera vez
		}
		x = 0;
		y = 0;
		dx = dy = 0;
		ancho = img->Width / 3;
		alto = img->Height / 5;
		accion = CaminarAbajo;
	}

	void SetAccion(SpriteJugador value) { accion = value; }
	void SetSobrePlataforma(bool value) { sobrePlataforma = value; }
	int GetAncho() { return ancho; }
	int GetX() { return x; }
	int GetY() { return y; }
	int GetDx() { return dx; }
	int GetDy() { return dy; }
	bool SobrePlataforma() { return sobrePlataforma; }
	int GetVidas() { return vidas; }

	void SetX(int newX) { x = newX; }
	void SetY(int newY) { y = newY; }

	static void SetVidas(int value) { vidas = value; }

	void RestarVida() {
		if (vidas > 0) {
			vidas--;
			if (vidas == 0) {
				// Cambia la acci�n a "Morir"
				accion = Morir;
			}
		}
	}

	virtual void Mover(Graphics^ g);
	virtual void Mostrar(Graphics^ g, Bitmap^ img, Bitmap^ imgCorazon);
};

class JugadorNivel1 : public JugadorBase {
private:
	// Nombres para los n�meros de posici�n que usa Mover(). Son EXACTAMENTE los mismos
	// valores que antes (no se cambi� ning�n n�mero), solo se les puso nombre para
	// que se entienda qu� representan. Si conoc�s el dise�o del nivel mejor que estos
	// nombres gen�ricos, renombralos con confianza; el comportamiento no cambia.
	static const int Y_FILA_BAJA = 585;          // Fila de "aterrizaje"/bloqueo m�s cercana al jugador
	static const int Y_TRONCO_CERCA = 660;       // Posici�n de descanso sobre el tronco cercano a la orilla
	static const int Y_RESTRICCION_SUBIR = 683;  // Si el jugador est� ac�, se lo empuja al l�mite de abajo
	static const int Y_LIMITE_RESTRINGIDO = 706; // Tope al que se manda cuando se activa la restricci�n
	static const int Y_FILA_2 = 503;
	static const int Y_FILA_3 = 421;
	static const int Y_FILA_4 = 339;
	static const int MS_BLOQUEO_SALTO = 1000;    // Tiempo (ms) sin poder subir/bajar tras aterrizar
	static const int Y_TOPE_JUGABLE = 257;       // L�mite superior de la zona jugable (orilla m�s lejana)
	static const int X_ZONA_IZQ_MAX = 698;
	static const int X_ZONA_DER_MIN = 759;
	static const int X_ZONA_DER_MAX = 1500;

public:
	JugadorNivel1(Bitmap^ img, int v) : JugadorBase(img, v) {}

	void Mover(Graphics^ g) override {
		// Mover en X dentro de los l�mites
		if (x + dx >= 0 && x + dx <= g->VisibleClipBounds.Width - ancho) {
			x += dx;
		}

		// Ajustes de posici�n espec�ficos (sin cambios)
		switch (y) {
		case 637: case 539: case 562:
			y = Y_FILA_BAJA;
			break;
		case 667:
			y = Y_TRONCO_CERCA;
			break;
		}

		// **Bloquear movimiento en Y seg�n la posici�n en X**
		if ((x >= 0 && x <= X_ZONA_IZQ_MAX) || (x >= X_ZONA_DER_MIN && x <= X_ZONA_DER_MAX)) {
			if (y == Y_RESTRICCION_SUBIR || y == Y_TRONCO_CERCA) {
				y = Y_LIMITE_RESTRINGIDO;  // Restringir para que no suba m�s arriba
			}
		}

		// **L�gica de bloqueo de movimiento en Y**
		if (y == Y_FILA_BAJA || y == Y_FILA_2 || y == Y_FILA_3 || y == Y_FILA_4) {
			if (tiempoBloqueo == 0) {
				dy = 0; // Bloquear movimiento en Y
				tiempoBloqueo = clock(); // Guardar tiempo de inicio del bloqueo
			}
		}

		// **Permitir movimiento en Y despu�s de 1 segundo**
		if (tiempoBloqueo > 0 && (clock() - tiempoBloqueo) > MS_BLOQUEO_SALTO) {
			tiempoBloqueo = 0; // Restablecer bloqueo
		}

		// Mover en Y dentro de los l�mites y con bloqueo
		if (y + dy >= Y_TOPE_JUGABLE && y + dy <= g->VisibleClipBounds.Height - alto && tiempoBloqueo == 0) {
			y += dy;
		}
		else if (y < Y_TOPE_JUGABLE) {
			y = Y_TOPE_JUGABLE;
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img, Bitmap^ imgCorazon) override {
		// imgCorazon llega ya precargada desde el Controlador (no se recarga en cada frame)

		// Posici�n inicial para los corazones
		int posX = 770;
		int posY = 38;
		int espacioEntreCorazones = 30; // Espacio entre im�genes

		// Dibujar el texto "VIDAS :"
		g->DrawString("VIDAS:", gcnew Font("Arial Black", 16), Brushes::Red, 785, 13);

		// Dibujar corazones seg�n la cantidad de vidas
		for (int i = 0; i < vidas; i++) {
			g->DrawImage(imgCorazon, posX + (i * espacioEntreCorazones), posY, 30, 30); // Tama�o de imagen 30x30
		}

		System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Blue, HitBox());

		// Animaci�n del personaje
		if (dx != 0 || dy != 0) {
			if (accion >= CaminarArriba && accion <= CaminarAbajo)
				IDx = (IDx + 1) % 3;
			else if (accion >= CaminarIzquierda && accion <= Morir)
				IDx = (IDx + 1) % 2;
		}
	}
};
class JugadorNivel2 : public JugadorBase {
private:
	// Mismos valores que antes, solo con nombre (ver nota en JugadorNivel1).
	static const int Y_FILA_BAJA = 593;
	static const int Y_TRONCO_CERCA = 660;
	static const int Y_FILA_ALTA = 265;
	static const int Y_TOPE_SNAP = 206;          // Posici�n a la que se ajusta cerca del tope superior
	static const int Y_RESTRICCION_A = 683;
	static const int Y_RESTRICCION_B = 675;
	static const int Y_LIMITE_RESTRINGIDO = 695;
	static const int Y_FILA_2 = 511;
	static const int Y_FILA_3 = 429;
	static const int Y_FILA_4 = 347;
	static const int MS_BLOQUEO_SALTO = 1000;
	static const int Y_TOPE_JUGABLE = 183;       // L�mite superior de la zona jugable
	static const int X_ZONA_IZQ_MAX = 707;
	static const int X_ZONA_DER_MIN = 808;
	static const int X_ZONA_DER_MAX = 1500;

public:
	JugadorNivel2(Bitmap^ img, int v) : JugadorBase(img, v) {}

	void Mover(Graphics^ g) {
		// Mover en X dentro de los l�mites
		if (x + dx >= 0 && x + dx <= g->VisibleClipBounds.Width - ancho) {
			x += dx;
		}

		// Ajustes de posici�n espec�ficos (sin cambios)
		switch (y) {
		case 655: case 539: case 635:
			y = Y_FILA_BAJA;
			break;
		case 667:
			y = Y_TRONCO_CERCA;
			break;

		case 226: case 246:
			y = Y_FILA_ALTA;
			break;
		case 186:
			y = Y_TOPE_SNAP;
			break;
		}

		// **Bloquear movimiento en Y seg�n la posici�n en X**
		if ((x >= 0 && x <= X_ZONA_IZQ_MAX) || (x >= X_ZONA_DER_MIN && x <= X_ZONA_DER_MAX)) {
			if (y == Y_RESTRICCION_A || y == Y_RESTRICCION_B) {
				y = Y_LIMITE_RESTRINGIDO;  // Restringir para que no suba m�s arriba
			}
		}

		// **L�gica de bloqueo de movimiento en Y**
		if (y == Y_FILA_BAJA || y == Y_FILA_2 || y == Y_FILA_3 || y == Y_FILA_4 || y == Y_FILA_ALTA) { //limites filas de salto
			if (tiempoBloqueo == 0) {
				dy = 0; // Bloquear movimiento en Y
				tiempoBloqueo = clock(); // Guardar tiempo de inicio del bloqueo
			}
		}

		// **Permitir movimiento en Y despu�s de 1 segundo**
		if (tiempoBloqueo > 0 && (clock() - tiempoBloqueo) > MS_BLOQUEO_SALTO) {
			tiempoBloqueo = 0; // Restablecer bloqueo
		}

		// Mover en Y dentro de los l�mites y con bloqueo //limite pantalla con ranas
		if (y + dy >= Y_TOPE_JUGABLE && y + dy <= g->VisibleClipBounds.Height - alto && tiempoBloqueo == 0) {
			y += dy;
		}
		else if (y <= Y_TOPE_JUGABLE) {
			y = Y_TOPE_SNAP;
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img, Bitmap^ imgCorazon) override {
		// imgCorazon llega ya precargada desde el Controlador (no se recarga en cada frame)

		// Posici�n inicial para los corazones
		int posX = 770;
		int posY = 38;
		int espacioEntreCorazones = 30; // Espacio entre im�genes

		// Dibujar el texto "VIDAS :"
		g->DrawString("VIDAS:", gcnew Font("Arial Black", 16), Brushes::Red, 785, 13);

		// Dibujar corazones seg�n la cantidad de vidas
		for (int i = 0; i < vidas; i++) {
			g->DrawImage(imgCorazon, posX + (i * espacioEntreCorazones), posY, 30, 30); // Tama�o de imagen 30x30
		}

		System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Blue, HitBox());

		// Animaci�n del personaje
		if (dx != 0 || dy != 0) {
			if (accion >= CaminarArriba && accion <= CaminarAbajo)
				IDx = (IDx + 1) % 3;
			else if (accion >= CaminarIzquierda && accion <= Morir)
				IDx = (IDx + 1) % 2;
		}
	}
};
class JugadorNivel3 : public JugadorBase {
private:
	// Mismos valores que antes, solo con nombre (ver nota en JugadorNivel1).
	static const int Y_FILA_BAJA = 585;
	static const int Y_TRONCO_CERCA = 668;
	static const int Y_FILA_ALTERNA = 580;       // Fila usada tanto de snap (case 641) como de bloqueo
	static const int Y_RESTRICCION_MIN = 650;
	static const int Y_RESTRICCION_MAX = 680;
	static const int Y_LIMITE_RESTRINGIDO = 710;
	static const int Y_FILA_2 = 660;
	static const int Y_FILA_3 = 616;
	static const int Y_FILA_4 = 492;
	static const int Y_FILA_5 = 404;
	static const int Y_FILA_6 = 316;
	static const int Y_FILA_7 = 228;
	static const int MS_BLOQUEO_SALTO = 1000;
	static const int Y_TOPE_JUGABLE = 70;        // L�mite superior de la zona jugable
	static const int X_ZONA_IZQ_MAX = 694;
	static const int X_ZONA_DER_MIN = 755;
	static const int X_ZONA_DER_MAX = 1500;

public:
	JugadorNivel3(Bitmap^ img, int v) : JugadorBase(img, v) {}

	void Mover(Graphics^ g) {
		// Mover en X dentro de los l�mites
		if (x + dx >= 0 && x + dx <= g->VisibleClipBounds.Width - ancho) {
			x += dx;
		}

		// Ajustes de posici�n espec�ficos (sin cambios)
		switch (y) {
		case 637: case 539: case 562:
			y = Y_FILA_BAJA;
			break;
		case 678:
			y = Y_TRONCO_CERCA;
			break;
		case 641:
			y = Y_FILA_ALTERNA;
		}

		// **Bloquear movimiento en Y seg�n la posici�n en X**
		if ((x >= 0 && x <= X_ZONA_IZQ_MAX) || (x >= X_ZONA_DER_MIN && x <= X_ZONA_DER_MAX)) {
			if (y >= Y_RESTRICCION_MIN && y <= Y_RESTRICCION_MAX) {
				y = Y_LIMITE_RESTRINGIDO;  // Restringir para que no suba m�s arriba
			}
		}

		if (y == Y_FILA_2 || y == Y_FILA_3 || y == Y_FILA_ALTERNA || y == Y_FILA_4 || y == Y_FILA_5 || y == Y_FILA_6 || y == Y_FILA_7) { //limites filas de salto
			if (tiempoBloqueo == 0) {
				dy = 0; // Bloquear movimiento en Y
				tiempoBloqueo = clock(); // Guardar tiempo de inicio del bloqueo
			}
		}

		if (y >= Y_FILA_7 && y <= Y_FILA_2) {
			if (tiempoBloqueo == 0) {
				dy = 0; // Bloquear movimiento en Y
				tiempoBloqueo = clock(); // Guardar tiempo de inicio del bloqueo
			}
		}

		// **Permitir movimiento en Y despu�s de 1 segundo**
		if (tiempoBloqueo > 0 && (clock() - tiempoBloqueo) > MS_BLOQUEO_SALTO) {
			tiempoBloqueo = 0; // Restablecer bloqueo
		}

		// Mover en Y dentro de los l�mites y con bloqueo //limite pantalla con ranas
		if (y + dy >= Y_TOPE_JUGABLE && y + dy <= g->VisibleClipBounds.Height - alto && tiempoBloqueo == 0) {
			y += dy;
		}
		else if (y < Y_TOPE_JUGABLE) {
			y = Y_TOPE_JUGABLE;
		}
	}

	void Mostrar(Graphics^ g, Bitmap^ img, Bitmap^ imgCorazon) override {
		// imgCorazon llega ya precargada desde el Controlador (no se recarga en cada frame)

		// Posici�n inicial para los corazones
		int posX = 770;
		int posY = 38;
		int espacioEntreCorazones = 30; // Espacio entre im�genes

		// Dibujar el texto "VIDAS :"
		g->DrawString("VIDAS:", gcnew Font("Arial Black", 16), Brushes::Red, 785, 13);

		// Dibujar corazones seg�n la cantidad de vidas
		for (int i = 0; i < vidas; i++) {
			g->DrawImage(imgCorazon, posX + (i * espacioEntreCorazones), posY, 30, 30); // Tama�o de imagen 30x30
		}

		System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Black, Area());
		//g->DrawRectangle(Pens::Blue, HitBox());

		// Animaci�n del personaje
		if (dx != 0 || dy != 0) {
			if (accion >= CaminarArriba && accion <= CaminarAbajo)
				IDx = (IDx + 1) % 3;
			else if (accion >= CaminarIzquierda && accion <= Morir)
				IDx = (IDx + 1) % 2;
		}
	}
};