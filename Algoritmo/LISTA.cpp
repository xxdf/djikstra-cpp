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

void leTamanho(int *&PT_N);
void dijkstra(char BUSCA, lista *VT, int N, int *&PT_tamDist, int *&PT_dist, char *&p1, char *&p2);

int main (){
	system("Title Algoritimo de Busca em Grafos™");
							//Declaracao de variaveis
	int N, *PT_N, NN;//Quantidade de vertices
	PT_N = &N;
	leTamanho(PT_N);
	NN = N*2;
	char BUSCA,v1[NN] ,v2[NN], *p1, *p2;
	int pnum = 0, *PT_pnum, tamDist = 0, *PT_tamDist, distancia[NN], *PT_dist;
	p1 = &v1[0];
	p2 = &v2[0];
	PT_dist = &distancia[0];
	PT_tamDist = &tamDist;
	PT_pnum = &pnum;
						//Declaraçao de prototipos
	void leitura (lista *&VT, lista *PT, lista *ANT, int &N, int *&PT_tamDist,int *&PT_dist, char *&p1, char *&p2);
	void imprime(lista *VT, lista *PT, lista *ANT, int N);
						//Declaracao de ponteiros
	struct lista *VT,*PT,*ANT;
						//Chamada das funçoes Principais
	leitura(VT, PT, ANT, N, PT_tamDist, PT_dist, p1, p2);
	PT_dist = &distancia[0];
	p1 = &v1[0];
	p2 = &v2[0];
	imprime(VT, PT, ANT, N);
		cout<<"\nInforme o Vertice: ";
		cin>>BUSCA;
	busca_larg(BUSCA, VT, PT, ANT, N);
	//busca(VT, PT, ANT, N, PT_pnum);
	//dijkstra(BUSCA, VT, N, PT_tamDist, PT_dist, p1, p2);
	delete(VT);//Desaloca memoria
	cout<<"\n\nFIM DA EXECUCAO DO PROGRAMA!\n\n"<<endl;
	system("PAUSE");
	return 0;
}
/*  Funcao que realiza a leitura do tamanho de posições a serem criadas (primeira linha)*/
void leTamanho(int *&PT_N){
	ifstream leitura;
	char eber = 'e';
	bool flag = true;
	leitura.open("Entrada Dijkstra.txt");
	if(!leitura.is_open()){
			cout<<"\n\nErro ao tentar abrir o arquivo!\nTalvez o arquivo nao esteja na pasta, Verifique..\n\n";
			system("pause");
			leitura.clear();
	}
	else{
			while(flag){
					int i=0;
					if(eber!='='){
						leitura>>eber;
					}
					else{
						leitura>>*PT_N;
						flag = false;
					}
			}
	}
	leitura.close();
}
/*  Funcao que realiza a leitura do arquivo*/
void leitura (lista *&VT, lista *PT, lista *ANT, int &N, int *&PT_tamDist,int *&PT_dist, char *&p1, char *&p2){
	//Declaraçao de prototipo
	void monta_lista(char v1, char v2, lista *VT, lista *PT, lista *ANT);

	//Declaracao de variaveis
	int i = 0,h = 0,cond = 1,cont = 0, ue=0, it=0;
	char *pont,caracter,v1,v2, *dist, aux[5];
	//char nome[30];
	FILE *arquivo;//Declaraçao de ponteiro p/ o arquivo
	//Alcaçao de memoria
	dist = new char [5];
	pont = new char [5];

	//	cout<<"Informe o nome do arquivo : ";
	//	gets(nome);

	//Abertura do arquivo
	if((arquivo = fopen("Entrada Dijkstra.txt","r")) == NULL){
		cout<<"ERRO NA ABERTURA DO ARQUIVO!!! ";
 		exit(0);
	}

	//Percorre todo o arquivo lendo caracter por caracter
	while((caracter = getc(arquivo))!= EOF){
		//Condicao p/ descartar os caracteres antes do sinal de igual
		if(((caracter == '=') && (cond > 0)) || ((caracter == '\n') && (cond < 0))){
				cond *= -1;
				if(caracter == '=')
				ue += 1;
		}

		else{
			if(cond < 0)//Verifica se o caracter vem depois do sinal de igual
			{
					//Realiza a leitura do numero de vertices
					if(ue < 4){
					if(isdigit(caracter))//Verifica se o caracter eh um numero
					{
						pont[i++] = caracter;

						//Laço p/ ler o numero caso tiver mais de um caracter
						while(isdigit(caracter = getc(arquivo)))
							pont[i++] = caracter;

						if(i > 1)
							fseek(arquivo, -1, 1);

						pont[i] = '\0';
						N = atoi(pont);//Transforma os caracteres em um valor inteiro

						delete(pont);//Desaloca memoria

						VT = new lista[N];//Aloca memoria p/ o vetor de no cabeças
					}
					else//começa a ler os vértices
					{
						//Realiza a leitura do conjunto de vertices
						if((isalpha(caracter)) && (h < N))
						{
							VT[h].vert = caracter;
							VT[h++].prox = NULL;
						}
						else
						{
							//Realiza a leitura dos pares de vertices
							if(isalpha(caracter))//Verifica se o caracter e uma letra
							{
								cont++;
								if(cont == 2)//Condicao p/ ler o par vertices
								{
									v1 = v2;
									v2 = caracter;
									monta_lista(v1, v2, VT, PT, ANT);//Chamada da funcao
									*p1 = v1;
									*p2 = v2;
									p1++;
									p2++;
									cont = 0;
								}
								else
									v2 = caracter;
							}
						}
					}
				}//Termina ue
				else{//se ja tiver achado o 4º sinal de igual começa a ler o vetor de distancia

						int j = 0, p = i, k;
							if(isdigit(caracter))//Verifica se o caracter eh um numero
							{
								dist[i++] = caracter;
								j++;
								//Laço p/ ler o numero caso tiver mais de um caracter
								while(isdigit(caracter = getc(arquivo))){
									dist[i++] = caracter;
									j++;
								}
								for(k = 0; k < j, p != i; k++, p++)
									aux[k] = dist[p];

								if(i > 1)
									fseek(arquivo, -1, 1);
								//dist[i] = '\0';
								*PT_dist = atoi(aux);				//Transforma os caracteres em um valor inteiro
								for(k = 0; k < j; k++){
									aux[k] = NULL;
								}
								//delete(dist);				//Desaloca memoria
								PT_dist++;
								*PT_tamDist = *PT_tamDist+1;
								_flushall();
								it++;
							}
						//}//while 1
					}
				}
			}
		}
		free(dist);
		fclose(arquivo);//Fecha o arquivo
}
/*  Funcao que realiza o algoritmo de Dijkstra*/
void dijkstra(char BUSCA, lista *VT, int N, int *&PT_tamDist,int *&PT_dist, char *&p1, char *&p2){
	int bsc = 0, v1, v2, k;
	bool condA = true;
	int matriz[N][N];
	int estimativa[N];
	char aberto[N], precedente[N];
	for(int i = 0; i < N; i++){//inicializando matriz
		for(int j = 0; j < N; j++){
			if(i==j)
				matriz[i][j] = NULL;
			else
				matriz[i][j] = 0;
		}
	}
	for(int b = 0; b < *PT_tamDist; b++){// preenchendo a matriz de distancia
		for(v1=0; VT[v1].vert!=*p1;v1++);//acha v1
		for(v2=0; VT[v2].vert!=*p2;v2++);//acha v2
		matriz[v1][v2] = *PT_dist;
		matriz[v2][v1] = *PT_dist;
		p1++;
		p2++;
		PT_dist++;
	}
				//Procura o vértice informado pelo usuário
		if(VT[bsc].vert == BUSCA)
			break;
		bsc++;

	for(int i=0; i<N; i++){ //Inicialização das variaveis
		if(i==bsc){
			estimativa[bsc] = 0;
			precedente[bsc] = '-';
		}
		else{
			estimativa[i] = 32767;
			precedente[i] = NULL;
		}
		aberto[i] = 'V';
	}
	while(condA){// Dijkstra
		int menor = 65535, u;
		for(k = 0; k < N; k++){
				if((estimativa[k]<menor) && (aberto[k]=='V')){ // Procura a menor estimativa dentre todas para fazer o algoritmo
						menor = estimativa[k];
						u = k;
				}
		}
		k = u;
		aberto[k]='F';
		for(int j = 0; j<N; j++){// percorre todos os adjacentes a k
				if(j!=k){
					if((aberto[j]=='V')&&(matriz[k][j]>0)){ // se estiver aberto e se for adjacente a k
						menor = estimativa[k]+matriz[k][j];
						if(menor<estimativa[j]){
							estimativa[j] = menor;
							precedente[j] = VT[k].vert;
						}
					}
					_flushall();
				}
		}
		for(int j = 0; j<N; j++){ // Apenas modifica a condição de saída (Se todos os vertices estiverem fechados)
			if(aberto[j]=='V'){
				condA = true;
				break;
			}
			else
				condA = false;
		}
	}
	// mostrando resultado
	cout<<"\nAlgoritmo de Djikstra atraves do vetor "<<VT[bsc].vert<<" informado!..."<<endl;
	cout<<"\nVertices  :";
	for(int j = 0; j<N; j++){
		cout<<"\t"<<VT[j].vert;
	}
	cout<<"\nEstimativa:";
	for(int j = 0; j<N; j++){
		cout<<"\t"<<estimativa[j];
	}
	cout<<"\nPrecedente:";
	for(int j = 0; j<N; j++){
				cout<<"\t"<<precedente[j];
	}
	cout<<"\nAberto	:";
	for(int j = 0; j<N; j++){
		cout<<"\t"<<aberto[j];
	}
}
/*  Funçao para montar a lista*/
void monta_lista(char v1, char v2, lista *VT, lista *PT, lista *ANT){
	//Declaracao de variaveis
	int i, cont = 0, cond = 0;
	char aux;

	do{
		//Percorre o vetor de vetices ate encontrar o vertice correspondente
		for(i = 0; VT[i].vert != v1; i++);

		//Condicao p/ montar a lista
		if(VT[i].prox != NULL){
			ANT = VT[i].prox;
			//Percorre a lista ate o fim ou ate encontar um vertice repetido
			while((ANT->prox != NULL) && (cond == 0))
			{
				ANT = ANT->prox;

				if(ANT->vert == v2)
					cond = 1;

			}
			//Se nao houver vertice repetido, entao um novo no e inserido na lista
			if((ANT->vert != v2) && (cond == 0))
			{
				PT = new lista; //Alocando memoria p/ os nos
				PT->prox = ANT->prox;
				ANT->prox = PT;
				PT->vert = v2;
			}
		}
		else{
			PT = new lista; //Alocando memoria p/ os nos
			PT->prox = VT[i].prox;
			VT[i].prox = PT;
			PT->vert = v2;
		}

	//Inverte os vetices
		aux = v1;
		v1 = v2;
		v2 = aux;
	 //Realiza a simetria repetindo a mesma operacao caso os vertices sejam diferentes
	}while((++cont < 2) && ( v1 != v2) && (cond == 0));
}
/*  Funçao para imprimir a lista resultante*/
void imprime(lista *VT, lista *PT, lista *ANT, int N){
	//Declaracao de variavel indice
	int i;

	cout<<"\nLISTA DE ADJACENCIA\n\n";

	for(i = 0;i < N; i++)//Laço p/ percorrer todo o vetor de vertices
	{
		cout<<i<<") "<<VT[i].vert<<" -";
		PT = VT[i].prox;

		while(PT != NULL)//Percorre a lista ate o final
		{
			cout<<"  "<<PT->vert<<"  ";
	//		ANT = PT;
			PT = PT->prox;
	//		delete(ANT);//Desaloca memoria
		}
		cout<<endl;
	}
}

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
