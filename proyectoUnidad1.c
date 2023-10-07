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
        printf("\nnombreCarta: %s,tipoCarta: %s, vidaCarta: %d, ataqueCarta: %d., defensaCarta: %d.\n", actualCarta->nombreCarta,actualCarta->tipoCarta, actualCarta->puntosVida,actualCarta->puntosAtaque ,actualCarta->puntosDefensa);
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

void initFromText(Carta **primeraCarta){

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

    Carta *primeraCarta = NULL;
    Carta *nuevaCarta;
    initFromText(&primeraCarta);
    int opcion;
    char nom[50];
    char tipo[50];
    int vida, defensa,ataque;

    nuevaCarta = crear_Cartita_Mazo("Alan","Mago",10,10,10);
    add_Cartita_Mazo(&primeraCarta, nuevaCarta);

    nuevaCarta = crear_Cartita_Mazo("Matias","Brujo",10,10,10);
    add_Cartita_Mazo(&primeraCarta, nuevaCarta);

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
