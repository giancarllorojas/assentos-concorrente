#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define LIVRE 0
#define RESERVADO 1
#define TAM_BUFFER 10

typedef struct t_Assento{
	int estado;
	int id_usuario;
	int posicao;
}t_Assento;

typedef struct t_Log{
	int operacao;
	int id_usuario;
	int assento;
	int *mapa;
}t_Log;

/* Variáveis globais */
t_Log buffer[TAM_BUFFER];
sem_t slotCheio, slotVazio, mutex, aloca;
t_Assento *mapa;
int n_assentos, in = 0, out = 0;
FILE *arq_saida;
/* ----------------------------- */

/*
* Inicializa as variaveis para o sistema funcionar:
* - Mapa de assentos com todos assentos livres
* - Inicializa os semaforos
* - Guarda a quantidade de assentos em uma variavel global
*/
void init(int qtd, FILE* arq){
	int i;
	mapa = (t_Assento *)malloc(sizeof(t_Assento)*qtd);
	for(i=0; i < qtd; i++){
		mapa[i].id_usuario = LIVRE;
		mapa[i].estado = LIVRE;
		mapa[i].posicao = i;
	}
	n_assentos = qtd;
	arq_saida = arq;
	sem_init(&slotCheio, 0, 0);
	sem_init(&slotVazio, 0, qtd);
	sem_init(&mutex, 0, 1);
	sem_init(&aloca, 0, 1);
}

/**
* Retorna uma cópia simples do estado atual do mapa
*/
int *clone_mapa(){
	int *m = (int *)malloc(sizeof(int)*n_assentos), i;
	for(i = 0; i < n_assentos; i++){
		m[i] = mapa[i].id_usuario;
	}
	return m;
}

/*
* Função para preencher uma estrutura de log
*/
void log_init(t_Log *log, int operacao, int id, int assento, int *m){
	log->operacao = operacao;
	log->id_usuario = id;
	log->assento = assento;
	log->mapa = m;
}

/*
* Função que pega uma estrutura t_Log e escreve no arquivo conforme as especificações
*/
void log_arq(t_Log *log, FILE *arq_saida){
	int i;
	
	fprintf(arq_saida, "%d,", log->operacao);
	fprintf(arq_saida, "%d,", log->id_usuario);
	//caso exista um assento selecionado
	if(log->assento != -1) fprintf(arq_saida, "%d,", log->assento);
	fprintf(arq_saida, "[");
	for(i=0; i < n_assentos; i++){
		fprintf(arq_saida, "%d", log->mapa[i]);
		if(i != n_assentos -1){
			fprintf(arq_saida, ",");
		}
	}
	fprintf(arq_saida, "]\n");
}

void log_destroy(t_Log *log){
	free(log);
}

/* Insere um log no buffer */
void insere_log_buffer(t_Log log){
	sem_wait(&slotVazio);
	sem_wait(&mutex);
	buffer[in] = log;
	in = (in + 1) % TAM_BUFFER;
	sem_post(&mutex);
	sem_post(&slotCheio);
}

/*
* Retira um log do buffer e o consome, imprimindo o resultado no stdout e no arquivo de saida
*/
void consome_log_buffer(){
	t_Log log;
	sem_wait(&slotCheio);
	log = buffer[out];
	log_arq(&log, arq_saida);
	log_arq(&log, stdout);
	log_destroy(&log);
	out = (out + 1) % TAM_BUFFER;
	sem_post(&slotVazio);
}

/**
* Operação código 1: visualizaAssentos
* @descrição: Visualiza o mapa de assentos 
* @retorno: void
* @log: a operação(1), id da thread e o mapa de assentos
*/
void visualizaAssentos(int id){
	t_Log log;
	int *m = clone_mapa(m);
	log_init(&log, 1, id, -1, m);
	insere_log_buffer(log);
}

/**
* Operação código 2: alocaAssentoLivre
* @descrição: Escolhe de forma aleatória um assento livre e aloca para a thread(usuário) com
* identificador "id"
* @retorno: O assento é alocado no parâmetro "assento", retornando 1 caso tenha sido alocado 
* e 0 se não
* @restrição: Apenas a thread de mesmo identificador id pode realizar essa alocacão
* @log: a operação, id da thread, assento selecionado e o mapa de assentos imediatamente apos a alocaço
*/
int alocaAssentoLivre(t_Assento *assento, int id){
	t_Log log;
	int i;
	int *m;
	sem_wait(&aloca);
	for(i = 0; i < n_assentos; i++){
		if(!mapa[i].estado){
			mapa[i].id_usuario = id;
			mapa[i].estado = RESERVADO;
			*assento = mapa[i];
			m = clone_mapa();
			sem_post(&aloca);
			log_init(&log, 2, id, assento->posicao, m);
			insere_log_buffer(log);
			return 1;
		}
	}
	m = clone_mapa();
	sem_post(&aloca);
	log_init(&log, 2, id, -1, m);
	insere_log_buffer(log);
	
	return 0;
}

/**
* Operação código 3: alocaAssentoDado
* @descrição: Aloca o assento dado para uma thread(usuário) de identificador "id"
* @retorno: 1 se o assento foi alocado, 0 se não
* @restrição: Apenas a thread de mesmo identificador id pode realizar essa alocacão
* @log: a operação, id da thread, assento selecionado e o mapa de assentos imediatamente apos a alocaço
*/
int alocaAssentoDado(t_Assento assento, int id){
	t_Log log;
	int *m;
	sem_wait(&aloca);
	if(!assento.estado){
		assento.id_usuario = id;
		assento.estado = RESERVADO;
		m = clone_mapa();
		sem_post(&aloca);
		log_init(&log, 3, id, assento.posicao, m);
		insere_log_buffer(log);
		
		return 1;
	}else{
		m = clone_mapa();
		sem_post(&aloca);
		log_init(&log, 3, id, -1, m);
		insere_log_buffer(log);
		return 0;
	}
}

/**
* Operação código 4: liberaAssento
* @descrição: libera/desaloca o assento(assento) dado alocado pelo usuario de identificador "id"
* @retorno: 1 se o assento foi desalocado, 0 se não
* @restrição: Apenas a thread de mesmo identificador id pode realizar essa desalocacão
* @log: a operação, id da thread, assento selecionado e o mapa de assentos imediatamente apos a alocaço
*/
int liberaAssento(t_Assento assento, int id){
	int *m,i;
	t_Log log;
	//printf("debug: \n id: %d estado: %d u_id: %d\n", id, assento.estado, assento.id_usuario);
	if(assento.id_usuario == id && assento.estado){
		mapa[assento.posicao].id_usuario = LIVRE;
		mapa[assento.posicao].estado = LIVRE;
		m = clone_mapa();
		log_init(&log, 4, id, assento.posicao, m);
		insere_log_buffer(log);
		return 1;
	}else{
		m = clone_mapa();
		log_init(&log, 4, id, assento.posicao, m);
		insere_log_buffer(log);
		return 0;
	}
}
