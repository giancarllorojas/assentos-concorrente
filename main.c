#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct t_Assento{
	bool ocupado;
}t_Assento;

/**
* Opera��o c�digo 1: visualizaAssentos
* @descri��o: Visualiza o mapa de assentos 
* @retorno: void
* @log: a opera��o, id da thread e o mapa de assentos
*/
void visualizaAssentos(){
	printf("");
}

/**
* Opera��o c�digo 2: alocaAssentoLivre
* @descri��o: Escolhe de forma aleat�ria um assento livre e aloca para a thread(usu�rio) com
* identificador "id"
* @retorno: O assento � alocado no par�metro "assento", retornando 1 caso tenha sido alocado 
* e 0 se n�o
* @restri��o: Apenas a thread de mesmo identificador id pode realizar essa alocac�o
* @log: 
*/
int alocaAssentoLivre(t_Assento *assento, int id){
	return 0;
}

/**
* Opera��o c�digo 3: alocaAssentoDado
* @descri��o: Aloca o assento dado para uma thread(usu�rio) de identificador "id"
* @retorno: 1 se o assento foi alocado, 0 se n�o
* @restri��o: Apenas a thread de mesmo identificador id pode realizar essa alocac�o
*/
int alocaAssentoDado(t_Assento assento, int id){
	return 0;
}


int main(int argc, char *argv[]) {
	printf("Hello Assentos");
	return 0;
}
