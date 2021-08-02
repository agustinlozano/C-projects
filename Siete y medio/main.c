#include "cartas.h"

int main(void) {
    Baraja mazoPartida = {7, 27, 37, 16, 24, 5, 10, 28, 18, 33, 21, 32, 12};
    int tesoroBanca = 100000;
    int saldos[MAXIMOS_JUGADORES_POSIBLES];
    int cantidadJugadores, ronda = 0;
    char respuesta;

    ejecutarMenuPresentacion();


        // Determinar numero de jugadores
    cantidadJugadores = determinarJugadores();

        //Validar le numero de jugadores
    if (cantidadJugadores > 0 && cantidadJugadores < 6) {
        printf("El numero de jugadores se ingreso correctamente.\n");
    } else {
        printf("ERROR: Usted ha ingresado un valor incorrecto\n");
        printf("Desea volver al menu principal? [y/n]\n");
        scanf(" %c", &respuesta);
        if (respuesta == SI) {
            main();
        }
    }

    for (int i = 0; i<cantidadJugadores; i++) {
        saldos[i] = 5000;
        printf("\nSe ha acreditado $5000 en el saldo del jugador %d", i+1);
    }

    printf("\n\nTodo listo para comenzar la partida!");
    separarBloque();
    //printf("Ronda numero %d", ronda);
    //ejecutarJuego(mazoPartida, LENGTH, cantidadJugadores, saldos, tesoroBanca);

    for(int index = 0; index<cantidadJugadores; index++){
        ronda++;
        printf("\n\n\tRonda numero %d\n", ronda);
        tesoroBanca = ejecutarJuego(mazoPartida, LENGTH, cantidadJugadores, saldos, tesoroBanca);;
        printf("\nTesoro banca principal es igual a: %d", tesoroBanca);

        // Mostrar estadisticas
        printf("\nMomento de la siguiente ronda!");
        separarBloque();
    }

    return EXIT_SUCCESS;
}
