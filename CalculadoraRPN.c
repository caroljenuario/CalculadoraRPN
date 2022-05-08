#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct no{
    float resultado; //resultado da conta
    struct no *no_anterior; // aponta pro no de baixo
}No;

No* push(No *pilha, float num){
    No *novo_no = malloc(sizeof(No)); // alocar espaço para o novo no
    if(novo_no){
        novo_no->resultado = num;
        novo_no->no_anterior = pilha;
        return novo_no;
    }
    else
        printf("Erro na alocação de memoria.\n");
    return NULL;
}

No* pop(No **pilha){
    No *remover = NULL;
    if(*pilha){
        remover = *pilha;
        *pilha = remover->no_anterior;
    }
    else
        printf("\tPilha vazia\n");
    return remover;
}

float operacao(float a, float b, char operador){
    switch(operador){
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '/':
        return a / b;
        break;
    case '*':
        return a * b;
        break;
    case '|':  
       return pow(a,b);
       break;
    case '&':
      return sqrt (a);
    default:
        return 0.0;
    }
}

float resolver_expressao(char operador[]){
    char *pt;
    float numero;
    No *numero_1, *numero_2, *pilha = NULL;

    pt = strtok(operador, " ");
    while(pt){
        if(pt[0] == '+' || pt[0] == '-' || pt[0] == '/' || pt[0] == '*' || pt[0] == '|' || pt[0] == '&'){
            numero_1 = pop(&pilha);
            numero_2 = pop(&pilha);
            numero = operacao(numero_2->resultado, numero_1->resultado, pt[0]);
            pilha = push(pilha, numero);
            free(numero_1);
            free(numero_2);
        }
        else{
            numero = strtol(pt, NULL, 10);
            pilha = push(pilha, numero);
        }
        pt = strtok(NULL, " ");
    }
    numero_1 = pop(&pilha);
    numero = numero_1->resultado;
    free(numero_1);
    return numero;
}

int main(){

    char exp[50];
    printf("Digite a expressão desejada: \n");
    gets(exp);
    printf("Resultado de %s:\t", exp);
    printf("%f\n", resolver_expressao(exp));

}