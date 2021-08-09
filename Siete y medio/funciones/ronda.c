#include "cartas.h"

int manejarRonda(Baraja mazo, const int numeroJugadores, int saldos[], int ganancias[], int tesoroBancaPrincipal, int ronda) {
    const int cartasPosibles = POSIBLES_CARTAS_JUGADOR*numeroJugadores;
    int cartasRonda[cartasPosibles], apuestas[numeroJugadores], premios[numeroJugadores];

    float puntajes[numeroJugadores], puntajeBanca = 0;
    int indiceMazo = 0;

    int tesoroBancaLocal = tesoroBancaPrincipal;

    //ordenar(mazo, LENGTH);
    //mezclarMazo(mazo);

    for(int i = 0; i<numeroJugadores+BANCA; i++){
        if(i == numeroJugadores) {
            cartasRonda[i] = repartirCarta(mazo, i);
            puntajeBanca = clasificarNaipe(cartasRonda, i);
            printf("\nLa banca recibio su carta");
        } else {
            cartasRonda[i] = repartirCarta(mazo, i);
            printf("\nJugador %d recibio su carta", (i+1));
        }
        indiceMazo++;
    }

        // COMIENZO SEGUNDO FOR
    printf("\n");
    for(int j = 0; j<numeroJugadores; j++) {
     if (saldos[j]<MINIMA_APUESTA) {
        printf("\n\nEl jugador %d no tiene dinero suficiente para jugar esta ronda.\n\n", j+1);
        puntajes[j] = DESCALIFICADO;
        apuestas[j] = NULO;
        premios[j] = NULO;
        separarBloque();
     } else {
        int indiceJugador = 0;
        int cartasDelJugador[POSIBLES_CARTAS_JUGADOR];

        cartasDelJugador[indiceJugador] = cartasRonda[j];
        indiceJugador++;

        printf("\n\n\tEs el turno del jugador %d", j+1);
        mostrarCarta(cartasRonda, j);

        // Apuesta
        apuestas[j] = 0;
        printf("\n\n\tLlego la hora de apostar");
        printf("\nSu saldo actual es de $%d\n", saldos[j]);

        int montoApuesta = ejecutarMenuApuesta(saldos, j);

        if (montoApuesta == APUESTA_INVALIDA) {
            printf("ERROR: no puede realizar esta apuesta a causa de que no tiene dinero suficiente.\n");
            apuestas[j] = apuestas[j] + APUESTA_NULA;
        } else if (montoApuesta == APUESTA_NULA) {
            printf("No se realiza ninguna apuesta.\n");
            apuestas[j] = apuestas[j] + APUESTA_NULA;
        }else {
            apuestas[j] = apuestas[j] + montoApuesta;
            printf("Exito: su desicion para la apuesta fue efectuada.\n");
            printf("\nEl saldo del jugador %d ahora es: %d\n", j+1, saldos[j]);
        }

        int respuestaApuesta = 0;
        float puntaje = 0;

        separarBloque();

        printf("\n\tEs momento para tomar una desicion!");
        while(respuestaApuesta != PLANTARSE) {

            respuestaApuesta = ejecutarMenuDesiciones();

            switch(respuestaApuesta){
                case PEDIR_CARTA:
                    cartasDelJugador[indiceJugador] = repartirCarta(mazo, indiceMazo);
                    cartasRonda[indiceMazo] = cartasDelJugador[indiceJugador];

                    indiceMazo++;
                    indiceJugador++;

                    printf("\nSe entrego una carta al jugador %d", j+1);
                    printf("\nAhora veamos sus cartas\n\n");
                    puntaje = obtenerPuntaje(cartasDelJugador, indiceJugador);
                    break;
                case PLANTARSE:
                    printf("\nEl jugador se planta.");
                    printf("\nVeamos sus cartas y luego calculemos el puntaje.\n");
                    puntaje = obtenerPuntaje(cartasDelJugador, indiceJugador);
                    break;
            }

            printf("Y su puntaje es: %.1f\n", puntaje);
            puntaje = evaluarPuntaje(puntaje);

            if (puntaje == NULO || respuestaApuesta == PLANTARSE) {
                break;
            } else {
                printf("\n\tDesea seguir apostando?");

                montoApuesta = ejecutarMenuApuesta(saldos, j);

                if (montoApuesta == APUESTA_INVALIDA) {
                    printf("\nERROR: no puede realizar esta apuesta a causa de que no tiene dinero suficiente.\n");
                    apuestas[j] = apuestas[j] + APUESTA_NULA;
                } else {
                    apuestas[j] = apuestas[j] + montoApuesta;
                    printf("Exito: su desicion para la apuesta fue efectuada.\n");
                    printf("\nEl saldo del jugador %d ahora es: %d\n", j+1, saldos[j]);
                }
            }
        }

        respuestaApuesta = 0;
        puntajes[j] = puntaje;
        premios[j] = clasificarPremio(cartasDelJugador, indiceJugador, puntaje);

        if (premios[j] == NULO) {
            printf("El usuario se paso, su bonificacion es cero.\n");
        } else {
            printf("\nLa bonificacion del jugador %d por su combinacion de cartas es: %d\n", j+1, premios[j]);
        }
        separarBloque();
     }
    }

        // BANCA
    printf("\n\n\tTurno de de la banca.");
    printf("\nEl puntaje correspondiente es: %.1f\n", puntajeBanca);

    nombrarCarta(cartasRonda, numeroJugadores);

    printf("\n\tAhora debera tomar una desicion...");
    while(puntajeBanca<SIETE_Y_MEDIO){
        if(puntajeBanca<CINCO_Y_MEDIO){
             printf("\nLa banca pide carta.");
             cartasRonda[indiceMazo] = repartirCarta(mazo, indiceMazo);
             printf("\n");
             nombrarCarta(cartasRonda, indiceMazo);
             puntajeBanca = puntajeBanca + clasificarNaipe(cartasRonda, indiceMazo);
             indiceMazo++;
        }
        if(puntajeBanca == CINCO_Y_MEDIO) {
            printf("\n5-La banca pide carta.");
            cartasRonda[indiceMazo] = repartirCarta(mazo, indiceMazo);
            printf("\n");
            nombrarCarta(cartasRonda, indiceMazo);
            puntajeBanca = puntajeBanca + clasificarNaipe(cartasRonda, indiceMazo);
            indiceMazo++;
        }
        if(puntajeBanca>=6 && puntajeBanca<SIETE_Y_MEDIO) {
             printf("\nLa banca se planta.\n");
             break;
        }
        if(puntajeBanca>SIETE_Y_MEDIO) {
            break;
        }
    }
    separarBloque();

        //ACABAR LA RONDA
    printf("\nFinalmente la banca suma un puntaje de %.1f puntos.\n", puntajeBanca);

    if (puntajeBanca>SIETE_Y_MEDIO) {
        printf("\n\tLa banca se paso, paga a los jugadores!\n");
        puntajeBanca = NULO;
        puntajes[numeroJugadores] = puntajeBanca;

        for (int i = 0; i<numeroJugadores; i++) {
            if (puntajes[i] == NULO) {
                printf("\nJugador %d no recibe pago porque perdio su apuesta.\n", i+1);
                tesoroBancaLocal = aumentarTesoroBanca(apuestas, i, tesoroBancaLocal);
            } else if (puntajes[i] == DESCALIFICADO) {
                printf("\nJugador %d no recibe pago porque esta descalificado.\n\n", i+1);
            } else {
                printf("\nJugador %d recibe su pago.", i+1);
                tesoroBancaLocal = repartirPremio(saldos, premios, apuestas, ganancias, i, tesoroBancaLocal);
            }
        }
    } else {
        puntajes[numeroJugadores] = puntajeBanca;
        for (int i = 0; i<numeroJugadores; i++) {
            printf("\n\tVeamos como le fue al jugador %d con respecto a la banca:", i+1);
            float resultado = definirGanadoresPerdedores(puntajes, puntajeBanca, apuestas, i);

            if (resultado == puntajeBanca) {
                tesoroBancaLocal = aumentarTesoroBanca(apuestas, i, tesoroBancaLocal);
            } else if (resultado == DESCALIFICADO) {
                printf("\n.\n");
            } else {
                printf("\ny la bonificacion correspondiente para el es: %d\n", premios[i]);
                tesoroBancaLocal = repartirPremio(saldos, premios, apuestas, ganancias, i, tesoroBancaLocal);
            }
        }
    }
    separarBloque();

    // Estadistica
    printf("\nLas cartas en juego para esta ronda fueron: \n");
    for(int i = 0; i<indiceMazo; i++){ nombrarCarta(cartasRonda, i); }

    int respuestaEstadistica = VALOR_INICIAL_RESPUESTA;
    while (respuestaEstadistica != SALIR_MENU_ESTADISTICA) {
        respuestaEstadistica = mostrarMenuEstadisticaRonda();

        switch (respuestaEstadistica) {
            case 1:
                printf("\n\tSaldos de la ronda:");
                imprimirEstadisticaInt(saldos, numeroJugadores);
                separarBloque();
                break;
            case 2:
                printf("\n\tApuestas de la ronda:");
                imprimirEstadisticaInt(apuestas, numeroJugadores);
                separarBloque();
                break;
            case 3:
                printf("\n\tPuntajes de la ronda:");
                imprimirEstadisticaFloat(puntajes, numeroJugadores+BANCA);
                separarBloque();
                break;
            case 4:
                printf("\nTesoro de la banca actual: %d\n", tesoroBancaLocal);
                separarBloque();
                break;
            case SALIR_MENU_ESTADISTICA:
                printf("\nUsted ha decidido salir del menu.\n");
                separarBloque();
                break;
            default:
                printf("\nUps! Parece que hubo un error.\n");
                separarBloque();
        }
    }

    respuestaEstadistica = VALOR_INICIAL_RESPUESTA;

    if (ronda == 2) {
        respuestaEstadistica = mostrarMenuEstadisticaPartida();

        switch (respuestaEstadistica) {
            case 1:
                printf("\nEstadisticas de la partida:\n");
                ejecutarEstadisticaFinal(ganancias, tesoroBancaLocal, numeroJugadores);
                separarBloque();
                break;
            case SALIR_MENU_ESTADISTICA:
                printf("\nPasar de las estadisticas.\n");
                separarBloque();
                break;
            default:
                printf("\nUps! Parece que hubo un error.");
                separarBloque();
        }
    }


    // Estadistica - Opcional
    // Utilizar varible ronda para mostrar los items adicionales
    printf("\n");
    printf("\nEl arreglo de apuestas contiene: \n");
    imprimirPosicionesArr(apuestas, numeroJugadores);
    printf("\n");
    printf("El arreglo de puntajes contiene: \n");
    imprimirPosicionesArrFloat(puntajes, numeroJugadores+BANCA);
    printf("\n");
    printf("El arreglo de premios contiene");
    imprimirPosicionesArr(premios, numeroJugadores);
    printf("\n");
    printf("\nIndice mazo vale: %d", indiceMazo);
    printf("\n");
    printf("\nEl arreglo de saldos contiene");
    imprimirPosicionesArr(saldos, numeroJugadores);
    printf("\n\nEl tesoro de la banca local es igual a: %d\n", tesoroBancaLocal);

    return tesoroBancaLocal;
}
