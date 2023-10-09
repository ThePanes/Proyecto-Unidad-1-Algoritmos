#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Carta *mazoPersonaje;
}Jugador;

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

Jugador *crear_Jugadores(char *nombreNuevoJugador){
    //creamos jugadores al igual como creamos una carta, por lo cual, creamos una lista de cartas.
    Jugador *nuevoJugador = (Jugador*)malloc(sizeof(Jugador));
    strcpy(nuevoJugador->nombreJugador, nombreNuevoJugador);
    nuevoJugador->mazoPersonaje = NULL;
    return nuevoJugador;
}

void agregar_Cartitas_Mazo_Jugador(Jugador *jugador, Carta *CartaParaJugador ){
        add_Cartita_Mazo(&(jugador->mazoPersonaje),CartaParaJugador);
}

//falta terminar la siguiente funcion, de momento no aseguro su funcionamiento.

void repartir_Aleatorio(Carta **mazoCartas, Jugador *jugador){

    if(*mazoCartas == NULL){
        return;
    }
    srand(time(NULL));
    int cartasTotales = 0;
    Carta *cartaActual = *mazoCartas;
    while (cartaActual != NULL) {
                            //aqui sumamos el total de las cartas en un contador (solo usamos carta actual para recorrer la cantidad de elementos)
        cartasTotales++;
        cartaActual = cartaActual->siguiente;
    }
    //tenemos el numero de la carta aleatoria entre la cantidad total de cartas
    int cartaAleatoriaPos = rand() % cartasTotales;
                                //volvemos al primer caso, para asi tener el principio del mazo
    cartaActual = *mazoCartas;
                                //recorremos la lista de cartas hasta llegar a la posicion actual de la carta aleatoria en el maoz
    for(int i = 0 ; i < cartaAleatoriaPos; i++){
        cartaActual = cartaActual->siguiente;
    }
                                    //si la posicion de la carta aleatoria es 0, es la primera carta del mazo, de lo contrario...
    if(cartaAleatoriaPos == 0){

        *mazoCartas = cartaActual->siguiente;
    }else{                          //funcion vista en clases,
        Carta *anterior = *mazoCartas;
        while(anterior->siguiente != cartaActual){
            anterior = anterior->siguiente;
        }
        anterior->siguiente = cartaActual->siguiente;
    }
    cartaActual->siguiente = NULL;
    agregar_Cartitas_Mazo_Jugador(jugador,cartaActual);
}

void imprimeCartas(Carta *primeraCarta) {
    Carta *actualCarta = primeraCarta;
    while (actualCarta != NULL) {
        printf("\nnombreCarta: %s,tipoCarta: %s, vidaCarta: %d, ataqueCarta: %d., defensaCarta: %d.\n", actualCarta->nombreCarta,actualCarta->tipoCarta, actualCarta->puntosVida,actualCarta->puntosAtaque ,actualCarta->puntosDefensa);
        actualCarta = actualCarta->siguiente;
    }
}

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

    //nuevaCarta = crear_Cartita_Mazo("Alan","Mago",/*vida*/10,/*ataque*/10,/*defensa*/10);
    //add_Cartita_Mazo(&primeraCarta, nuevaCarta);

    //nuevaCarta = crear_Cartita_Mazo("Matias","Brujo",10,10,10);
    //add_Cartita_Mazo(&primeraCarta, nuevaCarta);

    Jugador *nuevoJugador = crear_Jugadores("El brayan");

    //agregar_Cartitas_Mazo_Jugador(nuevoJugador,nuevaCarta);

    for(int i = 0; i < 15; i++){
        repartir_Aleatorio(&primeraCarta, nuevoJugador);
    }
    printf("\n A continuacion, las cartas del jugador:\n");
    imprimeCartas(nuevoJugador->mazoPersonaje);

    printf("\n nueva lista de cartas:\n");
    imprimeCartas(primeraCarta);

    printf("\nBienvenido, que desea hacer?\n");
    printf("\1.nueva carta en mazo");
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

        default: break;
    }

    return 0;
}
