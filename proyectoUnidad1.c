#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carta{
    char nombreCarta[50];
    char tipoCarta[50];
    int puntosVida;
    int puntosDefensa;
    int puntosAtaque;
    struct Carta *siguiente;
}Carta;

Carta* crear_Cartita_Mazo(char *nombreC, char *tipoC, int vidaC, int defensaC, int ataqueC){

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

void imprimeCartas(Carta *primeraCarta) {
    printf("\nLista de Cartas:\n");
    Carta *actualCarta = primeraCarta;
    while (actualCarta != NULL) {
        printf("\nnombreCarta: %s,tipoCarta: %s, vidaCarta: %d, defensaCarta: %d., ataqueCarta: %d.\n", actualCarta->nombreCarta,actualCarta->tipoCarta, actualCarta->puntosVida, actualCarta->puntosDefensa,actualCarta->puntosAtaque);
        actualCarta = actualCarta->siguiente;
    }
}

void liberar_Espacio_Cartitas(Carta *primeraCarta) {
    Carta *actualCarta = primeraCarta;
    while (actualCarta != NULL) {
        Carta *siguiente = actualCarta->siguiente;
        free(actualCarta);
        actualCarta = siguiente;
    }
}

int main(){

    Carta *primeraCarta = NULL;
    Carta *nuevaCarta;

    nuevaCarta = crear_Cartita_Mazo("Alan","Mago",10,10,10);
    add_Cartita_Mazo(&primeraCarta, nuevaCarta);

    nuevaCarta = crear_Cartita_Mazo("Matias","Brujo",10,10,10);
    add_Cartita_Mazo(&primeraCarta, nuevaCarta);

    imprimeCartas(primeraCarta);


    return 0;
}
