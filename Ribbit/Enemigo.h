#pragma once
#include "Entidad.h"
#include <ctime>  // Para manejar el tiempo

enum SpriteEnemigo {
    eCaminarDerecha,
    eCaminarIzquierda,
};

class Enemigo : public Entidad {
    SpriteEnemigo accion;
    int tipo; // Que varie entre 0 o 1 malos o buenos

public:
    Enemigo(int x, int y, int tipo) {
        this->x = x;
        this->y = y;
        this->tipo = tipo;
    }

    Enemigo(Bitmap^ img, int index, bool haciaIzquierda, int startX, int startY, int tipo) {
        ancho = img->Width / 2;
        alto = img->Height / 2;
        dx = haciaIzquierda ? 5 : 5;
        accion = haciaIzquierda ? eCaminarIzquierda : eCaminarIzquierda;
        int separacionX = 120;
        x = startX + index * separacionX;
        y = startY;
        this->tipo = tipo; // 0 para malo, 1 para bueno
    }

    bool DebeEliminarse(int pantallaAncho) {
        return (dx < 0 && x + ancho < -50) || (dx > 0 && x > pantallaAncho + 50);
    }
    int GetTipo() {
        return tipo;
    }

    void SetX(int newX) {
        x = newX;
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
        return System::Drawing::Rectangle(x + 5, y + 5, ancho - 20, alto - 10);
    }

    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx * ancho, accion * alto, ancho, alto);
        Bitmap^ img = (tipo == 0) ? img1 : img2;
        g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
        //g->DrawRectangle(Pens::Black, Area());
        //g->DrawRectangle(Pens::Red, HitBox());
        if (accion >= eCaminarDerecha && accion <= eCaminarIzquierda)
            IDx = (IDx + 1) % 2;
    }
};
class EnemigosBase {
protected:
    vector<Enemigo*> enemigos;
    int filaActualIzquierda = 0;
    int filaActualDerecha = 0;
    int filaActualNueva = 0;

    int cantidadIzquierda[3] = { 1, 1, 1 };
    int cantidadDerecha[3] = { 1, 1, 1 };
    int cantidadNueva[3] = { 1, 1, 1 };

    clock_t retrasoSpawnIzquierda;
    clock_t retrasoSpawnDerecha;
    clock_t retrasoSpawnNueva;

public:
    EnemigosBase() {
        retrasoSpawnIzquierda = clock();
        retrasoSpawnDerecha = clock();
        retrasoSpawnNueva = clock();
    }

    virtual ~EnemigosBase() {
        for (Enemigo* E : enemigos)
            delete E;
    }

    bool PosicionOcupada(int x, int y) {
        for (Enemigo* e : enemigos) {
            if (abs(e->GetX() - x) < 50 && abs(e->GetY() - y) < 50) {
                return true;
            }
        }
        return false;
    }

    vector<Enemigo*>& GetLista() {
        return enemigos;
    }
};
class EnemigosNivel1 : public EnemigosBase {
protected:

    int startXIzquierda = -313;
    int startYIzquierda = 414;
    int startXDerecha = -313;
    int startYDerecha = 578;

public:
    EnemigosNivel1(Bitmap^ img) : EnemigosBase() {}

    void AgregarFila(Bitmap^ img1, Bitmap^ img2, bool haciaIzquierda) {
        int fila = haciaIzquierda ? filaActualIzquierda % 3 : filaActualDerecha % 3;
        int cantidad = haciaIzquierda ? cantidadIzquierda[fila] : cantidadDerecha[fila];

        if (enemigos.size() >= 20) return;

        for (int i = 0; i < cantidad; i++) {
            int xPos = (haciaIzquierda ? startXIzquierda : startXDerecha) + i * 120;
            int yPos = haciaIzquierda ? startYIzquierda : startYDerecha;
            int tipoActual = (rand() % 100) < 20 ? 0 : 1; // 20% de probabilidad de ser malo (0), 80% de ser bueno (1)

            int intentos = 0;
            bool posicionLibre = false;

            while (intentos < 10) {
                System::Drawing::Rectangle hitboxNuevo(xPos, yPos, 210, 69);

                bool colisiona = false;
                for (Enemigo* e : enemigos) {
                    if (e->HitBox().IntersectsWith(hitboxNuevo)) {
                        colisiona = true;
                        break;
                    }
                }

                if (!colisiona) {
                    posicionLibre = true;
                    break;
                }

                xPos += 150;
                intentos++;
            }

            if (posicionLibre) {
                enemigos.push_back(new Enemigo(
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
        for (int i = 0; i < enemigos.size(); i++) {
            enemigos[i]->Mover(g);
            if (enemigos[i]->DebeEliminarse(pantallaAncho)) {
                delete enemigos[i];
                enemigos.erase(enemigos.begin() + i);
                i--;
            }
        }

        if ((clock() - retrasoSpawnIzquierda) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, true);
            retrasoSpawnIzquierda = clock();
        }

        if ((clock() - retrasoSpawnDerecha) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, false);
            retrasoSpawnDerecha = clock();
        }
    }

    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        for (Enemigo* E : enemigos)
            E->Mostrar(g, img1, img2);
    }

    bool Colision(System::Drawing::Rectangle obj) {
        for (Enemigo* E : enemigos) {
            if (E->HitBox().IntersectsWith(obj)) {
                return true;
            }
        }
        return false;
    }
};
class EnemigosNivel2 : public EnemigosBase {
protected:
    int startXIzquierda = -313;
    int startYIzquierda = 423;
    int startXDerecha = -313;
    int startYDerecha = 590;
    int startXNueva = -313;
    int startYNueva = 254;

public:
    EnemigosNivel2(Bitmap^ img) : EnemigosBase() {}

