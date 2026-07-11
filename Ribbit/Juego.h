#pragma once
#include "Jugador.h"
#include "Enemigo.h"
#include "Aliados.h"
#include "Ranitas.h"
#include <cstdlib>
#include <Windows.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

ref class ControladorNivel1 {
private:
    JugadorNivel1* jugador;
    AliadosNivel1* aliados;
    EnemigosNivel1* enemigos;
    Ranitas* ranitas;

    Bitmap^ imgAliados1;
    Bitmap^ imgAliados2;
    Bitmap^ imgJugador;
    Bitmap^ imgJugadorModificado;
    Bitmap^ imgEnemigos;
    Bitmap^ imgEnemigos1;
    Bitmap^ imgRanita1;
    Bitmap^ imgRanita2;
    Bitmap^ imgCorazon; // Precargada una sola vez (antes se recargaba en cada frame)

    int cooldownAtaqueEnemigo;
    int tiempo;
    int posXInicial;
    int posYInicial;
    bool cambioImagen;
    bool tieneRanita;
    clock_t tiempoInicio;
    String^ nombreJugador;

    int puntaje;
    int ranasSalvadas;
    List<System::Drawing::Rectangle>^ zonasSalvacion;

public:
    ControladorNivel1(int v, int t, String^ nombreJugador, int skin) {
        zonasSalvacion = gcnew List<System::Drawing::Rectangle>();
        zonasSalvacion->Add(System::Drawing::Rectangle(60, 275, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(344, 275, 30, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(581, 275, 48, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(873, 275, 10, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(1125, 275, 32, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(1378, 275, 32, 50));
        tiempoInicio = clock();

        if (skin == 1) {
            imgJugador = gcnew Bitmap("img/Ranitas.png");
            imgJugadorModificado = gcnew Bitmap("img/RanayBB.png");
        }
        else if (skin == 2) {
            imgJugador = gcnew Bitmap("img/RanaRF.png");
            imgJugadorModificado = gcnew Bitmap("img/RanaRFbb.png");
        }
        else if (skin == 3) {
            imgJugador = gcnew Bitmap("img/RanaAN.png");
            imgJugadorModificado = gcnew Bitmap("img/RanaANbb.png");
        }
        else if (skin == 4) {
            imgJugador = gcnew Bitmap("img/RanaVP.png");
            imgJugadorModificado = gcnew Bitmap("img/RanaVpBB.png");
        }

        imgAliados1 = gcnew Bitmap("img/Troncoroto.png");
        imgAliados2 = gcnew Bitmap("img/Troncobueno.png");
        imgEnemigos = gcnew Bitmap("img/caimanMaloNivel1.png");
        imgEnemigos1 = gcnew Bitmap("img/caimanBuenoNivel1.png");
        imgRanita1 = gcnew Bitmap("img/ranita.png");
        imgRanita2 = gcnew Bitmap("img/ranita.png");
        imgCorazon = gcnew Bitmap("img/corazon.png");

        Random^ rnd = gcnew Random();
        posXInicial = rnd->Next(0, 1500);
        posYInicial = 775;

        jugador = new JugadorNivel1(imgJugador, v);
        jugador->SetX(posXInicial);
        jugador->SetY(posYInicial);

        aliados = new AliadosNivel1(imgAliados1);
        enemigos = new EnemigosNivel1(imgEnemigos);
        ranitas = new Ranitas();
        ranitas->GenerarRanitas(imgRanita1, imgRanita2);

        cooldownAtaqueEnemigo = 0;
        this->nombreJugador = nombreJugador;
        tiempo = t * 1000;
        cambioImagen = false;
        tieneRanita = false;

        puntaje = 0;
        ranasSalvadas = 0;
    }

    ~ControladorNivel1() {
        delete jugador;
        delete aliados;
        delete enemigos;
        delete imgAliados1;
        delete imgAliados2;
        delete imgJugador;
        delete imgJugadorModificado;
        delete imgRanita1;
        delete imgRanita2;
        delete imgCorazon;
    }

    bool EstaEnZonaSalvacion(Ranita* ranita) {
        System::Drawing::Rectangle hitboxRanita = ranita->HitBox();
        for each (System::Drawing::Rectangle zona in zonasSalvacion) {
            if (zona.IntersectsWith(hitboxRanita)) {
                return true;
            }
        }
        return false;
    }

    int GetJugadorVidas() {
        return jugador->GetVidas();
    }
    void SetJugadorVidas(int vidas) {
        jugador->SetVidas(vidas);
    }

    int GetPuntaje() {
        return puntaje;
    }

    void MovimientoJugador(bool accion, Keys tecla) {
        int vx, vy;

        // **Nueva condici�n para y = 257**
        if (jugador->GetY() >= 660) {
            vx = 23;
            vy = 23;
        }
        else if (jugador->GetY() == 257) {
            vx = 23; vy = 82;
        }
        else {
            vy = 82;
            vx = 15;
        }

        if (accion) {
            if (tecla == Keys::Up) {
                jugador->SetDy(-vy);
                jugador->SetAccion(CaminarArriba);
            }
            else if (tecla == Keys::Down) {
                jugador->SetDy(vy);
                jugador->SetAccion(CaminarAbajo);
            }
            else if (tecla == Keys::Left) {
                jugador->SetDx(-vx);
                jugador->SetAccion(CaminarIzquierda);
            }
            else if (tecla == Keys::Right) {
                jugador->SetDx(vx);
                jugador->SetAccion(CaminarDerecha);
            }
        }
        else {
            jugador->SetDx(0);
            jugador->SetDy(0);
        }
    }

    // **Nuevo: Verificar si el jugador colisiona con una ranita y manejar el cambio de imagen**
    void VerificarColisionConRanita(Keys tecla) {
        if (tecla == Keys::Space) { // **Usar barra espaciadora**
            if (!tieneRanita) { // **Si no tiene ranita, recogerla**
                for (int i = 0; i < ranitas->GetLista().size(); i++) {
                    if (jugador->HitBox().IntersectsWith(ranitas->GetLista()[i]->HitBox())) {
                        delete ranitas->GetLista()[i]; // **Eliminar la ranita recogida**
                        ranitas->GetLista().erase(ranitas->GetLista().begin() + i);
                        cambioImagen = true; // **Cambiar la imagen del jugador**
                        tieneRanita = true; // **Marcar que tiene una ranita**
                        break;
                    }
                }
            }
            else { // **Si ya tiene ranita, intentar colocarla**
                int x = jugador->GetX();
                int y = jugador->GetY();

                // **Verificar si la nueva ranita colisiona con otra ya existente**
                for each (Ranita * ranita in ranitas->GetLista()) {
                    if (ranita->HitBox().IntersectsWith(System::Drawing::Rectangle(x, y, 40, 40))) {
                        return; // No colocar la ranita si se superpone con otra
                    }
                }

                //**Si no hay colisi�n, colocar la ranita**
                ranitas->AgregarRanita(x, y, imgRanita1, imgRanita2);
                cambioImagen = false; // **Volver a la imagen original**
                tieneRanita = false; // **Restablecer estado**
            }
        }
    }


    int GetJugadorY() {
        return jugador->GetY();
    }

    void VerificarRanasSalvadas() {
        int nuevasRanasSalvadas = 0;

        for each (Ranita * ranita in ranitas->GetLista()) {
            if (EstaEnZonaSalvacion(ranita)) {
                nuevasRanasSalvadas++;
            }
        }

        int diferencia = nuevasRanasSalvadas - ranasSalvadas;

        if (diferencia > 0) {
            puntaje += 10 * diferencia;
        }
        else if (diferencia < 0) {
            puntaje -= 10 * (-diferencia);
        }

        ranasSalvadas = min(nuevasRanasSalvadas, 4);
    }

    void Mostrar(Graphics^ g) {
        // imgRanita1 ya est� precargada en el constructor: se reutiliza en vez de recargar el archivo 30 veces por segundo
        g->DrawString("NIVEL 1", gcnew Font("Arial Black", 20), Brushes::DarkMagenta, 50, 4);
        g->DrawString("presiona 'space' para recoger / dejar a las ranitas", gcnew Font("Arial Black", 10), Brushes::Purple, 585, 83);
        g->DrawString("PLAYER: " + nombreJugador, gcnew Font("Arial Black", 18), Brushes::White, 336, 20);
        g->DrawString("PUNTAJE: ", gcnew Font("Arial Black", 16), Brushes::Lime, 898, 13);
        g->DrawString(puntaje.ToString(), gcnew Font("Arial Black", 16), Brushes::Lime, 952, 38);
        g->DrawImage(imgRanita1, 1040, 13, 30, 30); // Dibuja la imagen en (1040, 13) con tama�o 30x30
        g->DrawString("SALVADAS", gcnew Font("Arial Black", 16), Brushes::White, 1070, 13);
        g->DrawString(ranasSalvadas.ToString() + "/4", gcnew Font("Arial Black", 16), Brushes::White, 1070, 38);

        // **Calcular tiempo transcurrido y tiempo restante con espera de 5 segundos**
        int tiempoTranscurrido = max(0, (clock() - tiempoInicio) / CLOCKS_PER_SEC - 5);
        int tiempoRestante = max(0, 300 - tiempoTranscurrido);  // **300 segundos = 5 minutos**

        // **Convertir a formato MM:SS**
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        String^ tiempoFormateado = minutos.ToString("00") + ":" + segundos.ToString("00");

        // **Mostrar "TIEMPO :" y el tiempo formateado en pantalla**
        g->DrawString("TIEMPO:", gcnew Font("Arial Black", 16), Brushes::Yellow, 650, 13);
        g->DrawString(tiempoFormateado, gcnew Font("Arial Black", 16), Brushes::White, 660, 38);


        aliados->Mostrar(g, imgAliados1, imgAliados2);
        enemigos->Mostrar(g, imgEnemigos, imgEnemigos1);
        ranitas->Mostrar(g, imgRanita1, imgRanita2);

        if (cambioImagen) {
            jugador->Mostrar(g, imgJugadorModificado, imgCorazon);
        }
        else {
            jugador->Mostrar(g, imgJugador, imgCorazon);
        }
    }


    void Mover(Graphics^ g, int Tipo) {
        bool sobrePlataforma = false;
        bool sobreTroncoBueno = false;
        bool sobreCaimanBueno = false;
        int desplazamientoPlataforma = 0;
        int limiteIzquierdo = 0, limiteDerecho = 0;

        // **Verificar si el jugador est� sobre un caim�n bueno**
        for (Enemigo* e : enemigos->GetLista()) {
            if (jugador->Area().IntersectsWith(e->Area())) {
                if (e->GetTipo() == 1) {
                    desplazamientoPlataforma = e->GetDx();
                    sobrePlataforma = true;
                    sobreCaimanBueno = true;
                    limiteIzquierdo = e->GetX() + 35;
                    limiteDerecho = e->GetX() + e->GetAncho() - jugador->GetAncho() - 15;
                }
                else {
                    jugador->RestarVida();
                    ReiniciarPosicion();
                    return;
                }
            }
        }

        for (Aliado* a : aliados->GetLista()) {
            if (jugador->Area().IntersectsWith(a->Area())) {
                if (a->GetTipo() == 1) {
                    desplazamientoPlataforma = a->GetDx();
                    sobrePlataforma = true;
                    sobreTroncoBueno = true;
                    limiteIzquierdo = a->GetX() + 10;
                    limiteDerecho = a->GetX() + a->GetAncho() - jugador->GetAncho() - 15;
                }
                else {
                    jugador->RestarVida();
                    ReiniciarPosicion();
                    return;
                }
            }
        }

        VerificarRanasSalvadas();
        // **Si est� sobre una plataforma en movimiento**
        if (sobrePlataforma) {
            if (jugador->GetDx() == 0) {
                jugador->SetX(jugador->GetX() + desplazamientoPlataforma);
            }
            else {
                int nuevaX = jugador->GetX() + jugador->GetDx();
                if (nuevaX < limiteIzquierdo) {
                    jugador->SetX(limiteIzquierdo);
                }
                else if (nuevaX > limiteDerecho) {
                    jugador->SetX(limiteDerecho);
                }
                else {
                    jugador->SetX(nuevaX);
                }
            }
        }

        // **Si el jugador cae al lago, reaparece**
        if (jugador->GetY() >= 332 && jugador->GetY() < 660) {
            if (!sobreTroncoBueno && !sobreCaimanBueno) {
                jugador->RestarVida(); // **Restar una vida**
                ReiniciarPosicion();
                return;
            }
        }

        // **Si el jugador llega a los bordes mientras est� sobre una plataforma, reaparece**
        if ((jugador->GetX() <= 0 || jugador->GetX() >= 1508) && (sobreTroncoBueno || sobreCaimanBueno)) {
            jugador->RestarVida(); // **Restar una vida**
            ReiniciarPosicion();
            return;
        }

        jugador->Mover(g);
        aliados->Mover(g, imgAliados1, imgAliados2, 1508);
        enemigos->Mover(g, imgEnemigos, imgEnemigos1, 1507);
    }

    void ReiniciarPosicion() {
        jugador->SetX(rand() % 1300);
        jugador->SetY(775);
    }
};
ref class ControladorNivel2 {
private:
    JugadorNivel2* jugador;
    AliadosNivel2* aliados;
    EnemigosNivel2* enemigos;
    Ranitas* ranitas;

    Bitmap^ imgAliados1;
    Bitmap^ imgAliados2;
    Bitmap^ imgJugador;
    Bitmap^ imgJugadorModificado;
    Bitmap^ imgEnemigos;
    Bitmap^ imgEnemigos1;
    Bitmap^ imgRanita1;
    Bitmap^ imgRanita2;
    Bitmap^ imgCorazon; // Precargada una sola vez (antes se recargaba en cada frame)

    int cooldownAtaqueEnemigo;
    int tiempo;
    int posXInicial;
    int posYInicial;
    bool cambioImagen;
    bool tieneRanita;
    clock_t tiempoInicio;
    String^ nombreJugador;

    int puntaje;
    int ranasSalvadas;
    List<System::Drawing::Rectangle>^ zonasSalvacion;

public:
    ControladorNivel2(int v, int t, String^ nombreJugador, int skin) {
        zonasSalvacion = gcnew List<System::Drawing::Rectangle>();
        zonasSalvacion->Add(System::Drawing::Rectangle(174, 186, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(438, 186, 30, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(693, 186, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(953, 186, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(1218, 186, 50, 50));


        tiempoInicio = clock();
        if (skin == 1) {
            imgJugador = gcnew Bitmap("img/nivel2/RanitasNivel2.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel2/RanayBBNivel2V2.png");
        }
        else if (skin == 2) {
            imgJugador = gcnew Bitmap("img/nivel2/RanaRFNivel2.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel2/RanaRFbbNivel2.png");
        }
        else if (skin == 3) {
            imgJugador = gcnew Bitmap("img/nivel2/RanaANNivel2.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel2/RanaANbbNivel2.png");
        }
        else if (skin == 4) {
            imgJugador = gcnew Bitmap("img/nivel2/RanaVPNivel2.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel2/RanaVpBBNivel2.png");
        }

        imgAliados1 = gcnew Bitmap("img/nivel2/TroncorotoNivel2.png");
        imgAliados2 = gcnew Bitmap("img/nivel2/TroncobuenoNivel2.png");
        imgEnemigos = gcnew Bitmap("img/nivel2/caimanMaloNivel2.png");
        imgEnemigos1 = gcnew Bitmap("img/nivel2/caimanBuenoNivel2.png");
        imgRanita1 = gcnew Bitmap("img/ranita.png");
        imgRanita2 = gcnew Bitmap("img/ranita.png");
        imgCorazon = gcnew Bitmap("img/corazon.png");

        Random^ rnd = gcnew Random();
        posXInicial = rnd->Next(2, 1460);
        posYInicial = 775;

        jugador = new JugadorNivel2(imgJugador, v);
        jugador->SetX(posXInicial);
        jugador->SetY(posYInicial);

        aliados = new AliadosNivel2(imgAliados1);
        enemigos = new EnemigosNivel2(imgEnemigos);
        ranitas = new Ranitas();
        ranitas->GenerarRanitas(imgRanita1, imgRanita2);

        cooldownAtaqueEnemigo = 0;
        this->nombreJugador = nombreJugador;
        tiempo = t * 1000;
        cambioImagen = false;
        tieneRanita = false;

        puntaje = 0;
        ranasSalvadas = 0;
    }
    int GetJugadorVidas() {
        return jugador->GetVidas();
    }

    int GetPuntaje() {
        return puntaje;
    }

    ~ControladorNivel2() {
        delete jugador;
        delete aliados;
        delete enemigos;
        delete imgAliados1;
        delete imgAliados2;
        delete imgJugador;
        delete imgJugadorModificado;
        delete imgRanita1;
        delete imgRanita2;
        delete imgCorazon;
    }

    bool EstaEnZonaSalvacion(Ranita* ranita) {
        System::Drawing::Rectangle hitboxRanita = ranita->HitBox();
        for each (System::Drawing::Rectangle zona in zonasSalvacion) {
            if (zona.IntersectsWith(hitboxRanita)) {
                return true;
            }
        }
        return false;
    }

    void SetJugadorVidas(int vidas) {
        jugador->SetVidas(vidas);
    }

    void MovimientoJugador(bool accion, Keys tecla) {
        int vx, vy;
        if (jugador->GetY() >= 675) {
            vx = 20;
            vy = 20;
        }
        else if (jugador->GetY() == 206) {
            vx = 23; vy = 20;
        }
        /*else if (jugador->GetY() ==265) {
            vx = 23; vy = 59;
        }*/
        else {
            vy = 82;
            vx = 15;
        }


        if (accion) {
            if (tecla == Keys::Up) {
                jugador->SetDy(-vy);
                jugador->SetAccion(CaminarArriba);
            }
            else if (tecla == Keys::Down) {
                jugador->SetDy(vy);
                jugador->SetAccion(CaminarAbajo);
            }
            else if (tecla == Keys::Left) {
                jugador->SetDx(-vx);
                jugador->SetAccion(CaminarIzquierda);
            }
            else if (tecla == Keys::Right) {
                jugador->SetDx(vx);
                jugador->SetAccion(CaminarDerecha);
            }
        }
        else {
            jugador->SetDx(0);
            jugador->SetDy(0);
        }
    }

    // **Nuevo: Verificar si el jugador colisiona con una ranita y manejar el cambio de imagen**
    void VerificarColisionConRanita(Keys tecla) {
        if (tecla == Keys::Space) { // **Usar barra espaciadora**
            if (!tieneRanita) { // **Si no tiene ranita, recogerla**
                for (int i = 0; i < ranitas->GetLista().size(); i++) {
                    if (jugador->HitBox().IntersectsWith(ranitas->GetLista()[i]->HitBox())) {
                        delete ranitas->GetLista()[i]; // **Eliminar la ranita recogida**
                        ranitas->GetLista().erase(ranitas->GetLista().begin() + i);
                        cambioImagen = true; // **Cambiar la imagen del jugador**
                        tieneRanita = true; // **Marcar que tiene una ranita**
                        break;
                    }
                }
            }
            else { // **Si ya tiene ranita, intentar colocarla**
                int x = jugador->GetX();
                int y = jugador->GetY();

                // **Verificar si la nueva ranita colisiona con otra ya existente**
                for each (Ranita * ranita in ranitas->GetLista()) {
                    if (ranita->HitBox().IntersectsWith(System::Drawing::Rectangle(x, y, 40, 40))) {
                        return; // No colocar la ranita si se superpone con otra
                    }
                }

                //**Si no hay colisi�n, colocar la ranita**
                ranitas->AgregarRanita(x, y, imgRanita1, imgRanita2);
                cambioImagen = false; // **Volver a la imagen original**
                tieneRanita = false; // **Restablecer estado**
            }
        }
    }

    int GetJugadorY() {
        return jugador->GetY();
    }

    void VerificarRanasSalvadas() {
        int nuevasRanasSalvadas = 0;

        for each (Ranita * ranita in ranitas->GetLista()) {
            if (EstaEnZonaSalvacion(ranita)) {
                nuevasRanasSalvadas++;
            }
        }

        int diferencia = nuevasRanasSalvadas - ranasSalvadas;

        if (diferencia > 0) {
            puntaje += 10 * diferencia;
        }
        else if (diferencia < 0) {
            puntaje -= 10 * (-diferencia);
        }

        ranasSalvadas = min(nuevasRanasSalvadas, 4);
    }

    void Mostrar(Graphics^ g) {
        // imgRanita1 ya est� precargada en el constructor: se reutiliza en vez de recargar el archivo 30 veces por segundo
        g->DrawString("NIVEL 2", gcnew Font("Arial Black", 20), Brushes::White, 35, 4);
        g->DrawString("presiona 'space' para recoger / dejar a las ranitas", gcnew Font("Arial Black", 10), Brushes::White, 590, 98);
        g->DrawString("PLAYER: " + nombreJugador, gcnew Font("Arial Black", 18), Brushes::White, 336, 20);
        g->DrawString("PUNTAJE: ", gcnew Font("Arial Black", 16), Brushes::Lime, 898, 13);
        g->DrawString(puntaje.ToString(), gcnew Font("Arial Black", 16), Brushes::Lime, 950, 38);
        g->DrawImage(imgRanita1, 1040, 13, 30, 30); // Dibuja la imagen en (1040, 13) con tama�o 30x30
        g->DrawString("SALVADAS", gcnew Font("Arial Black", 16), Brushes::White, 1070, 13);
        g->DrawString(ranasSalvadas.ToString() + "/4", gcnew Font("Arial Black", 16), Brushes::White, 1070, 38);


        // **Calcular tiempo transcurrido y tiempo restante con espera de 5 segundos**
        int tiempoTranscurrido = max(0, (clock() - tiempoInicio) / CLOCKS_PER_SEC - 5);
        int tiempoRestante = max(0, 270 - tiempoTranscurrido);

        // **Convertir a formato MM:SS**
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        String^ tiempoFormateado = minutos.ToString("00") + ":" + segundos.ToString("00");

        // **Mostrar "TIEMPO :" y el tiempo formateado en pantalla**
        g->DrawString("TIEMPO:", gcnew Font("Arial Black", 16), Brushes::Yellow, 650, 13);
        g->DrawString(tiempoFormateado, gcnew Font("Arial Black", 16), Brushes::White, 660, 38);


        aliados->Mostrar(g, imgAliados1, imgAliados2);
        enemigos->Mostrar(g, imgEnemigos, imgEnemigos1);
        ranitas->Mostrar(g, imgRanita1, imgRanita2);

        if (cambioImagen) {
            jugador->Mostrar(g, imgJugadorModificado, imgCorazon);
        }
        else {
            jugador->Mostrar(g, imgJugador, imgCorazon);
        }
    }


    void Mover(Graphics^ g, int Tipo) {
        bool sobrePlataforma = false;
        bool sobreTroncoBueno = false;
        bool sobreCaimanBueno = false;
        int desplazamientoPlataforma = 0;
        int limiteIzquierdo = 0, limiteDerecho = 0;

        // **Verificar si el jugador est� sobre un caim�n bueno**
        for (Enemigo* e : enemigos->GetLista()) {
            if (jugador->Area().IntersectsWith(e->Area())) {
                if (e->GetTipo() == 1) {
                    desplazamientoPlataforma = e->GetDx();
                    sobrePlataforma = true;
                    sobreCaimanBueno = true;
                    limiteIzquierdo = e->GetX() + 35;
                    limiteDerecho = e->GetX() + e->GetAncho() - jugador->GetAncho() - 15;
                }
                else {
                    jugador->RestarVida();
                    ReiniciarPosicion();
                    return;
                }
            }
        }

        for (Aliado* a : aliados->GetLista()) {
            if (jugador->Area().IntersectsWith(a->Area())) {
                if (a->GetTipo() == 1) {
                    desplazamientoPlataforma = a->GetDx();
                    sobrePlataforma = true;
                    sobreTroncoBueno = true;
                    limiteIzquierdo = a->GetX() + 10;
                    limiteDerecho = a->GetX() + a->GetAncho() - jugador->GetAncho() - 15;
                }
                else {
                    jugador->RestarVida();
                    ReiniciarPosicion();
                    return;
                }
            }
        }

        VerificarRanasSalvadas();
        // **Si est� sobre una plataforma en movimiento**
        if (sobrePlataforma) {
            if (jugador->GetDx() == 0) {
                jugador->SetX(jugador->GetX() + desplazamientoPlataforma);
            }
            else {
                int nuevaX = jugador->GetX() + jugador->GetDx();
                if (nuevaX < limiteIzquierdo) {
                    jugador->SetX(limiteIzquierdo);
                }
                else if (nuevaX > limiteDerecho) {
                    jugador->SetX(limiteDerecho);
                }
                else {
                    jugador->SetX(nuevaX);
                }
            }
        }

        // **Si el jugador cae al lago, reaparece**
        if (jugador->GetY() >= 254 && jugador->GetY() < 675) {
            if (!sobreTroncoBueno && !sobreCaimanBueno) {
                jugador->RestarVida(); // **Restar una vida**
                ReiniciarPosicion();
                return;
            }
        }

        // **Si el jugador llega a los bordes mientras est� sobre una plataforma, reaparece**
        if ((jugador->GetX() <= 0 || jugador->GetX() >= 1508) && (sobreTroncoBueno || sobreCaimanBueno)) {
            jugador->RestarVida(); // **Restar una vida**
            ReiniciarPosicion();
            return;
        }

        jugador->Mover(g);
        aliados->Mover(g, imgAliados1, imgAliados2, 1508);
        enemigos->Mover(g, imgEnemigos, imgEnemigos1, 1507);
    }

    void ReiniciarPosicion() {
        jugador->SetX(rand() % 1441);
        jugador->SetY(775);
    }
};
ref class ControladorNivel3 {
private:
    JugadorNivel3* jugador;
    AliadosNivel3* aliados;
    EnemigosNivel3* enemigos;
    Ranitas* ranitas;

    Bitmap^ imgAliados1;
    Bitmap^ imgAliados2;
    Bitmap^ imgJugador;
    Bitmap^ imgJugadorModificado;
    Bitmap^ imgEnemigos;
    Bitmap^ imgEnemigos1;
    Bitmap^ imgRanita1;
    Bitmap^ imgRanita2;
    Bitmap^ imgCorazon; // Precargada una sola vez (antes se recargaba en cada frame)

    int cooldownAtaqueEnemigo;
    int tiempo;
    int posXInicial;
    int posYInicial;
    bool cambioImagen;
    bool tieneRanita;
    clock_t tiempoInicio;
    String^ nombreJugador;

    int puntaje;
    int ranasSalvadas;
    List<System::Drawing::Rectangle>^ zonasSalvacion;

public:
    ControladorNivel3(int v, int t, String^ nombreJugador, int skin) {
        zonasSalvacion = gcnew List<System::Drawing::Rectangle>();
        zonasSalvacion->Add(System::Drawing::Rectangle(335, 140, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(594, 140, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(849, 140, 50, 50));
        zonasSalvacion->Add(System::Drawing::Rectangle(1105, 140, 50, 50));

        tiempoInicio = clock();
        if (skin == 1) {
            imgJugador = gcnew Bitmap("img/nivel3/RanitasNivel3.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel3/RanayBBNivel3.png");
        }
        else if (skin == 2) {
            imgJugador = gcnew Bitmap("img/nivel3/RanaRFNivel3.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel3/RanaRFbbNivel3.png");
        }
        else if (skin == 3) {
            imgJugador = gcnew Bitmap("img/nivel3/RanaANNivel3.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel3/RanaANbbNivel3.png");
        }
        else if (skin == 4) {
            imgJugador = gcnew Bitmap("img/nivel3/RanaVPNivel3.png");
            imgJugadorModificado = gcnew Bitmap("img/nivel3/RanaVPBBNivel3.png");
        }

        imgAliados1 = gcnew Bitmap("img/nivel3/TroncorotoNivel3.png");
        imgAliados2 = gcnew Bitmap("img/nivel3/TroncobuenoNivel3.png");
        imgEnemigos = gcnew Bitmap("img/nivel3/caimanMaloNivel3.png");
        imgEnemigos1 = gcnew Bitmap("img/nivel3/caimanBuenoNivel3.png");
        imgRanita1 = gcnew Bitmap("img/ranita.png");
        imgRanita2 = gcnew Bitmap("img/ranita.png");
        imgCorazon = gcnew Bitmap("img/corazon.png");

        Random^ rnd = gcnew Random();
        posXInicial = rnd->Next(2, 1457);
        posYInicial = 775;

        jugador = new JugadorNivel3(imgJugador, v);
        jugador->SetX(posXInicial);
        jugador->SetY(posYInicial);

        aliados = new AliadosNivel3(imgAliados1);
        enemigos = new EnemigosNivel3(imgEnemigos);
        ranitas = new Ranitas();
        ranitas->GenerarRanitas(imgRanita1, imgRanita2);

        cooldownAtaqueEnemigo = 0;
        this->nombreJugador = nombreJugador;
        tiempo = t * 1000;
        cambioImagen = false;
        tieneRanita = false;

        puntaje = 0;
        ranasSalvadas = 0;
    }

    int GetJugadorVidas() {
        return jugador->GetVidas();
    }
    void SetJugadorVidas(int vidas) {
        jugador->SetVidas(vidas);
    }

    int GetPuntaje() {
        return puntaje;
    }

    ~ControladorNivel3() {
        delete jugador;
        delete aliados;
        delete enemigos;
        delete imgAliados1;
        delete imgAliados2;
        delete imgJugador;
        delete imgJugadorModificado;
        delete imgRanita1;
        delete imgRanita2;
        delete imgCorazon;
    }


    bool EstaEnZonaSalvacion(Ranita* ranita) {
        System::Drawing::Rectangle hitboxRanita = ranita->HitBox();
        for each (System::Drawing::Rectangle zona in zonasSalvacion) {
            if (zona.IntersectsWith(hitboxRanita)) {
                return true;
            }
        }
        return false;
    }

    void MovimientoJugador(bool accion, Keys tecla) {
        int vx, vy;
        if (jugador->GetY() >= 660) {
            vx = 23;
            vy = 23;
        }
        else if (jugador->GetY() == 70) {
            vx = 23; vy = 88;
        }
        else {
            vy = 88;
            vx = 15;
        }

        if (accion) {
            if (tecla == Keys::Up) {
                jugador->SetDy(-vy);
                jugador->SetAccion(CaminarArriba);
            }
            else if (tecla == Keys::Down) {
                jugador->SetDy(vy);
                jugador->SetAccion(CaminarAbajo);
            }
            else if (tecla == Keys::Left) {
                jugador->SetDx(-vx);
                jugador->SetAccion(CaminarIzquierda);
            }
            else if (tecla == Keys::Right) {
                jugador->SetDx(vx);
                jugador->SetAccion(CaminarDerecha);
            }
        }
        else {
            jugador->SetDx(0);
            jugador->SetDy(0);
        }
    }

    // **Nuevo: Verificar si el jugador colisiona con una ranita y manejar el cambio de imagen**
    void VerificarColisionConRanita(Keys tecla) {
        if (tecla == Keys::Space) { // **Usar barra espaciadora**
            if (!tieneRanita) { // **Si no tiene ranita, recogerla**
                for (int i = 0; i < ranitas->GetLista().size(); i++) {
                    if (jugador->HitBox().IntersectsWith(ranitas->GetLista()[i]->HitBox())) {
                        delete ranitas->GetLista()[i]; // **Eliminar la ranita recogida**
                        ranitas->GetLista().erase(ranitas->GetLista().begin() + i);
                        cambioImagen = true; // **Cambiar la imagen del jugador**
                        tieneRanita = true; // **Marcar que tiene una ranita**
                        break;
                    }
                }
            }
            else { // **Si ya tiene ranita, intentar colocarla**
                int x = jugador->GetX();
                int y = jugador->GetY();

                // **Verificar si la nueva ranita colisiona con otra ya existente**
                for each (Ranita * ranita in ranitas->GetLista()) {
                    if (ranita->HitBox().IntersectsWith(System::Drawing::Rectangle(x, y, 40, 40))) {
                        return; // No colocar la ranita si se superpone con otra
                    }
                }

                //**Si no hay colisi�n, colocar la ranita**
                ranitas->AgregarRanita(x, y, imgRanita1, imgRanita2);
                cambioImagen = false; // **Volver a la imagen original**
                tieneRanita = false; // **Restablecer estado**
            }
        }
    }

    int GetJugadorY() {
        return jugador->GetY();
    }

    void VerificarRanasSalvadas() {
        int nuevasRanasSalvadas = 0;

        for each (Ranita * ranita in ranitas->GetLista()) {
            if (EstaEnZonaSalvacion(ranita)) {
                nuevasRanasSalvadas++;
            }
        }

        int diferencia = nuevasRanasSalvadas - ranasSalvadas;

        if (diferencia > 0) {
            puntaje += 10 * diferencia;
        }
        else if (diferencia < 0) {
            puntaje -= 10 * (-diferencia);
        }

        ranasSalvadas = min(nuevasRanasSalvadas, 4);
    }

    void Mostrar(Graphics^ g) {
        // imgRanita1 ya est� precargada en el constructor: se reutiliza en vez de recargar el archivo 30 veces por segundo
        g->DrawString("NIVEL 3", gcnew Font("Arial Black", 20), Brushes::Black, 35, 4);
        g->DrawString("presiona 'space' para recoger / dejar a las ranitas", gcnew Font("Arial Black", 10), Brushes::Blue, 590, 110);
        g->DrawString("PLAYER: " + nombreJugador, gcnew Font("Arial Black", 18), Brushes::White, 336, 20);
        g->DrawString("PUNTAJE: ", gcnew Font("Arial Black", 16), Brushes::Lime, 898, 13);
        g->DrawString(puntaje.ToString(), gcnew Font("Arial Black", 16), Brushes::Lime, 952, 38);
        g->DrawImage(imgRanita1, 1040, 13, 30, 30); // Dibuja la imagen en (1040, 13) con tama�o 30x30
        g->DrawString("SALVADAS", gcnew Font("Arial Black", 16), Brushes::White, 1070, 13);
        g->DrawString(ranasSalvadas.ToString() + "/4", gcnew Font("Arial Black", 16), Brushes::White, 1070, 38);

        // **Calcular tiempo transcurrido y tiempo restante**
        int tiempoTranscurrido = max(0, (clock() - tiempoInicio) / CLOCKS_PER_SEC - 5);
        int tiempoRestante = max(0, 250 - tiempoTranscurrido);

        // **Convertir a formato MM:SS**
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        String^ tiempoFormateado = minutos.ToString("00") + ":" + segundos.ToString("00");

        // Mostrar en pantalla
        g->DrawString("TIEMPO:", gcnew Font("Arial Black", 16), Brushes::Yellow, 650, 13);
        g->DrawString(tiempoFormateado, gcnew Font("Arial Black", 16), Brushes::White, 660, 38);


        aliados->Mostrar(g, imgAliados1, imgAliados2);
        enemigos->Mostrar(g, imgEnemigos, imgEnemigos1);
        ranitas->Mostrar(g, imgRanita1, imgRanita2);

        if (cambioImagen) {
            jugador->Mostrar(g, imgJugadorModificado, imgCorazon);
        }
        else {
            jugador->Mostrar(g, imgJugador, imgCorazon);
        }
    }


    void Mover(Graphics^ g, int Tipo) {
        bool sobrePlataforma = false;
        bool sobreTroncoBueno = false;
        bool sobreCaimanBueno = false;
        int desplazamientoPlataforma = 0;
        int limiteIzquierdo = 0, limiteDerecho = 0;

        // **Verificar si el jugador est� sobre un caim�n bueno**
        for (EnemigoN3* e : enemigos->GetLista()) {
            if (jugador->Area().IntersectsWith(e->Area())) {
                if (e->GetTipo() == 1) {
                    desplazamientoPlataforma = e->GetDx();
                    sobrePlataforma = true;
                    sobreCaimanBueno = true;
                    limiteIzquierdo = e->GetX() + 35;
                    limiteDerecho = e->GetX() + e->GetAncho() - jugador->GetAncho() - 15;
                }
                else {
                    jugador->RestarVida();
                    ReiniciarPosicion();
                    return;
                }
            }
        }

        for (AliadoN3* a : aliados->GetLista()) {
            if (jugador->Area().IntersectsWith(a->Area())) {
                if (a->GetTipo() == 1) {
                    desplazamientoPlataforma = a->GetDx();
                    sobrePlataforma = true;
                    sobreTroncoBueno = true;
                    limiteIzquierdo = a->GetX() + 10;
                    limiteDerecho = a->GetX() + a->GetAncho() - jugador->GetAncho() - 15;
                }
                else {
                    jugador->RestarVida();
                    ReiniciarPosicion();
                    return;
                }
            }
        }

        VerificarRanasSalvadas();
        // **Si est� sobre una plataforma en movimiento**
        if (sobrePlataforma) {
            if (jugador->GetDx() == 0) {
                jugador->SetX(jugador->GetX() + desplazamientoPlataforma);
            }
            else {
                int nuevaX = jugador->GetX() + jugador->GetDx();
                if (nuevaX < limiteIzquierdo) {
                    jugador->SetX(limiteIzquierdo);
                }
                else if (nuevaX > limiteDerecho) {
                    jugador->SetX(limiteDerecho);
                }
                else {
                    jugador->SetX(nuevaX);
                }
            }
        }

        // **Si el jugador cae al lago, reaparece**
        if (jugador->GetY() >= 210 && jugador->GetY() < 640) {
            if (!sobreTroncoBueno && !sobreCaimanBueno) {
                jugador->RestarVida(); // **Restar una vida**
                ReiniciarPosicion();
                return;
            }
        }

        // **Si el jugador llega a los bordes mientras est� sobre una plataforma, reaparece**
        if ((jugador->GetX() <= 0 || jugador->GetX() >= 1508) && (sobreTroncoBueno || sobreCaimanBueno)) {
            jugador->RestarVida(); // **Restar una vida**
            ReiniciarPosicion();
            return;
        }

        jugador->Mover(g);
        aliados->Mover(g, imgAliados1, imgAliados2, 1508);
        enemigos->Mover(g, imgEnemigos, imgEnemigos1, 1507);
    }

    void ReiniciarPosicion() {
        jugador->SetX(rand() % 1441);
        jugador->SetY(775);
    }
};