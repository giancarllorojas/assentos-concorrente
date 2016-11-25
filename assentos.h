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
* Opera��o c�digo 1: visualizaAssentos
* @descri��o: Visualiza o mapa de assentos 
* @retorno: void
* @log: a opera��o, id da thread e o mapa de assentos
*/
void visualizaAssentos();

/**
* Opera��o c�digo 2: alocaAssentoLivre
* @descri��o: Escolhe de forma aleat�ria um assento livre e aloca para a thread(usu�rio) com
* identificador "id"
* @retorno: O assento � alocado no par�metro "assento", retornando 1 caso tenha sido alocado 
* e 0 se n�o
* @restri��o: Apenas a thread de mesmo identificador id pode realizar essa alocac�o
* @log: 
*/
int alocaAssentoLivre(t_Assento *assento, int id);

/**
* Opera��o c�digo 3: alocaAssentoDado
* @descri��o: Aloca o assento dado para uma thread(usu�rio) de identificador "id"
* @retorno: 1 se o assento foi alocado, 0 se n�o
* @restri��o: Apenas a thread de mesmo identificador id pode realizar essa alocac�o
*/
int alocaAssentoDado(t_Assento assento, int id);

/**
* Opera��o c�digo 4: liberaAssento
* @descri��o: libera/desaloca o assento(assento) dado alocado pelo usuario de identificador "id"
* @retorno: 1 se o assento foi desalocado, 0 se n�o
* @restri��o: Apenas a thread de mesmo identificador id pode realizar essa desalocac�o
*/
int liberaAssento(t_Assento assento, int id);
