#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 500
typedef struct Carta{
    char nombreCarta[50];
    char tipoCarta[50];
    int puntosVida;
    int puntosDefensa;
    int puntosAtaque;
    struct Carta *siguiente;
}Carta;

typedef struct Jugador{
    char nombreJugador[50];
    int vidaJugador;
    Carta *mazoPersonal;
    Carta *cartasenMano;
    Carta *cartasMesaJugador;
}Jugador;

Carta *crear_Cartita_Mazo(char *nombreC, char *tipoC, int vidaC, int defensaC, int ataqueC);
Jugador *crear_Jugadores(char *nombreNuevoJugador);
void add_Cartita_Mazo(Carta **primeraCarta, Carta *nuevaCartaMazo);
void agregar_Cartitas_Mazo_Jugador(Jugador *jugador, Carta *CartaParaJugador );
void eliminar_Cartas(Carta **primeraCarta, Carta *cartaEliminar);
void imprimir_mesa(Carta *primeraCarta);
void imprimeCartas(Carta *primeraCarta);
void agregar_Cartitas_Mesa_Jugador(Jugador *jugador, Carta *CartaParaJugador );
Carta *get_carta_en_posicion(Carta *primera, int pos);
void jugar_Partida(Jugador *jugador, Jugador *maquina);
void agregar_Cartitas_Mano_Jugador(Jugador *jugador, Carta *CartaParaJugador );
void sacarCartas(Jugador *jugador);
void initFromText(Carta **primeraCarta);
void liberar_Espacio_Cartitas(Carta *primeraCarta);
void repartir_Aleatorio(Carta **mazoCartas, Jugador *jugador);
Carta *pop_carta(Carta **pila);
void push_carta(Carta **pila, Carta *cartaNueva);
Carta *seleccionar_carta_mesa_ataque(Jugador *jugador);
Carta *seleccionar_carta_enemiga_atacar(Jugador *adversario);
void autoTurnoMaquina(Jugador *jugador, Jugador *maquina);
Carta *seleccionar_carta_enemiga_atacar_auto(Jugador *adversario);
//void atacar_oponente(Carta *cartaAtacante,Jugador *jugador, Jugador *oponente);

int main(){

    int opcion;
    char nom[50];
    char tipo[50];
    int vida, defensa,ataque;
    Carta *primeraCarta = NULL;
    Carta *nuevaCarta;
    initFromText(&primeraCarta);

    printf("\nLista de Cartas:\n");
    imprimeCartas(primeraCarta);

                        //probando el eliminar cartas

    nuevaCarta = crear_Cartita_Mazo("Alan","Mago",/*vida*/10,/*ataque*/10,/*defensa*/10);
    add_Cartita_Mazo(&primeraCarta, nuevaCarta);

    printf("\n Estas son las nuevas cartas con la agregada\n");
    imprimeCartas(primeraCarta);

    printf("\n Procedemos a eliminar la ultima carta\n");
    eliminar_Cartas(&primeraCarta, nuevaCarta);

    printf("\n Este es el mazo despues de eliminar la carta:\n");
    imprimeCartas(primeraCarta);
    //nuevaCarta = crear_Cartita_Mazo("Matias","Brujo",10,10,10);
    //add_Cartita_Mazo(&primeraCarta, nuevaCarta);

                                //Fin prueba de eliminar cartas

    Jugador *nuevoJugador = crear_Jugadores("El brayan");
    Jugador *maquina = crear_Jugadores("Maquina");
    //printf("\n Creamos los jugadores.");

    //agregar_Cartitas_Mazo_Jugador(nuevoJugador,nuevaCarta);

    for(int i = 0; i < 15; i++){
        repartir_Aleatorio(&primeraCarta, nuevoJugador);
        repartir_Aleatorio(&primeraCarta, maquina);
    }
    printf("\n A continuacion, las cartas del jugador:\n");
    imprimeCartas(nuevoJugador->mazoPersonal);
    printf("\n A continuacion, las cartas de la maquina:\n");
    imprimeCartas(maquina->mazoPersonal);

    printf("\n nueva lista de cartas:\n");
    imprimeCartas(primeraCarta);

    printf("\nBienvenido, que desea hacer?\n");
    printf("\n 1.poner nueva carta en mazo. /n 2._Jugar.");
    scanf("%d",&opcion);
    switch(opcion){

        case 1:
            printf("\nIngrese nombre de la carta\n");
            scanf("%s",&nom);
            printf("\nIngrese tipo de la carta\n");
            scanf("%s",&tipo);
            printf("\nIngrese vida de la carta\n");
            scanf("%d",&vida);
            printf("\nIngrese defensa de la carta\n");
            scanf("%d",&defensa);
            printf("\nIngrese ataque de la carta\n");
            scanf("%d",&ataque);
            nuevaCarta = crear_Cartita_Mazo(nom,tipo,vida,defensa,ataque);
            add_Cartita_Mazo(&primeraCarta, nuevaCarta);
            break;
        case 2:
            jugar_Partida(nuevoJugador,maquina);
            break;

        default: break;
    }

    return 0;
}
                        //con esta funcion creamos una carta, le pasamos los parametros correspondientes y se crea.
