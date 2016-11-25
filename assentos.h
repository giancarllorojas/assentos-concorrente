#define LIVRE 0
#define RESERVADO 1

/* Estrutura de um assento */
typedef struct t_Assento{
	bool ocupado;
	int id_usuario;
}t_Assento;

/* Inicializa um Assento */
void assento_init(t_Assento *end);

/**
* Operação código 1: visualizaAssentos
* @descrição: Visualiza o mapa de assentos 
* @retorno: void
* @log: a operação, id da thread e o mapa de assentos
*/
void visualizaAssentos();

/**
* Operação código 2: alocaAssentoLivre
* @descrição: Escolhe de forma aleatória um assento livre e aloca para a thread(usuário) com
* identificador "id"
* @retorno: O assento é alocado no parâmetro "assento", retornando 1 caso tenha sido alocado 
* e 0 se não
* @restrição: Apenas a thread de mesmo identificador id pode realizar essa alocacão
* @log: 
*/
int alocaAssentoLivre(t_Assento *assento, int id);

/**
* Operação código 3: alocaAssentoDado
* @descrição: Aloca o assento dado para uma thread(usuário) de identificador "id"
* @retorno: 1 se o assento foi alocado, 0 se não
* @restrição: Apenas a thread de mesmo identificador id pode realizar essa alocacão
*/
int alocaAssentoDado(t_Assento assento, int id);

/**
* Operação código 4: liberaAssento
* @descrição: libera/desaloca o assento(assento) dado alocado pelo usuario de identificador "id"
* @retorno: 1 se o assento foi desalocado, 0 se não
* @restrição: Apenas a thread de mesmo identificador id pode realizar essa desalocacão
*/
int liberaAssento(t_Assento assento, int id);
