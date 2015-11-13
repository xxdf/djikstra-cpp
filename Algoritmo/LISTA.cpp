//Bibliotecas utilizadas
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <fstream>
using namespace std;

//Declaraçao do registro
struct lista { struct lista *prox;
	char vert;
	char cor;int dist;int prec; int posicao, ordem;
};
typedef struct fila{
	int valor;
	struct fila *prox;
}Fila;

//Declaração das funções da Fila
Fila *nova_fila();
int fila_vazia(Fila *f);
Fila *push(Fila *u, int valor);
Fila* pop(Fila* f);

# INSERIR CÓDIGO AQUI

/*  Inicia uma fila*/
Fila *nova_fila(){
		return NULL;
	}
/*  Verifica se uma fila está vazia*/
int fila_vazia(Fila *f){
	if(f==NULL)
	return 1;//fila vazia
	else
	return 0;//fila nao vazia
}
/*  Insere elementos na fila*/
Fila *push(Fila *u, int valor){

	Fila *temp = u;
	Fila *novo = (Fila*)malloc(sizeof(Fila));
	novo -> valor = valor;
	novo -> prox = NULL;

	if(fila_vazia(u))
	return novo;

	while(temp -> prox != NULL){
	temp = temp -> prox;
	}

	temp->prox = novo;
	return u;
}
/*  Remover os elementos da fila*/
Fila* pop(Fila* f){
 	if(fila_vazia(f))
		return NULL;
	Fila *temp = f -> prox;
	free(f);
	return temp;
}
