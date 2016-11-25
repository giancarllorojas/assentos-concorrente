# Sistema de reserva de assentos

#### Trabalho de computa��o concorrente - UFRJ 2016.2

Descri��o do problema: Um sistema de reserva de assentos consiste em um programa que mantem informa��es sobre a aloca��o de assentos em um espa�o f�sico ou em um meio de transporte, permitindo
que usu�rios remotos possam ver o estado das aloca��es, solicitar nova aloca��o ou cancelar uma aloca��o realizada previamente pelo pr�prio usu�rio. Normalmente esse tipo de sistema e executado em um ambiente distribu�do com duas aplica��es distintas: uma que executa o c�digo que gerencia as estruturas de dados usadas para manter o estado de aloca��o dos assentos e outra que � executada em maquinas remotas pelos usu�rios. Em ess�ncia, trata-se de uma aplica��o concorrente com v�rios fluxos de execu��o independentes.

A vers�o aqui implementada � simplificada e rodar� em apenas uma m�quina, utilizando v�rias threads independentes para simular.

Condi��es da implementa��o:
- O numero de assentos deve ser passado como par�metro no in�cio da execu��o da aplica��o.
- Quando um assento e reservado, ele deve guardar um identificador �nico do usu�rio que fez a reserva no mapa de assentos.
- Dois ou mais usu�rios n�o podem alocar o mesmo assento ao mesmo tempo
- Se um assento j� est� alocado, ele n�o pode ser realocado para outro usu�rio, apenas se esse assento for liberado posteriormente pelo usu�rio dono da reserva.
- Entre o instante em que um usu�rio visualiza o mapa de assentos e o instante seguinte em que ele solicita a aloca��o de um assento, pode ocorrer de outro usu�rio j� ter alocado o assento que previamente (na visualiza��o anterior) estava livre.
