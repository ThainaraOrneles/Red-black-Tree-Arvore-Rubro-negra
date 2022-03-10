//                                   ==============================================
//									 | UNIVERSIDADE FEDERAL DO MATO GROSSO DO SUL |
//									 |		TRABALHO DE ÁRVORE RUBRO-NEGRA        |
//									 |			THAINARA ORNELES MATOS            |
//									 |			   PROF YORAH BOSSE               |
//									 ==============================================
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#define RED 1
#define BLACK 0
//FUNÇÃO DO TIPO STRUCT CRIA A ESTRUTURA DA ÁRVORE RUBRO NEGRA
typedef struct sRN{
	int valor;
	int cor;
	struct sRN *dir;
	struct sRN *esq;
	struct sRN *pai;
}sRN;
//FUNÇÃO QUE RETORNA A LETRA P QUANDO O NÓ QUE APONTA PARA COR FOR IGUAL A 0 
//E V QUANDO O NÓ QUE APONTA PARA COR FOR IGUAL A 1
char cor(sRN *R){
	if(R->cor == 0){
		return 'P';
	}else{
		return 'V';
	}
}
//	FUNÇÃO QUE USA RECURSIVIDADE PARA PERCORRER TODA A ÁRVORE E CONTAR TODAS AS CORES
int conta_cor(sRN *R, int *V, int *P){	
	if(R == NULL)	
		return 0;
	else{	
		if(R->cor == 0)
			*P=*P+1;
		else
			if(R->cor == 1)
				*V=*V+1;											
		conta_cor(R->esq,V,P);
		conta_cor(R->dir,V,P);						
	}		
}
//FUNÇÃO QUE PERCORRE A ÁRVORE ATÉ ENCOTRAR O NÓ DE MAIOR VALOR
sRN* maximo(sRN *R){
	if(vazia(R) )
          return 0;   
     else   
          if(vazia(R->dir) )   
              return R;   
          else  
              return maximo(R->dir);  
}
//FUNÇÃO QUE PERCORRE A ÁRVORE ATÉ ENCOTRAR O NÓ DE MENOR VALOR
sRN* minimo(sRN *R){
	if(vazia(R) )
          return 0;   
     else   
          if(vazia(R->esq) )   
              return R;   
          else  
              return minimo(R->esq);  
}
//FUNÇÃO QUE IMPRIMI A ÁRVORE EM ORDEM
void mostra_em_ordem(sRN *R){
    if (R != NULL){
        mostra_em_ordem(R->esq);
        printf("(%d %c) ",R->valor,cor(R));
        mostra_em_ordem(R->dir);
	}
}
//FUNÇÃO QUE IMPRIMI A ÁRVORE POS ORDEM
void mostra_pos_ordem(sRN *R){
    if (R != NULL){
        mostra_pos_ordem(R->esq);
        mostra_pos_ordem(R->dir);
        printf("(%d %c) ",R->valor,cor(R));
    }
}
//FUNÇÃO QUE IMPRIMI A ÁRVORE PRÉ ORDEM
void mostra_pre_ordem(sRN *R){
    if (R != NULL){
        printf("(%d %c) ",R->valor,cor(R));
        mostra_pre_ordem(R->esq);
        mostra_pre_ordem(R->dir);
    }
}
//FUNÇÃO QUE VERIFICA SE A ÁRVORE ESTA VAZIA OU NÃO
int vazia(sRN *R){
	if(R == NULL){
		return 1;
	}else{
		return 0;
	}
}
//FUNÇÃO QUE FAZ A ROTAÇÃO EM CIMA DO NÓ DESBALANCEADO PARA A DIREITA
sRN *RSD(sRN *R, sRN *aux){
	sRN *y;
	y = aux->esq;
	aux->esq = y->dir;
	if(y->dir != NULL){
		y->dir->pai = aux;
	}
	y->pai = aux->pai;
	if(y->pai == NULL)
		R = y;
	else{
		if(aux == aux->pai->dir)
			aux->pai->dir = y;
		else
			aux->pai->esq = y;			
	}
	y->dir = aux;
	aux->pai = y;
	return R;
}
//FUNÇÃO QUE FAZ A ROTAÇÃO EM CIMA DO NÓ DESBALANCEADO PARA A ESQUERDA
sRN* RSE(sRN *R, sRN *aux){
	sRN *y;
	y = aux->dir;
	aux->dir = y->esq;
	if(y->esq != NULL)
		y->esq->pai = aux;
		
	y->pai = aux->pai;
	if(y->pai == NULL)
		R = y;
	else{
		if(aux == aux->pai->esq)
			aux->pai->esq = y;
		else
			aux->pai->dir = y;
	}
	y->esq = aux;
	aux->pai = y;
	return R;
}
//FUNÇÃO QUE LISTA NAS ORDENS (EM ORDEM, POS ORDEM E PRE ORDEM)
void Listar(sRN *R){
	if(vazia(R)){
		printf("\nLISTA VAZIA!\n");
		system("pause");
	}else{
		printf("\nEm ordem: ");
		mostra_em_ordem(R);
		printf("\nPos ordem: ");
		mostra_pos_ordem(R);
		printf("\nPre ordem: ");
		mostra_pre_ordem(R);
		printf("\n\n");
		system("pause");
	}
}
//FUNÇÃO QUE REALIZA AS ROTAÇÕES NECESSARIA NA HORA DE EXCLUIR O NÓ
sRN* Definir_exclusao(sRN *R, sRN *aux){ 
	sRN *w;
	while(aux != R && aux->cor == BLACK){
		if(aux == aux->pai->esq){
			w = aux->pai->dir;
			//CASO 2.1A
			if(w->cor == RED){
				w->cor = BLACK;
				aux->pai->cor = RED;
				RSE(R,aux->pai);
				w = aux->pai->dir;				
			}
			// CASO 2.1B
			if(w->esq->cor == BLACK && w->dir->cor == BLACK){
				w->cor = RED;
				aux->pai->cor = BLACK;
				aux = aux->pai;
			}else{
				//CASO 2.1C
				if(w->dir->cor == BLACK){
					w->cor = RED;
					w->esq->cor = BLACK;
					RSD(R,w);
					w = aux->pai->dir;
				}
				// CASO 2.1D
				w->cor = aux->pai->cor;
				aux->pai->cor = BLACK;
				aux->dir->cor = BLACK;
				RSE(R,aux->pai);
				aux = R;
			}
		}else{
			w = aux->pai->esq;
			// CASO 2.1C
			if(w->cor == RED){
				w->cor = BLACK;
				aux->pai->cor = BLACK;
				RSD(R,aux->pai);
				w = aux->pai->esq;
			}
			// CASO 2.1B
			if(w->esq->cor == BLACK && w->dir->cor == BLACK){
				w->cor = RED;
				aux->pai->cor = BLACK;
				aux = aux->pai;
			}else{
				//CASO 2.1C
				if(w->esq->cor == BLACK){
					w->cor = RED;
					w->dir->cor = BLACK;
					RSE(R,w);
					w = aux->pai->esq;
				}
				// CASO 2.1D
				w->cor = aux->pai->cor;
				aux->pai->cor = BLACK;
				w->esq->cor = BLACK;
				RSD(R,aux->pai);
				aux = R;
			}
		}
		aux->cor = BLACK;
	}
	return R;
}
//FUNÇÃO QUE EXCLUI O NÓ 
sRN *Excluir(sRN *R, sRN *dado){
	sRN *y,*x,*aux;
	//SE O DADO A SER APAGADO FOR DIFERENTE DE NULL ENTAO Y RECEBE O MAIOR VALOR Á ESQUERDA
	if(dado->esq != NULL){
		y = maximo(dado->esq);
	}else{
		//SE O DADO A SER APAGADO FOR DIFERENTE DE NULL ENTAO Y RECEBE O MENOR VALOR Á DIREITA
		if(dado->dir != NULL){
			y = minimo(dado->dir);
		}else{
			y = dado;
		}
	}
	
	// SE Y À ESQUERDA FOR DIFERENTE DE NULL X RECEBE Y À ESQUERDA
	if(y->esq != NULL){
		x = y->esq;
	}else{
		//SE NÃO, X RECEBE Y À DIREITA
		x = y->dir;
	}
//SE Y QUE APONTA PARA O PAI FOR IGUAL A NULL ENTAO RAIZ RECEBE X
	if(y->pai == NULL){
		R = x;
	}else{
		//SE VALOR DE Y FOR IGUAL O VALOR DE Y QUE APONTA PARA O PAI QUE APONTA PARA À ESQUERDA , RECEBE X
		if(y == y->pai->esq){
			y->pai->esq = x;
		}//SE NÃO, Y QUE APONTA PARA O PAI À DIREITA RECEBE O X
		else
			y->pai->dir = x;
	}
	//SE Y FOR DIFERENTE DO DADO A SER APAGADO ENTAO O ESPAÇO A SER APAGADO RECEBE O VALOR DE Y 
		if(y != dado){
		dado->valor = y->valor;
	}
	//SE A COR DO Y FOR PRETO CHAMA-SE A FUNÇÃO PARA FAZER AS ALTERAÇÕES NECESSARIAS
	if(y->cor == BLACK){		
		R = Definir_exclusao(R,x);
	}
		//Y É APAGADO
	free(y);
	//RETORNO DA RAIZ
	return R;
	
}
//FUNÇÃO QUE EXCLUI A ÁRVORE TODA
sRN *Excluir_Tudo(sRN *R){	
//RAIZ FOR DIFERENTE DE NULL CHAMA-SE A RECURSIVIDADE PARA ENCONTRAR TODOS OS NÓS DEPOIS RECEBE NULL E É APAGADO COM FREE
	if (R != NULL){
       	Excluir_Tudo(R->esq);
        Excluir_Tudo(R->dir); 		
		R = NULL;
		free(R);
	}	
	return R;
}