    void AgregarFila(Bitmap^ img1, Bitmap^ img2, bool haciaIzquierda, bool nuevaFila = false) {
        int fila = nuevaFila ? filaActualNueva % 3 : (haciaIzquierda ? filaActualIzquierda % 3 : filaActualDerecha % 3);
        int cantidad = nuevaFila ? cantidadNueva[fila] : (haciaIzquierda ? cantidadIzquierda[fila] : cantidadDerecha[fila]);

        if (enemigos.size() >= 20) return;

        for (int i = 0; i < cantidad; i++) {
            int xPos = nuevaFila ? startXNueva + i * 120 : (haciaIzquierda ? startXIzquierda : startXDerecha) + i * 120;
            int yPos = nuevaFila ? startYNueva : (haciaIzquierda ? startYIzquierda : startYDerecha);
            int tipoActual = (rand() % 100) < 35 ? 0 : 1; // 35% de probabilidad de ser malo (0), 75% de ser bueno (1)

            int intentos = 0;
            bool posicionLibre = false;

            while (intentos < 10) {
                System::Drawing::Rectangle hitboxNuevo(xPos, yPos, 210, 69);

                bool colisiona = false;
                for (Enemigo* e : enemigos) {
                    if (e->HitBox().IntersectsWith(hitboxNuevo)) {
                        colisiona = true;
                        break;
                    }
                }

                if (!colisiona) {
                    posicionLibre = true;
                    break;
                }

                xPos += 150;
                intentos++;
            }

            if (posicionLibre) {
                enemigos.push_back(new Enemigo(
                    (tipoActual == 0) ? img1 : img2,
                    i,
                    haciaIzquierda,
                    xPos,
                    yPos,
                    tipoActual
                ));
            }
        }
        if (nuevaFila)
            filaActualNueva++;
        else if (haciaIzquierda)
            filaActualIzquierda++;
        else
            filaActualDerecha++;
    }

    void Mover(Graphics^ g, Bitmap^ img1, Bitmap^ img2, int pantallaAncho) {
        for (int i = 0; i < enemigos.size(); i++) {
            enemigos[i]->Mover(g);
            if (enemigos[i]->DebeEliminarse(pantallaAncho)) {
                delete enemigos[i];
                enemigos.erase(enemigos.begin() + i);
                i--;
            }
        }

        if ((clock() - retrasoSpawnIzquierda) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, true);
            retrasoSpawnIzquierda = clock();
        }

        if ((clock() - retrasoSpawnDerecha) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, false);
            retrasoSpawnDerecha = clock();
        }

        if ((clock() - retrasoSpawnNueva) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, false, true);
            retrasoSpawnNueva = clock();
        }
    }

    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        for (Enemigo* E : enemigos)
            E->Mostrar(g, img1, img2);
    }

    bool Colision(System::Drawing::Rectangle obj) {
        for (Enemigo* E : enemigos) {
            if (E->HitBox().IntersectsWith(obj)) {
                return true;
            }
        }
        return false;
    }
};


class EnemigoN3 : public Entidad {
    SpriteEnemigo accion;
    int tipo; // Que varie entre 0 o 1 malos o buenos

public:
    EnemigoN3(int x, int y, int tipo) {
        this->x = x;
        this->y = y;
        this->tipo = tipo;
    }

    EnemigoN3(Bitmap^ img, int index, bool haciaIzquierda, int startX, int startY, int tipo) {
        ancho = img->Width / 2;
        alto = img->Height / 2;
        dx = haciaIzquierda ? 8 : 8;
        accion = haciaIzquierda ? eCaminarIzquierda : eCaminarIzquierda;
        int separacionX = 120;
        x = startX + index * separacionX;
        y = startY;
        this->tipo = tipo; // 0 para malo, 1 para bueno
    }

    bool DebeEliminarse(int pantallaAncho) {
        return (dx < 0 && x + ancho < -50) || (dx > 0 && x > pantallaAncho + 50);
    }
    int GetTipo() {
        return tipo;
    }

