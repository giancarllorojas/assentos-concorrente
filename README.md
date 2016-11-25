# Sistema de reserva de assentos

#### Trabalho de computação concorrente - UFRJ 2016.2

Descrição do problema: Um sistema de reserva de assentos consiste em um programa que mantem informações sobre a alocação de assentos em um espaço físico ou em um meio de transporte, permitindo
que usuários remotos possam ver o estado das alocações, solicitar nova alocação ou cancelar uma alocação realizada previamente pelo próprio usuário. Normalmente esse tipo de sistema e executado em um ambiente distribuído com duas aplicações distintas: uma que executa o código que gerencia as estruturas de dados usadas para manter o estado de alocação dos assentos e outra que ˜ e executada em maquinas remotas pelos usuários. ´
Em essência, trata-se de uma aplicação concorrente com vários fluxos de execução independentes.