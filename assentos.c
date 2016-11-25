#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define LIVRE 0
#define RESERVADO 1

typedef struct t_Assento{
	bool ocupado;
	int id_usuario;
}t_Assento;

void assento_init(t_Assento *end){
	t_Assento *a;
	a = (t_Assento *)malloc(sizeof(t_Assento));
	a->ocupado = LIVRE;
	a->id_usuario = -1;
	*end = *a;
}

void visualizaAssentos(){
	printf("");
}

int alocaAssentoLivre(t_Assento *assento, int id){
	return 0;
}

int alocaAssentoDado(t_Assento assento, int id){
	return 0;
}

int liberaAssento(t_Assento assento, int id){
	return 0;
}