Carta *crear_Cartita_Mazo(char *nombreC, char *tipoC, int vidaC, int defensaC, int ataqueC){
    Carta *nuevaCarta = (Carta*)malloc(sizeof(Carta));
    strcpy(nuevaCarta->nombreCarta, nombreC);
    strcpy(nuevaCarta->tipoCarta, tipoC);
    nuevaCarta->puntosVida = vidaC;
    nuevaCarta->puntosDefensa = defensaC;
    nuevaCarta->puntosAtaque = ataqueC;
    nuevaCarta->siguiente = NULL;
    return nuevaCarta;
}
                    //creamos el mazo, como lista de cartas.
void add_Cartita_Mazo(Carta **primeraCarta, Carta *nuevaCartaMazo) {
    //primera carta es la primera del mazo, pero en realidad se toma como el head para la lista de cartas, por lo que recorremos esa lista
    //vemos que en esa lista si no hay una primera carta, se crea una primera carta, luego comparamos
    if (*primeraCarta == NULL) {
        *primeraCarta = nuevaCartaMazo;
    } else {
        Carta *actualCarta = *primeraCarta;
        while (actualCarta->siguiente != NULL) {
            actualCarta = actualCarta->siguiente;
        }
        actualCarta->siguiente = nuevaCartaMazo;
    }
}

void eliminar_Cartas(Carta **primeraCarta, Carta *cartaEliminar){
    if(*primeraCarta == NULL || cartaEliminar == NULL){
        return;
    }
                    //vemos si la primera carta es la carta a eliminar y la sacamos de la lista.
    if(*primeraCarta == cartaEliminar){
        *primeraCarta = cartaEliminar->siguiente;
        free(cartaEliminar);
        return;
    }
                    //creamos una actualCarta para que sea la lista, y desvincular la carta recorriendo la lista
    Carta *actualCarta = *primeraCarta;
    while(actualCarta->siguiente != NULL && actualCarta->siguiente != cartaEliminar){
        actualCarta = actualCarta->siguiente;
    }
    if(actualCarta->siguiente == NULL)
    {
        return;
    }
    actualCarta->siguiente = cartaEliminar->siguiente;
    free(cartaEliminar);
}
void imprimir_mesa(Carta *primeraCarta){
    int pos = 1;
    Carta *cartaActual = primeraCarta;
        while(cartaActual != NULL){
            printf("\n%d", pos);
            printf("nombreCarta: %s,tipoCarta: %s, vidaCarta: %d, ataqueCarta: %d., defensaCarta: %d.\n", cartaActual->nombreCarta,cartaActual->tipoCarta, cartaActual->puntosVida,cartaActual->puntosAtaque ,cartaActual->puntosDefensa);
            cartaActual = cartaActual->siguiente;
            pos++;
        }
}

