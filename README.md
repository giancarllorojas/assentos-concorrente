# Sistema de reserva de assentos

#### Trabalho de computa��o concorrente - UFRJ 2016.2

Descri��o do problema: Um sistema de reserva de assentos consiste em um programa que mantem informa��es sobre a aloca��o de assentos em um espa�o f�sico ou em um meio de transporte, permitindo
que usu�rios remotos possam ver o estado das aloca��es, solicitar nova aloca��o ou cancelar uma aloca��o realizada previamente pelo pr�prio usu�rio. Normalmente esse tipo de sistema e executado em um ambiente distribu�do com duas aplica��es distintas: uma que executa o c�digo que gerencia as estruturas de dados usadas para manter o estado de aloca��o dos assentos e outra que � e executada em maquinas remotas pelos usu�rios. �
Em ess�ncia, trata-se de uma aplica��o concorrente com v�rios fluxos de execu��o independentes.