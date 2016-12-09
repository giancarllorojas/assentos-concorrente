/*
* Trabalho de Computação Concorrente - Sistema de Reserva de Assentos
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "assentos.h"

#define L 10 //quantidade de loops pro código exemplo

int b = 3;
pthread_mutex_t mutex;

void *consumidor(){
	while(1){
		consome_log_buffer();
	}
	pthread_exit(NULL);
}

void *thread1 () {
	int tid = 1, i;
	t_Assento assento;
	//visualiza mapa de assentos
	for(i = 0; i < L; i++){
		visualizaAssentos(tid);
		//tenta alocar um assento livre
		alocaAssentoLivre(&assento, tid);
		//visualiza mapa de assentos
		visualizaAssentos(tid);
	}
	printf("\nt1 completa\n");
	pthread_exit(NULL);
}

void *thread2 () {
	int tid = 2, i;
	//visualiza mapa de assentos
	for(i = 0; i < L; i++){
		visualizaAssentos(tid);
		t_Assento assento = pega_assento(rand() % n_assentos); //inicializa com um assento
		//tenta alocar um assento especifico
		alocaAssentoDado(assento, tid);
		//visualiza mapa de assentos
		visualizaAssentos(tid);
		
	}
	printf("\nt2 completa\n");
	pthread_exit(NULL);	
}

void *thread3 () {
	//salva seu identificador unico
	int tid = 3, t, i;
	t_Assento assento;
	//visualiza mapa de assentos
	for(i = 0; i < L; i++){
		visualizaAssentos(tid);
		//tenta alocar um assento livre
		t = alocaAssentoLivre(&assento, tid);
		//visualiza mapa de assentos
		//printf("debug: \n id: %d estado: %d u_id: %d t: %d \n", tid, assento.estado, assento.id_usuario, t);
		visualizaAssentos(tid);
		//libera alocacao
		t = liberaAssento(assento, tid);
		
		//visualiza mapa de assentos
		visualizaAssentos(tid);	
	}
	printf("\nt3 completa\n");
	pthread_exit(NULL);

}

int main(int argc, char *argv[]) {
	int i, *tids;
	pthread_t threads[4];
	if(argc < 3 ){
		printf("Execute %s <log saida> <quantidade de assentos>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	pthread_mutex_init(&mutex, NULL);
	FILE *arq = fopen(argv[1], "w");
	int n_assentos = atoi(argv[2]);
	init(n_assentos, arq);
	
	pthread_create(&threads[0], NULL, consumidor, NULL);
	pthread_create(&threads[1], NULL, thread1, NULL);
	pthread_create(&threads[2], NULL, thread2, NULL);
	pthread_create(&threads[3], NULL, thread3, NULL);
	
	for(i=0; i < n_assentos; i++){
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}