void imprimeCartas(Carta *primeraCarta) {
    Carta *actualCarta = primeraCarta;
    int contarCartaPos = 1;
    while (actualCarta != NULL) {
        printf("\n%d._",contarCartaPos);
        printf("nombreCarta: %s,tipoCarta: %s, vidaCarta: %d, ataqueCarta: %d., defensaCarta: %d.\n", actualCarta->nombreCarta,actualCarta->tipoCarta, actualCarta->puntosVida,actualCarta->puntosAtaque ,actualCarta->puntosDefensa);
        actualCarta = actualCarta->siguiente;
        contarCartaPos++;
    }
}

Jugador *crear_Jugadores(char *nombreNuevoJugador){
    //creamos jugadores al igual como creamos una carta, por lo cual, creamos una lista de cartas.
    Jugador *nuevoJugador = (Jugador*)malloc(sizeof(Jugador));
    strcpy(nuevoJugador->nombreJugador, nombreNuevoJugador);
    nuevoJugador->mazoPersonal = NULL;
    nuevoJugador->cartasMesaJugador = NULL;
    nuevoJugador->cartasenMano = NULL;
    nuevoJugador->vidaJugador = 5;
    return nuevoJugador;
}
void repartir_Aleatorio(Carta **mazoCartas, Jugador *jugador){
    srand(time(NULL));
        //printf("/n Empezamos la funcion.");
    if(*mazoCartas == NULL){
        return;
    }
    if(jugador == NULL){
        return;
    }
    int cartasTotales = 0;
        //printf("/n El total de cartas es:\n %d",cartasTotales);
    Carta *cartaActual = *mazoCartas;
    while (cartaActual != NULL) {
                            //aqui sumamos el total de las cartas en un contador (solo usamos carta actual para recorrer la cantidad de elementos)
        cartasTotales++;
        cartaActual = cartaActual->siguiente;
    }
        //printf("/nAhora, despues de agregar las cartas, El total de cartas es:\n %d",cartasTotales);
    if(cartasTotales == 0){
            printf("\n El mazo esta vacio.");
        return;
    }
        //tenemos el numero de la carta aleatoria entre la cantidad total de cartas
    int cartaAleatoriaPos = rand() % cartasTotales;
                                //volvemos al primer caso, para asi tener el principio del mazo
    cartaActual = *mazoCartas;
                                //recorremos la lista de cartas hasta llegar a la posicion actual de la carta aleatoria en el maoz
    for(int i = 0 ; i < cartaAleatoriaPos; i++){
        cartaActual = cartaActual->siguiente;
    }
        // printf("La primera carta aleatoria es:%s \n",cartaActual->nombreCarta);
                                    //si la posicion de la carta aleatoria es 0, es la primera carta del mazo, de lo contrario...
    if(cartaAleatoriaPos == 0){
        *mazoCartas = cartaActual->siguiente;
    }else{                          //funcion vista en clases mas implementaciones.
        Carta *anterior = *mazoCartas;
        while(anterior->siguiente != cartaActual){
            anterior = anterior->siguiente;
        }
        anterior->siguiente = cartaActual->siguiente;
    }
    cartaActual->siguiente = NULL;
    //printf("\n La funcion hasta aqui funciona.\n");
    agregar_Cartitas_Mazo_Jugador(jugador,cartaActual);
}

void agregar_Cartitas_Mazo_Jugador(Jugador *jugador, Carta *CartaParaJugador ){
        add_Cartita_Mazo(&(jugador->mazoPersonal),CartaParaJugador);
}
void agregar_Cartitas_Mano_Jugador(Jugador *jugador, Carta *CartaParaJugador ){
        add_Cartita_Mazo(&(jugador->cartasenMano),CartaParaJugador);
}
void agregar_Cartitas_Mesa_Jugador(Jugador *jugador, Carta *CartaParaJugador ){
        add_Cartita_Mazo(&(jugador->cartasMesaJugador),CartaParaJugador);
}

