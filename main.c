/*
* Trabalho de Computação Concorrente - Sistema de Reserva de Assentos
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "assentos.h"

/* Variáveis globais */
t_Assento *assentos;



int main(int argc, char *argv[]) {
	int n_assentos;
	if(argc < 3 ){
		printf("Execute %s <log saida> <quantidade de assentos>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	n_assentos = atoi(argv[2]);
	
	t_Assento *test;
	assento_init(test);
	printf("Hello: %d", test->id_usuario);
	return 0;
}
