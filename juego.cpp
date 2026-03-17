#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string> 

using namespace std;

// Prototipos
int generarcartas();
string nombrecarta(int carta);
float pedirapuestas(float dinero);
void actualizardinero(float &dinero, float apuesta, bool ganar);
void agregarcarta(int carta, int &total, int &Ascomo11);

int main() {
    float dinero = 100;
    srand(time(0));
    char opcion;

    do {
        if (dinero <= 0) {
            cout << "Te quedaste sin dinero. Fin del juego." << endl;
            break;
        }

        float apuesta = pedirapuestas(dinero);
        
        // Inicialización de variables por ronda
        int totaljugador = 0, totaljugador2 = 0, totaldealer = 0;
        int Asjugador = 0, Asjugador2 = 0, Asdealer = 0;
        bool pasasteJ1 = false, pasasteJ2 = false;

        // Repartición inicial
        agregarcarta(generarcartas(), totaljugador, Asjugador);
        agregarcarta(generarcartas(), totaljugador, Asjugador);

        agregarcarta(generarcartas(), totaljugador2, Asjugador2);
        agregarcarta(generarcartas(), totaljugador2, Asjugador2);

        int d1 = generarcartas();
        int d2 = generarcartas();
        agregarcarta(d1, totaldealer, Asdealer);
        agregarcarta(d2, totaldealer, Asdealer);

        cout << "\n------ Black Jack Edu ------" << endl;
        cout << "Carta visible del dealer: " << nombrecarta(d1) << endl;

        // --- Turno Jugador 1 ---
        cout << "\n>>> TURNO JUGADOR 1 (Total actual: " << totaljugador << ")" << endl;
        while (totaljugador <= 21) {
            cout << "¿Quieres otra carta? (s/n): ";
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {
                int nueva = generarcartas();
                agregarcarta(nueva, totaljugador, Asjugador);
                cout << "Robaste: " << nombrecarta(nueva) << " | Total: " << totaljugador << endl;
            } else break;
        }
        if (totaljugador > 21) {
            cout << "Jugador 1 se pasó!" << endl;
            pasasteJ1 = true;
        }

        // --- Turno Jugador 2 ---
        cout << "\n>>> TURNO JUGADOR 2 (Total actual: " << totaljugador2 << ")" << endl;
        while (totaljugador2 <= 21) {
            cout << "¿Quieres otra carta? (s/n): ";
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {
                int nueva = generarcartas();
                agregarcarta(nueva, totaljugador2, Asjugador2);
                cout << "Robaste: " << nombrecarta(nueva) << " | Total: " << totaljugador2 << endl;
            } else break;
        }
        if (totaljugador2 > 21) {
            cout << "Jugador 2 se pasó!" << endl;
            pasasteJ2 = true;
        }

        // --- Turno del Dealer ---
        // El dealer solo juega si al menos uno de los jugadores no se ha pasado
        if (!pasasteJ1 || !pasasteJ2) {
            cout << "\n>>> TURNO DEL DEALER <<<" << endl;
            cout << "Revela: " << nombrecarta(d1) << " y " << nombrecarta(d2) << " | Total: " << totaldealer << endl;
            while (totaldealer < 17) {
                int nueva = generarcartas();
                agregarcarta(nueva, totaldealer, Asdealer);
                cout << "Dealer roba: " << nombrecarta(nueva) << " | Total: " << totaldealer << endl;
            }
        }

        // --- Resultados (Enfocado en el Jugador 1 para la apuesta) ---
        cout << "\n--- RESULTADOS FINALES ---" << endl;
        cout << "Jugador 1: " << totaljugador << " | Jugador 2: " << totaljugador2 << " | Dealer: " << totaldealer << endl;

        if (pasasteJ1) {
            actualizardinero(dinero, apuesta, false);
        } else if (totaldealer > 21 || totaljugador > totaldealer) {
            cout << "¡Jugador 1 gana a la casa!" << endl;
            actualizardinero(dinero, apuesta, true);
        } else if (totaljugador < totaldealer) {
            cout << "La casa gana al Jugador 1." << endl;
            actualizardinero(dinero, apuesta, false);
        } else {
            cout << "Empate con la casa." << endl;
        }

        cout << "\n¿Jugar otra ronda? (s/n): ";
        cin >> opcion;

    } while (opcion == 's' || opcion == 'S');

    return 0;
}

// --- Funciones ---

int generarcartas() {
    return (rand() % 13) + 1;
}

string nombrecarta(int carta) {
    if (carta == 1) return "A";
    if (carta == 11) return "J";
    if (carta == 12) return "Q";
    if (carta == 13) return "K";
    return to_string(carta);
}

void agregarcarta(int carta, int &total, int &Ascomo11) {
    if (carta == 1) {
        total += 11;
        Ascomo11++;
    } else if (carta >= 11) {
        total += 10;
    } else {
        total += carta;
    }

    while (total > 21 && Ascomo11 > 0) {
        total -= 10;
        Ascomo11--;
    }
}

float pedirapuestas(float dinero) {
    float apuesta;
    do {
        cout << "\nSaldo: " << dinero << " | Apuesta: ";
        cin >> apuesta;
        if (apuesta > dinero || apuesta <= 0) cout << "Cantidad invalida." << endl;
    } while (apuesta > dinero || apuesta <= 0);
    return apuesta;
}

void actualizardinero(float &dinero, float apuesta, bool ganar) {
    if (ganar) {
        dinero += apuesta;
        cout << "Resultado: + " << apuesta << " | Nuevo saldo: " << dinero << endl;
    } else {
        dinero -= apuesta;
        cout << "Resultado: - " << apuesta << " | Nuevo saldo: " << dinero << endl;
    }
}