//FUNÇÃO QUE FAZ O BALANCEAMENTO DA ÁRVORE
sRN* Verifica_Balanceamento(sRN *aux, sRN *R){
sRN *y;
	//ENQUANTO O AUX FOR DIFERENTE DA RAIZ E O PAI FOR VERMELHO ELE IRÁ REPITIR PARA DEIXAR BALANCEADO
	while(aux != R && aux->pai->cor == RED){
		if(aux->pai == aux->pai->pai->dir)
			y = aux->pai->pai->esq;
		else
			y = aux->pai->pai->dir;
		//SE O TIO FOR PRETO
		if(y == NULL || y->cor == BLACK){
			//CASO 2.2A  TIO À DIREITA NOVO NÓ À ESQUERDA	
			if(aux->pai->cor == RED && aux->pai == aux->pai->pai->esq && aux == aux->pai->esq){
				aux->pai->cor = BLACK;
				aux->pai->pai->cor = RED;
				//CHAMA A FUNÇÃO QUE FAZ A ROTAÇÃO À DIREITA				
				R = RSD(R,aux->pai->pai);			
			}else{
				//CASO 2.2C TIO À DIREITA NOVO NÓ À DIREITA
				if(aux->pai->cor == RED && aux->pai == aux->pai->pai->esq && aux == aux->pai->dir){
					aux->cor = BLACK;
					aux->pai->pai->cor = RED;
					//CHAMA A FUNÇÃO QUE FAZ A ROTAÇÃO À ESQUERDA
					R = RSE(R,aux->pai);
					//CHAMA A FUNÇÃO QUE FAZ A ROTAÇÃO À DIREITA
					R = RSD(R,aux->pai);
					//AS DUAS CHAMADAS ACIMA REALIZA A ROTAÇÃO DUPLA
				}else{
					//CASO 2.2A TIO À DIREITA NOVO NÓ À ESQUERDA 
					if(aux->pai->cor == RED && aux->pai == aux->pai->pai->dir && aux == aux->pai->dir){
						aux->pai->cor = BLACK;
						aux->pai->pai->cor = RED;				
						R = RSE(R,aux->pai->pai);
					}else{
						//CASO 2.2D TIO À ESQUERDA NOVO NÓ À ESQUERDA 
						if(aux->pai->cor == RED && aux->pai == aux->pai->pai->dir && aux == aux->pai->esq){
							aux->cor = BLACK;
							aux->pai->pai->cor = RED;
							R = RSD(R,aux->pai);
							R = RSE(R,aux->pai);
						}
					}
				}
			}
	
		}else{	
			//CASO 2.1	PAI VERMELHO TIO VERMELHO
			if(aux->pai->cor == RED && y->cor == RED ){
				aux->pai->cor = BLACK;
				y->cor = BLACK;
				aux->pai->pai->cor = RED;
				//AVÔ PASSA A SER O NOVO NÓ
				aux = aux->pai->pai;
			}		
		}
	}
	R->cor = BLACK;
return R;	
}
//FUNÇÃO QUE FAZ A INSERÇÃO NA ÁRVORE
sRN* inserir(sRN *R, int n){
	sRN *aux = (sRN*) malloc (sizeof(sRN));
	aux->valor = n;
	aux->dir = NULL;
	aux->esq = NULL;
	aux->pai = NULL;
	if(R == NULL){
		aux->cor = BLACK;
		R = aux;
	}else{
		sRN *x, *y;
		y = NULL;
		x = R;
		while(x != NULL){
			y = x;
			if(aux->valor < x->valor)
				x = x->esq;
			else
				x = x->dir;
		}
		aux->pai = y;
		if(aux->valor > y->valor)
			y->dir = aux;
		else
			y->esq = aux;
		aux->cor = RED;
	}
  R = Verifica_Balanceamento(aux,R);

return R;
}
//FUNÇAO QUE UTILIZA OS DADOS INFORMADOS PELO USUÁRIO PARA FAZER A INSERÇÃO NA ÁRVORE
sRN* inserir_num(sRN *R){
	int n;
	char resp;
	do{
		system("cls");
		printf("\nDigite um número: ");
		scanf("%d",&n);
		R = inserir(R,n);
		printf("\nDeseja inserir novamente?\n[S] sim [N] não: ");
		resp = toupper(getch());
	}while(resp == 'S');
	
return R;
}
//FUNÇÃO QUE FAZ A BUSCA NA ÁRVORE CONFORME O SOLICITADO PELO USUÁRIO
sRN *Busca(sRN *R, int Num){
	while(R != NULL && R->valor !=Num){
		if(Num < R->valor){
			R = R->esq;
		}else{
			R = R->dir;
		}
	}
	return R;
}
//FUNÇÃO QUE FAZ A ALTERAÇÃO DO NÓ FAZENDO PRIMEIRO A EXCLUSÃO  E DEPOIS A INSERÇÃO 
sRN* alterar(sRN *R){
	if(vazia(R)){
		printf("\n\nVazia\n\n");
		system("pause");
	}else{
		int n;
	sRN *busc;
	char resp;
	do{
		system("cls");
		printf("\nDigite o numero a ser apagado: \n");
		scanf("%d",&n);
		busc = Busca(R,n);
		if(busc == NULL){
			printf("Numero não encotrado!\nDeseja procurar mais uma vez?  \n[S]sim [N]não\n"); 
		}else{
			R = Excluir(R,busc);
			system("cls");
			printf("\nDigite o numero a ser inserido\n");
			scanf("%d",&n);
			R = inserir(R,n);
			system("cls");
			printf("Deseja fazer mais uma alteração?\n[S] sim [N] não: ");
		}
		resp = toupper(getch());
	}while(resp == 'S');	
		
	}
	return R;
}
//FUNÇÃO MENU QUE ULTILIZA OS DADOS INFORMADOS PELO USUÁRIO 
sRN* apagar(sRN *R){
	
	int n;
	sRN *busc;
	char resp;
	do{
		system("cls");
		printf("\nDigite o numero a ser apagado: \n");
		scanf("%d",&n);
		busc = Busca(R,n);
		if(busc == NULL){
			printf("Numero não encotrado!\nDeseja procurar mais uma vez?  [S]sim [N]não\n"); 
		}else{
			R = Excluir(R,busc);
			printf("Apagado com sucesso\n");
			printf("\nDeseja apagar novamente?\n");
		}
		resp = toupper(getch());
	}while(resp == 'S');
return R;	
}
//FUNÇÃO MENU QUE ULTILIZA OS DADOS INFORMADOS PELO USUÁRIO PARA FAZER A BUSCA PELA ÁRVORE
void Pesquisar(sRN *R){
	char resp;
	int Num;
	sRN *aux;
	if(vazia(R)){
		printf("\nLista vazia\n");
		system("pause");
	}else{
		do{
			system("cls");
			printf("\nDigite o número a ser pesquisado: ");
			scanf("%d",&Num);
			aux = Busca(R,Num);
			if(aux == NULL){
				printf("Numero (%d) nao encontrado!\n",Num);
				system("pause");
			}else{
				system("cls");
				printf("Numero (%d) encontrado!",Num);
				printf("\nVocê Deseja \n[E] Exclui-lo\n[A] Altera-lo \nou precione qualquer tecla para continuar\n");
				resp = toupper(getch());
				switch(resp){
					case 'E':{					
						R = Excluir(R,aux);
					}break;
					case 'A' :{
						R = alterar(R);
					}break;
				}
			}
			system("cls");
			printf("\nDeseja pesquisar outro número [S] sim [N] não: ");
			resp = toupper(getch());	
	}while(resp == 'S');
	}
}
// FUNÇÃO MENU
void menu(sRN *R){
	setlocale (LC_ALL,"Portuguese");
		
		char l;
	do{
		system("cls");
		printf("\n|=============================|");
		printf("\n|[I] Inserir                  |");
		printf("\n|[L] Listar                   |");
		printf("\n|[C] Total de nós de cada cor |");
		printf("\n|[P] Pesquisar                |");
		printf("\n|[E] Excluir                  |");
		printf("\n|[T] Excluir tudo             |");
		printf("\n|[A] Alterar                  |");
		printf("\n|[S] Sair                     |");
		printf("\n|=============================|\n");		
		l = toupper(getch());
		switch(l){
			case 'I': {	
				R = inserir_num(R);		
			}break;			
			case 'L': {
				Listar(R);
			}break;
			case 'C': {
				int V=0, P=0;
				if(vazia(R)){
					printf("\n\nVazia!!!\n");
					system("pause");
				}else{
					conta_cor(R,&V,&P);
					printf("\nVermelho:%d\nPreto:%d\n\n",V,P);
					system("pause");	
				}
			}break;
			case 'P': {
				Pesquisar(R);
			}break;			
		  	case 'E':{
			  	apagar(R);				
			}break;			
			case 'T':{		
				R = Excluir_Tudo(R);
				printf("Apagado com sucesso\n");
				system("pause");		
			}break;			
			case 'A':{	
				R = alterar(R);			
			}break;
		}
	}while(l != 'S');
}
//FUNÇÃO PRINCIPAL DO PROGRAMA
int main(){
	//CRIA A ESTRUTURA DA ÁRVORE
	sRN *arvore;
	//INICIALIZA A ÁRVORE
	arvore = NULL;
	//CHAMA O MENU DO PROGRAMA
	menu(arvore);
}
//FONTES 
//SLIDES 53, 56 E 57 DO ARQUIVO (Aula 5 - EDP - Árvores Balanceadas Rubro-Negras - Exclusão - Novo)
//https://gist.github.com/VictorGarritano/5f894be162d39e9bdd5c
//https://gist.github.com/aagontuk/38b4070911391dd2806f
//https://www.programiz.com/dsa/red-black-tree
//LIVRO ALGORITMOS TEORIA E PRÁTICA 3ª EDIÇÃO AMERICANA (PDF FORNECIDO PELO EVALDO)
//CÓDIGO DE ÁRVORE BINARIA DE BUSCA FORNECIDO PELA PROFESSORA (ABB_Moodle)