void jugar_Partida(Jugador *jugador, Jugador *maquina){
    int contadorTurno = 1;
    int opcionJugador;
    while(jugador->vidaJugador != 0 || maquina->vidaJugador !=0){
        printf("\n Turno numero:\n %d",contadorTurno);
        sacarCartas(jugador);
        printf("\nEstas son las cartas en tu mano:\n");
        imprimeCartas(jugador->cartasenMano);
                //programamos el turno del jugador:
        printf("\n que desea hacer? \n 1._Atacar Carta enemiga.\n 2._Poner Carta en el campo.");
        scanf("%d",&opcionJugador);
        switch(opcionJugador){

            case 1:{
                        //arreglar funcion seleccionar carta mano
                Carta *cartaAtaque = seleccionar_carta_mesa_ataque(jugador);

                        //finamente arregle funcion seleccionar carta mano., falta implementar que se vea el numero de la carta en la pantalla para eleccion.
                if(cartaAtaque == NULL){
                    printf("\n No tienes carta para atacar. \n");
                }
                            //hacemos una funcion similar a seleccionar carta mano, pero para la mesa enemiga.
                Carta *cartaEnemiga = seleccionar_carta_enemiga_atacar(maquina);
                if(cartaEnemiga == NULL){
                    printf("\n No hay cartas para atacar. \n");
                }

                int golpeCarta = cartaAtaque->puntosAtaque - cartaEnemiga->puntosDefensa;
                if(golpeCarta > 0 ){
                    cartaEnemiga->puntosVida -= golpeCarta;

                    if(cartaEnemiga->puntosVida <= 0){
                        printf("\n Haz eliminado la carta enemiga. \n");
                        eliminar_Cartas(&(maquina->cartasMesaJugador), cartaEnemiga);
                    }
                }else{
                    printf("\n La carta enemiga resistio el ataque. \n");
                }
                break;
            }
            case 2:{
                //funcion para poner una carta de la mano en el campo del juego.
                    poner_Carta_Mesa(jugador);
                    break;
            }

            default:
                printf("\n Opcion invalida. \n");
                break;
        }
        sacarCartas(maquina);
        printf("\nHasta aqui funciona\n");
        autoTurnoMaquina(jugador,maquina);
        contadorTurno++;
    }
    if(jugador->vidaJugador < 0 ){
        printf("\n Haz perdido la partida. \n");
    }else if(maquina->vidaJugador < 0){
        printf("\n Haz ganado la partida, felicidades. \n");
    }

}

void autoTurnoMaquina(Jugador *jugador, Jugador *maquina){
    srand(time(NULL));
    int contador = 1;
    Carta *contadorCartas = maquina->cartasenMano;
    while(contadorCartas != NULL){
        contador++;
        contadorCartas = contadorCartas->siguiente;
    }
    printf("\n Turno de la maquina:\n");
    if(maquina->cartasMesaJugador == NULL){
        if(maquina->cartasenMano == NULL){
            printf("\n No tiene cartas en su mano para poner en el campo.\n");
            return;
        }
        //printf("\n Estas son las cartas en tu mano:\n");
        //imprimeCartas(maquina->cartasenMano);
        int cartaAleatoriaPosUno = rand() % contador;
        Carta *cartaEleccionUno = get_carta_en_posicion(maquina->cartasenMano,cartaAleatoriaPosUno );
        if(cartaEleccionUno == NULL){
            printf("\n No existe carta en esa posicion,reintente.\n");
            return;
        }
        eliminar_Cartas(&(maquina->cartasenMano),cartaEleccionUno);
        push_carta(&(maquina->cartasMesaJugador),cartaEleccionUno);

        printf("\n La maquina coloco una carta en la mesa.\n");
    }else{


        imprimeCartas(maquina->cartasMesaJugador);
        if(maquina->cartasMesaJugador != NULL){

            int rancarta = rand() % contador;
            Carta *cartaEleccion = get_carta_en_posicion(maquina->cartasMesaJugador, rancarta);

            if(cartaEleccion == NULL){
                printf("\n No hay cartas enemigas para atacar.\n");
                return;
            }
            Carta *cartaEnemiga = seleccionar_carta_enemiga_atacar_auto(jugador);
            if(cartaEnemiga == NULL){
                printf("\n No hay cartas enemigas para atacar.\n");
                return;
            }

            int golpeCartaAuto = cartaEleccion->puntosAtaque -  cartaEnemiga->puntosDefensa;
                if(golpeCartaAuto > 0 ){
                    cartaEnemiga->puntosVida -=golpeCartaAuto;
                    if(cartaEnemiga->puntosVida <= 0){
                            printf("\n Eliminaste la carta enemiga.\n");
                        eliminar_Cartas(&(jugador->cartasMesaJugador), cartaEnemiga);
                    }
                }else{
                    printf("\n La carta enemiga se resistio al ataque. \n");
                }
        }

    }
        //la maquina pone una carta en la mesa
    if(maquina->cartasenMano != NULL){
        printf("\n Estas son las cartas en tu mano:\n");
        imprimeCartas(maquina->cartasenMano);
        int cartaAleatoriaPos = rand() % contador;
        Carta *cartaEleccion = get_carta_en_posicion(maquina->cartasenMano,cartaAleatoriaPos );
        if(cartaEleccion == NULL){
            printf("\n No existe carta en esa posicion,reintente.\n");
            return;
        }
        eliminar_Cartas(&(maquina->cartasenMano),cartaEleccion);
        push_carta(&(maquina->cartasMesaJugador),cartaEleccion);
    }

}

