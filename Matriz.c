#include <stdlib.h>
#include <stdio.h>
#include "Matriz.h"

Matriz* crear(int numero_filas, int numero_columnas);
Matriz* crearZero(int numero_filas, int numero_columnas);
void printMatrix(Matriz *matriz);
void traspuesta(Matriz *prev_matriz, Matriz *post_matriz);
void sumar_inplace(Matriz *a, Matriz *b);
void restar_inplace(Matriz *a, Matriz *b);
Matriz* matmul(Matriz *a, Matriz *b);


int main(void){
    Matriz *A = crearZero(2,1);
    Matriz *B = crearZero(1,3);
    A->data[0] = 2.0;
    B->data[0] = 2.0;
    printMatrix(A);
    printMatrix(B);
    Matriz *C = matmul(A,B);
    printMatrix(C);
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
    printf("Imprimiendo matriz:\n");
    for(int i=0;i<matriz->cantidad_filas;i++){
        for(int j=0;j<matriz->cantidad_columnas;j++){
            if(j==0){
                printf("[");
            }
            printf("%f",matriz->data[i*matriz->cantidad_columnas + j]);
            if(j==(matriz->cantidad_columnas-1)){
                printf("]\n");
            }else{
                printf(",");
            }
        }
    }
}

void traspuesta(Matriz *prev_matriz, Matriz *post_matriz){
    for(int i=0;i<prev_matriz->cantidad_filas;i++){
        for(int j=0;j<prev_matriz->cantidad_columnas;j++){
            post_matriz->data[j* post_matriz->cantidad_columnas + i] = prev_matriz->data[i*prev_matriz->cantidad_columnas + j];
        }
    }
}

//IA
int mismaDimension(Matriz *a, Matriz *b){
    return a->cantidad_filas    == b->cantidad_filas &&
           a->cantidad_columnas == b->cantidad_columnas;
}

//IA
// a = a + b  (a se modifica, b no)
void sumar_inplace(Matriz *a, Matriz *b){
    if(!mismaDimension(a, b)){
        fprintf(stderr, "sumar_inplace: dimensiones incompatibles\n");
        return;
    }
    int n = a->cantidad_filas * a->cantidad_columnas;
    for(int i = 0; i < n; i++){
        a->data[i] += b->data[i];
    }
}

//IA
// a = a - b  (a se modifica, b no)
void restar_inplace(Matriz *a, Matriz *b){
    if(!mismaDimension(a, b)){
        fprintf(stderr, "restar_inplace: dimensiones incompatibles\n");
        return;
    }
    int n = a->cantidad_filas * a->cantidad_columnas;
    for(int i = 0; i < n; i++){
        a->data[i] -= b->data[i];
    }
}

//naive matmul
Matriz* matmul(Matriz *a, Matriz *b){
    if(a->cantidad_columnas != b->cantidad_filas){
        printf("Dimensiones de matrices son distintas.");
        return NULL;
    }
    int newFila = a->cantidad_filas;
    int newColumna = b->cantidad_columnas;
    Matriz *c = malloc(sizeof(Matriz));
    c->cantidad_columnas = newColumna;
    c->cantidad_filas = newFila;
    c->data = malloc(sizeof(double) * newFila * newColumna);
    for(int i=0;i<a->cantidad_filas;i++){
        for(int j=0;j<b->cantidad_columnas;j++){
            c->data[i*newFila + j] = 0;
            for(int k=0;k<a->cantidad_columnas;k++){
                printf("valor de a: [%f]\n",a->data[i*newFila + k]);
                printf("valor de b: [%f]\n",b->data[k* newFila + j]);
                c->data[i*c->cantidad_columnas + j] += a->data[i*a->cantidad_columnas + k] * b->data[k* b->cantidad_columnas + j];
                printf("[%f]\n",c->data[i*newFila + j]);
            }
        }
    }
    return c;
}