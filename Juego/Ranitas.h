#pragma once
#include "Entidad.h"

class Ranita : public Entidad {
private:
    int tipo;

public:
    Ranita(int x, int y, int tipo) {
        this->x = x;
        this->y = y;
        this->tipo = tipo;
        this->ancho = 40;
        this->alto = 40;
    }

    int GetTipo() {
        return tipo;
    }

    System::Drawing::Rectangle HitBox() {
        return System::Drawing::Rectangle(x, y, ancho, alto);
    }


    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        Bitmap^ img = (tipo == 0) ? img1 : img2;
        g->DrawImage(img, Area());
        //g->DrawRectangle(Pens::Red, HitBox());
    }
};

class Ranitas {
private:
    vector<Ranita*> ranitas;
    int cantidadRanitas = 4;

public:
    Ranitas() {}

    ~Ranitas() {
        for (Ranita* r : ranitas)
            delete r;
    }

    bool PosicionOcupada(int x, int y) {
        for (Ranita* r : ranitas) {
            if (abs(r->GetX() - x) < 50 && abs(r->GetY() - y) < 50) {
                return true;
            }
        }
        return false;
    }

    void AgregarRanita(int x, int y, Bitmap^ img1, Bitmap^ img2) {
        if (ranitas.size() >= 4) return; // Mantener el límite de 5 ranitas

        int tipo = rand() % 2; // 0 para normal, 1 para especial
        ranitas.push_back(new Ranita(x, y, tipo));
    }


    void GenerarRanitas(Bitmap^ img1, Bitmap^ img2) {
        Random^ rnd = gcnew Random();
        while (ranitas.size() < cantidadRanitas) {
            int x = rnd->Next(0, 1508 - 40);
            int y = rnd->Next(706, 775);
            int tipo = rnd->Next(0, 2);

            int intentos = 0;
            while (PosicionOcupada(x, y) && intentos < 10) {
                x = rnd->Next(0, 1508 - 40);
                y = rnd->Next(706, 775);
                intentos++;
            }

            if (!PosicionOcupada(x, y)) {
                ranitas.push_back(new Ranita(x, y, tipo));
            }
        }
    }

    void ReponerRanitas(Bitmap^ img1, Bitmap^ img2) {
        while (ranitas.size() < cantidadRanitas) {
            GenerarRanitas(img1, img2);
        }
    }

    void Mostrar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {
        for (Ranita* r : ranitas)
            r->Mostrar(g, img1, img2);
    }

    vector<Ranita*>& GetLista() {
        return ranitas;
    }
};