Carta *seleccionar_carta_enemiga_atacar_auto(Jugador *adversario){
        srand(time(NULL));
        int contador = 1;
        Carta *contadorCartas = adversario->cartasMesaJugador;
        while(contadorCartas != NULL){
            contadorCartas = contadorCartas->siguiente;
            contador++;
        }

        if(adversario->cartasMesaJugador == NULL){
            printf("\n No tiene cartas en el campo.\n");
            return NULL;
        }
        printf("\n Estas son las cartas en el campo enemigo:\n");
        imprimir_mesa(adversario->cartasMesaJugador);
        int cartaAleatoriaPosX = rand() % contador;

        Carta *cartaEleccion = get_carta_en_posicion(adversario->cartasMesaJugador, cartaAleatoriaPosX);
        if(cartaEleccion == NULL){
            printf("\n No existe carta en esa posicion,reintente.\n");
        }
        return cartaEleccion;
}


Carta *get_carta_en_posicion(Carta *primera, int pos){
        //tenemos un contador, la idea es que esto nos devuelva la carta que queremos en la posicion que solicitamos
    int i = 1;
    Carta *cartaActual = primera;
    while(cartaActual !=NULL){
                        //si encontramos la carta en la posicion, la retornamos,pero, de no ser asi, sumamos el contador y avanzamos en la lista.a
        if(i == pos){
            return cartaActual;
        }
        cartaActual = cartaActual->siguiente;
        i++;
    }
    return NULL;
}

            //con esta funcion, logramos sacar una carta del mazo personal del jugador y la podermos añadir a la mano.
void sacarCartas(Jugador *jugador){
    if(jugador->mazoPersonal == NULL){
        printf("\n Necesita cartas en su mazo para jugar");
        return;
    }
    Carta *cartaSacada = pop_carta(&(jugador->mazoPersonal));
    push_carta(&(jugador->cartasenMano),cartaSacada);

}

Carta *seleccionar_carta_mesa_ataque(Jugador *jugador){
        int op;
        if(jugador->cartasMesaJugador == NULL){
            printf("\n No tiene cartas en tu campo para atacar.\n");
            return;
        }

        printf("\n Estas son las cartas en tu campo:\n");
        imprimeCartas(jugador->cartasMesaJugador);
        printf("\n Elige con que carta deseas atacar:\n");
        scanf("%d",&op);
        Carta *cartaEleccion = get_carta_en_posicion(jugador->cartasMesaJugador, op);
        if(cartaEleccion == NULL){
            printf("\n No existe carta en esa posicion,reintente.\n");
            return;
        }

        return cartaEleccion;
}

