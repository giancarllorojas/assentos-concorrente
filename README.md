# Sistema de reserva de assentos

#### Trabalho de computação concorrente - UFRJ 2016.2

Descrição do problema: Um sistema de reserva de assentos consiste em um programa que mantem informações sobre a alocação de assentos em um espaço físico ou em um meio de transporte, permitindo
que usuários remotos possam ver o estado das alocações, solicitar nova alocação ou cancelar uma alocação realizada previamente pelo próprio usuário. Normalmente esse tipo de sistema e executado em um ambiente distribuído com duas aplicações distintas: uma que executa o código que gerencia as estruturas de dados usadas para manter o estado de alocação dos assentos e outra que é executada em maquinas remotas pelos usuários. Em essência, trata-se de uma aplicação concorrente com vários fluxos de execução independentes.

A versão aqui implementada é simplificada e rodará em apenas uma máquina, utilizando várias threads independentes para simular.

Condições da implementação:
- O numero de assentos deve ser passado como parâmetro no início da execução da aplicação.
- Quando um assento e reservado, ele deve guardar um identificador único do usuário que fez a reserva no mapa de assentos.
- Dois ou mais usuários não podem alocar o mesmo assento ao mesmo tempo
- Se um assento já está alocado, ele não pode ser realocado para outro usuário, apenas se esse assento for liberado posteriormente pelo usuário dono da reserva.
- Entre o instante em que um usuário visualiza o mapa de assentos e o instante seguinte em que ele solicita a alocação de um assento, pode ocorrer de outro usuário já ter alocado o assento que previamente (na visualização anterior) estava livre.
