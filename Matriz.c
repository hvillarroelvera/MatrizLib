#include <stdlib.h>
#include <stdio.h>
#include "Matriz.h"

Matriz* crear(int numero_filas, int numero_columnas);
Matriz* crearZero(int numero_filas, int numero_columnas);
void printMatrix(Matriz *matriz);

int main(void){
    Matriz *A = crearZero(2,2);
    printMatrix(A);
}

Matriz* crear(int numero_filas, int numero_columnas){
    Matriz *matriz = malloc(sizeof(Matriz));
    if(!matriz){
        return NULL;
    }
    matriz->cantidad_columnas = numero_columnas;
    matriz->cantidad_filas = numero_filas;
    matriz->data = malloc(sizeof(double) * numero_columnas * numero_filas);
    if (!matriz->data) {
         free(matriz);
         return NULL;
    }
    return matriz;
}

Matriz* crearZero(int numero_filas, int numero_columnas){
    Matriz *matriz = malloc(sizeof(Matriz));
    if(!matriz){
        return NULL;
    }
    matriz->cantidad_columnas = numero_columnas;
    matriz->cantidad_filas = numero_filas;
    matriz->data = malloc(sizeof(double) * numero_columnas * numero_filas);
    if (!matriz->data) {
         free(matriz);
         return NULL;
    }

    for(int i=0;i<numero_columnas * numero_filas;i++){
        matriz->data[i] = 0.0;
    }
    return matriz;
}

void printMatrix(Matriz *matriz){
    for(int i=0;i<matriz->cantidad_filas;i++){
        for(int j=0;j<matriz->cantidad_columnas;j++){
            if(j==0){
                printf("[");
            }
            printf("%f",matriz->data[i*matriz->cantidad_columnas + matriz->cantidad_filas]);
            if(j==(matriz->cantidad_columnas-1)){
                printf("]\n");
            }else{
                printf(",");
            }
        }
    }
}