Carta *seleccionar_carta_enemiga_atacar(Jugador *adversario){
        int op;
        if(adversario->cartasMesaJugador == NULL){
            printf("\n No tiene cartas en el campo.\n");
            return;
        }
        printf("\n Estas son las cartas en el campo enemigo:\n");
        imprimir_mesa(adversario->cartasMesaJugador);
        printf("\n Elige a que carta deseas atacar:\n");
        scanf("%d",&op);
        Carta *cartaEleccion = get_carta_en_posicion(adversario->cartasMesaJugador, op);
        if(cartaEleccion == NULL){
            printf("\n No existe carta en esa posicion,reintente.\n");
            return;
        }
        return cartaEleccion;
}

void poner_Carta_Mesa(Jugador *jugador){
    int op;

    if(jugador->cartasenMano == NULL){
        printf("\n No tiene cartas en su mano para poner en el campo.\n");
        return;
    }

    printf("\n Estas son las cartas en tu mano:\n");
    imprimeCartas(jugador->cartasenMano);
    printf("\n Elige que carta deseas poner en el campo:\n");
    scanf("%d",&op);

    Carta *cartaEleccion = get_carta_en_posicion(jugador->cartasenMano, op);
    if(cartaEleccion == NULL){
        printf("\n No existe carta en esa posicion,reintente.\n");
        return;
    }

    eliminar_Cartas(&(jugador->cartasenMano),cartaEleccion);
    push_carta(&(jugador->cartasMesaJugador),cartaEleccion);

}
                    //funciones de pila y cola para cartas, para poder crear el mazo del jugador.
void push_carta(Carta **pila, Carta *cartaNueva){

    cartaNueva->siguiente = *pila;
    *pila = cartaNueva;

}

Carta *pop_carta(Carta **pila){

    if(*pila == NULL){
        return NULL;
    }
    Carta *cartaSacar = *pila;
    *pila = cartaSacar->siguiente;
    cartaSacar->siguiente = NULL;
    return cartaSacar;
}

/*void atacar_oponente(Carta *cartaAtacante,Jugador *jugador, Jugador *oponente){

    if(atacante->cartasMesaJugador == NULL){
        printf("\nNo tienes cartas en tu campo para atacar\n");
        return;
    }
    if(oponente->cartasMesaJugador ==NULL){
        printf("\nEl enemigo no tiene cartas en su campo de batalla\n");
        return;
    }

    Carta *cartaAtaque = atacante->cartasMesaJugador;
}
*/

void liberar_Espacio_Cartitas(Carta *primeraCarta) {
    //liberamos el espacio de las cartas, recorriendo el mazo desde la primera carta de ese mazo.
    Carta *actualCarta = primeraCarta;
    while (actualCarta != NULL) {
        Carta *siguiente = actualCarta->siguiente;
        free(actualCarta);
        actualCarta = siguiente;
    }
}

void initFromText(Carta **primeraCarta){
                                            //solo funcionara si el texto en la misma carpeta tiene el nombre guardians.txt
    char *archivito = "guardians.txt";
    FILE *file = fopen(archivito, "r");
    if (file == NULL) return;
    char line[MAX_LINE_LENGTH]; //MAX_LINE_LENGTH es un valor global que definen ustedes
    while(fgets(line, MAX_LINE_LENGTH, file)){
        Carta *nuevaCartita = (Carta*)malloc(sizeof(Carta));
        char *nombreCartitaNueva = strtok(line, ",");
        char *tipoCartitaNueva = strtok(NULL, ",");
        strcpy(nuevaCartita->nombreCarta, nombreCartitaNueva);
        strcpy(nuevaCartita->tipoCarta, tipoCartitaNueva);
        //atoi para valores enteros
        nuevaCartita->puntosVida = atoi(strtok(NULL, ",")); //atof para valores decimales
        nuevaCartita->puntosAtaque = atoi(strtok(NULL, ","));
        nuevaCartita->puntosDefensa = atoi(strtok(NULL, ","));
        nuevaCartita->siguiente = NULL;
        // Se añade el Struct creado a la lista existente.
        add_Cartita_Mazo(primeraCarta, nuevaCartita);
    }
    fclose(file);
}

