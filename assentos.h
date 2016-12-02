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

t_Assento *mapa; /* t_Assentos: estrutura para guardar o mapa de assentos */
int n_assentos;

void init(int qtd, FILE* arq);

void insere_log_buffer(t_Log log);
void consome_log_buffer();

void visualizaAssentos();
int alocaAssentoLivre(t_Assento *assento, int id);
int alocaAssentoDado(t_Assento assento, int id);
int liberaAssento(t_Assento assento, int id);
