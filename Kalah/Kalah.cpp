#define PROFUNDIDAD_MAXIMA 2

#include <iostream>
#include <iomanip>

using namespace std;

int ganador;
int profundidad = 0;
int paso = 0;

void imprimirTablero(int board[]) {
	cout << "       |  13  |  12  |  11  |  10  |   9  |   8  |" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|" << "      | (" << setfill('0') << setw(2) << board[12] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[11];
	cout << ") | " << "(" << setfill('0') << setw(2) << board[10] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[9] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[8] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[7] << ") |      |" << endl;
	cout << "|      |_________________________________________|      |" << endl;
	cout << "|  " << setfill('0') << setw(2) << board[13] << "  |";
	cout << "                                         ";
	cout << "|  " << setfill('0') << setw(2) << board[6] << "  |" << endl;
	cout << "|      |_________________________________________|      |" << endl;
	cout << "|" << "      | (" << setfill('0') << setw(2) << board[0] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[1];
	cout << ") | " << "(" << setfill('0') << setw(2) << board[2] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[3] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[4] << ") | ";
	cout << "(" << setfill('0') << setw(2) << board[5] << ") |	     " << endl;
	cout << "________________________________________________________" << endl;
	cout << "       |   1  |   2  |   3  |   4  |   5  |   6  |" << endl;
	cout << endl;
}

bool verificarAccion(int tablero[], int posicionEscogida) {
	if (posicionEscogida > 6) {
		return false;
	} else if (posicionEscogida < 1) {
		return false;
	} else if (tablero[posicionEscogida - 1] == 0) {
		return false;
	}

	return true;
}

bool realizarMovimiento(int posicionEscogida, bool esLadoHumano, int tablero[]) {
	int piedrasRecogidas = tablero[posicionEscogida - 1]; 
	int aux = 0; 

	tablero[posicionEscogida - 1] = 0; 

	while (piedrasRecogidas > 0) {
		if (esLadoHumano) {
			if (posicionEscogida + aux > 13) {
				posicionEscogida = 0;
				aux = 0;
			}

			if (posicionEscogida + aux != 13) { 
				tablero[posicionEscogida + aux]++;
				piedrasRecogidas--;
			}

			if (piedrasRecogidas == 0) {
				if (posicionEscogida + aux == 6) {
					return true;
				} else if (tablero[posicionEscogida + aux] > 1) {
					piedrasRecogidas = tablero[posicionEscogida + aux];
					tablero[posicionEscogida + aux] = 0;
				}
			}

			aux++;




		} else { 


			if (posicionEscogida + aux != 6) { 
				tablero[posicionEscogida + aux]++;
				piedrasRecogidas--; 
			} 

			if (piedrasRecogidas == 0) {
				if (posicionEscogida + aux == 13) {
					return true;
				} else if (tablero[posicionEscogida + aux] > 1) {
					piedrasRecogidas = tablero[posicionEscogida + aux]; 
					tablero[posicionEscogida + aux] = 0;
				}
			}

			aux++;

			if (posicionEscogida + aux > 13) {
				posicionEscogida = 0;
				aux = 0;
			}
		}
	}

	return false;
}

bool finDeJuego(int tablero[]) {
	int contador = 0;
	int contador2 = 0;

	for (int i = 0; i < 6; i++) {
		if (tablero[i] == 0) {
			contador++;
		}
	}

	for (int i = 7; i < 13; i++) {
		if (tablero[i] == 0) {
			contador2++;
		}
	}

	if (contador == 6 || contador2 == 6) {
		if (tablero[6] > tablero[13]) {
			ganador = 1; //GANO HUMANO
		}
		else if (tablero[6] == tablero[13]) {
			ganador = 3; // EMPATE
		}
		else {
			ganador = 2; //GANO MAQUINA
		}

		return true;
	}

	return false;
}

int minMax(int& mejorMovimiento, bool esLadoHumano, int tablero[]) {
	profundidad++;

	int* aux = NULL;
	aux = new int[6];

	int tableroCopia[14]{};

	for (int i = 0; i < 14; i++) {
		tableroCopia[i] = tablero[i];
	}

	int dummy; 

	if (esLadoHumano) {
		int puntaje = tablero[6]; 

		for (int i = 0; i < 6; i++) { 
			int valorMovida = puntaje;

			if (tablero[i] != 0) {   
				bool repiteTurno = realizarMovimiento(i + 1, true, tableroCopia); 

				valorMovida = tableroCopia[6] - puntaje;

				if (repiteTurno) {
					profundidad--; 
					paso++; 
					aux[i] = valorMovida + minMax(dummy, true, tableroCopia);
					paso--;
					profundidad++;
				} else {
					if (profundidad <= PROFUNDIDAD_MAXIMA) {
						aux[i] = valorMovida - minMax(dummy, false, tableroCopia);
					} else {
						aux[i] = valorMovida;
					}
				}
			} else { 
				aux[i] = -10000;
			}

			for (int j = 0; j < 14; j++) {
				tableroCopia[j] = tablero[j];
			} 
		}
	} else {
		int puntaje = tablero[13]; 
		int huecosComputador = 0;

		for (int i = 7; i < 13; i++) { 
			int valorMovida = puntaje;

			if (tablero[i] != 0) { 
				bool repiteTurno = realizarMovimiento(i + 1, false, tableroCopia);

				valorMovida = tableroCopia[13] - puntaje;

				if (repiteTurno) {
					profundidad--; 
					paso++; 
					aux[huecosComputador] = valorMovida + minMax(dummy, false, tableroCopia);
					paso--;
					profundidad++;
				} else {
					if (profundidad <= PROFUNDIDAD_MAXIMA) {
						aux[huecosComputador] = valorMovida - minMax(dummy, true, tableroCopia);
					}
					else {
						aux[huecosComputador] = valorMovida;
					}
				}
			} else { 
				aux[huecosComputador] = -10000;
			}

			huecosComputador++;

			for (int j = 0; j < 14; j++) {
				tableroCopia[j] = tablero[j];
			} 
		}
	}

	int max = -100000000;

	for (int i = 0; i < 6; i++) {
		if (aux[i] > max) {
			max = aux[i];
			mejorMovimiento = i + 7;
		}
	}

	if (max == -10000) {
		finDeJuego(tableroCopia);

		if (!esLadoHumano) {
			if (ganador == 2) {
				max = 5000;
			} else if (ganador == 3) {
				max = -2500;
			} else {
				max = -5000;
			}
		} else {
			if (ganador == 1) {
				max = 5000;
			} else if (ganador == 3) {
				max = 2500;
			} else {
				max = -5000;
			}	
		}
	}

	profundidad--;

	delete [] aux;

	return max;
}

int main() {
	int tablero[14] = { 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0 };
	int inicia;
	bool turnoIA;

	do {
		cout << endl << "¿Quieres realizar el primer movimiento? SI (1) - NO (2).";
		cin >> inicia;

		if (inicia == 1) {
			turnoIA = false;
		} else if (inicia == 2) {
			turnoIA = true;
		} else {
			cout << "Opción no valida. Por favor presione 1 o 2." << endl;
		}
	} while (!(inicia == 1 || inicia == 2));

	imprimirTablero(tablero);

	do {
		bool accionValida = false;
		bool repiteTurno;

		if (turnoIA == false) {
			int posicionEscogida;

			cout << "Selecciona la casa que quieres mover (1 - 6)." << endl;

			do {
				
				cin >> posicionEscogida;

				accionValida = verificarAccion(tablero, posicionEscogida);

				if (accionValida == false) {
					cout << endl;
					cout << "Por favor ingresa un movimiento válido.";
					cout << endl;
				}
			} while (accionValida == false);

			repiteTurno = realizarMovimiento(posicionEscogida, true, tablero);

			if (repiteTurno) { 
				cout << endl;
				cout << "¡Ganas otro turno!" << endl;
				cout << endl;
			} else {
				turnoIA = true;

				system("CLS");
				cout << endl;
				cout << "Turno de la IA." << endl;
				cout << endl;
			}
		} else if (turnoIA == true) {
			int mejorMovimiento;

			minMax(mejorMovimiento, false, tablero);

			cout << endl;
			cout << "La IA eligió la caza #" << mejorMovimiento + 1 << endl;
			cout << endl;

			repiteTurno = realizarMovimiento(mejorMovimiento + 1, false, tablero);

			if (repiteTurno) {
				cout << endl;
				cout << "¡IA gana otro turno!" << endl;
				cout << endl;
			} else {
				turnoIA = false;

				cout << endl;
				cout << "¡Tu turno!" << endl;
				cout << endl;
			}
		}

		imprimirTablero(tablero);
	} while (finDeJuego(tablero) == false);

	cout << (ganador == 1 ? "Ganaste el juego." : ganador == 2 ? "Ganó la IA." : "Hubo un empate.") << endl;
	return 0;
}