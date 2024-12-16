# Eliminação de Gauss

## Integrantes
- Isaack Anthony Cordeiro Arcanjo
- Kevin Depolli
- Pedro Nunes Dutra

## Trabalho

Este trabalho contempla o assunto Sistemas Lineares da disciplina Algoritmos Numéricos. O trabalho  é
em grupo de até 3 pessoas e deve ser entregue pelo Google Sala de Aula da disciplina. O grupo deve
implementar o método de Eliminação de Gauss para a solução de Sistemas Lineares apresentado na disciplina.

## Entrada de dados
O trabalho deve receber, pela linha de comando, o nome do arquivo que contém os Sistemas Lineares a serem
resolvidos. O arquivo de entrada deve conter o Sistema Lineares e as informa ̧c ̃oes auxiliares necess ́arias para
resolvê-los, a saber:

- Dimensão (N) da matriz A quadrada dos Sistemas;
- Os N × N valores da matriz A quadrada dos Sistemas;
- Os 1 × N valores do vetor B do sistema;

## Dados de Saída
Ao final da execução, o trabalho deve informar o valor do vetor X obtido.

## Execução
- Para executar, é necessário passar como parâmetro o nome do arquivo no momento de compilar o programa. 
```bash
  gcc -o main main.c
```
```bash
  ./main sistema10x10.dat
```