    void SetX(int newX) {
        x = newX;
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
        return System::Drawing::Rectangle(x + 5, y + 5, ancho - 20, alto - 10);
    }

    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        System::Drawing::Rectangle corte = System::Drawing::Rectangle(IDx * ancho, accion * alto, ancho, alto);
        Bitmap^ img = (tipo == 0) ? img1 : img2;
        g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
        //g->DrawRectangle(Pens::Black, Area());
        //g->DrawRectangle(Pens::Red, HitBox());
        if (accion >= eCaminarDerecha && accion <= eCaminarIzquierda)
            IDx = (IDx + 1) % 2;
    }
};
class EnemigosBaseN3 {
protected:
    vector<EnemigoN3*> enemigos;
    int filaActualIzquierda = 0;
    int filaActualDerecha = 0;
    int filaActualNueva = 0;

    int cantidadIzquierda[3] = { 1, 1, 1 };
    int cantidadDerecha[3] = { 1, 1, 1 };
    int cantidadNueva[3] = { 1, 1, 1 };

    clock_t retrasoSpawnIzquierda;
    clock_t retrasoSpawnDerecha;
    clock_t retrasoSpawnNueva;

public:
    EnemigosBaseN3() {
        retrasoSpawnIzquierda = clock();
        retrasoSpawnDerecha = clock();
        retrasoSpawnNueva = clock();
    }

    virtual ~EnemigosBaseN3() {
        for (EnemigoN3* E : enemigos)
            delete E;
    }

    bool PosicionOcupada(int x, int y) {
        for (EnemigoN3* e : enemigos) {
            if (abs(e->GetX() - x) < 50 && abs(e->GetY() - y) < 50) {
                return true;
            }
        }
        return false;
    }

    vector<EnemigoN3*>& GetLista() {
        return enemigos;
    }
};
class EnemigosNivel3 : public EnemigosBaseN3 {
protected:
    int startXIzquierda = -313;
    int startYIzquierda = 396;
    int startXDerecha = -313;
    int startYDerecha = 572;
    int startXNueva = -313;
    int startYNueva = 220;

public:
    EnemigosNivel3(Bitmap^ img) : EnemigosBaseN3() {}

    void AgregarFila(Bitmap^ img1, Bitmap^ img2, bool haciaIzquierda, bool nuevaFila = false) {
        int fila = nuevaFila ? filaActualNueva % 3 : (haciaIzquierda ? filaActualIzquierda % 3 : filaActualDerecha % 3);
        int cantidad = nuevaFila ? cantidadNueva[fila] : (haciaIzquierda ? cantidadIzquierda[fila] : cantidadDerecha[fila]);

        if (enemigos.size() >= 20) return;

        for (int i = 0; i < cantidad; i++) {
            int xPos = nuevaFila ? startXNueva + i * 120 : (haciaIzquierda ? startXIzquierda : startXDerecha) + i * 120;
            int yPos = nuevaFila ? startYNueva : (haciaIzquierda ? startYIzquierda : startYDerecha);
            int tipoActual = (rand() % 100) < 45 ? 0 : 1; // 45% de probabilidad de ser malo (0), 55% de ser bueno (1)

            int intentos = 0;
            bool posicionLibre = false;

            while (intentos < 10) {
                System::Drawing::Rectangle hitboxNuevo(xPos, yPos, 210, 69);

                bool colisiona = false;
                for (EnemigoN3* e : enemigos) {
                    if (e->HitBox().IntersectsWith(hitboxNuevo)) {
                        colisiona = true;
                        break;
                    }
                }

                if (!colisiona) {
                    posicionLibre = true;
                    break;
                }

                xPos += 150;
                intentos++;
            }

            if (posicionLibre) {
                enemigos.push_back(new EnemigoN3(
                    (tipoActual == 0) ? img1 : img2,
                    i,
                    haciaIzquierda,
                    xPos,
                    yPos,
                    tipoActual
                ));
            }
        }
        if (nuevaFila)
            filaActualNueva++;
        else if (haciaIzquierda)
            filaActualIzquierda++;
        else
            filaActualDerecha++;
    }

    void Mover(Graphics^ g, Bitmap^ img1, Bitmap^ img2, int pantallaAncho) {
        for (int i = 0; i < enemigos.size(); i++) {
            enemigos[i]->Mover(g);
            if (enemigos[i]->DebeEliminarse(pantallaAncho)) {
                delete enemigos[i];
                enemigos.erase(enemigos.begin() + i);
                i--;
            }
        }

        if ((clock() - retrasoSpawnIzquierda) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, true);
            retrasoSpawnIzquierda = clock();
        }

        if ((clock() - retrasoSpawnDerecha) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, false);
            retrasoSpawnDerecha = clock();
        }

        if ((clock() - retrasoSpawnNueva) > 4000 && enemigos.size() < 11) {
            AgregarFila(img1, img2, false, true);
            retrasoSpawnNueva = clock();
        }
    }

    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        for (EnemigoN3* E : enemigos)
            E->Mostrar(g, img1, img2);
    }

    bool Colision(System::Drawing::Rectangle obj) {
        for (EnemigoN3* E : enemigos) {
            if (E->HitBox().IntersectsWith(obj)) {
                return true;
            }
        }
        return false;
    }
};
