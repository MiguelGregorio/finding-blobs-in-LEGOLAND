#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pixel{
	int r;
	int g;
	int b;
	int flag;
}Pixel;
	
typedef struct imagem{
	char nome[50];
	int linhas;
	int colunas;
	Pixel **m;
}Imagem;

typedef struct zona{
	char nome[50];
	int altura;
	int largura;
	int n;
}Zona;

typedef struct pilha{
	int linha;
	int coluna;
	struct pilha* nseg;
}Pilha;


int menu(){
	int opcao;
	printf("\n");
	printf("*********Finding BLOBS in LEGOLAND**********************\n");
	printf("MENU\n");
	printf("****************************************************\n");
	printf("1 - Ler ficheiro\n");
	printf("2 - Pesquisa de conteudo\n");
	printf("0 - Sair\n");
	printf("****************************************************\n");
	printf("Introduza uma das opcoes:");
	scanf("%d", &opcao);
	printf("***************************************\n");
	return opcao;
}




int words(const char sentence[ ]){
    int counted = 0; // result

    // state:
    const char* it = sentence;
    int inword = 0;

    do switch(*it) {
        case '\0': 
        case ' ': case '\t': case '\n': case '\r': // TODO others?
            if (inword) { inword = 0; counted++; }
            break;
        default: inword = 1;
    } while(*it++);

    return counted;
}




Pilha* push(Pilha *p, int linha, int coluna){
	
	Pilha*np=(Pilha*)malloc(sizeof(Pilha));
	np->linha=linha;
	np->coluna=coluna;
	np->nseg=p;
}

Pilha* pop(Pilha **p){
	Pilha *r = (*p);
	(*p)= (*p)->nseg;
	return r;
}


Zona * flood(Pixel ***m, int linha, int coluna, int r, int g,int b, int d ){
	
	Pilha *pilha=NULL;
	Pilha *currPixel;
	
	push(pilha, linha, coluna);
	Zona *nv= (Zona*) malloc(sizeof(Zona));
	
	while(pilha!=NULL){
		
		currPixel=pop(&pilha);
	
		(*m)[linha][coluna].flag=1;
	
		//nv->n = (nv->n) +1 ;
		//nv->altura=( nv->altura + linha);//dividir
		//nv->largura=( nv->largura + coluna);
		
	
	
	
		if((((*m)[currPixel->linha-1][currPixel->coluna].r >= r-d) && ((*m)[currPixel->linha-1][currPixel->coluna].r <= r+d)) &&
			(((*m)[currPixel->linha-1][currPixel->coluna].g >= g-d) && ((*m)[currPixel->linha-1][currPixel->coluna].g <= g+d))&&
			(((*m)[currPixel->linha-1][currPixel->coluna].b >= b-d) && ((*m)[currPixel->linha-1][currPixel->coluna].b <= b+d)) && (*m)[currPixel->linha-1][currPixel->coluna].flag==0){
												
				pilha= push(pilha, (currPixel->linha)-1,currPixel->coluna);
												
		}
		
		if((((*m)[currPixel->linha+1][currPixel->coluna].r >= r-d) && ((*m)[currPixel->linha+1][currPixel->coluna].r <= r+d)) &&
			(((*m)[currPixel->linha+1][currPixel->coluna].g >= g-d) && ((*m)[currPixel->linha+1][currPixel->coluna].g <= g+d))&&
			(((*m)[currPixel->linha+1][currPixel->coluna].b >= b-d) && ((*m)[currPixel->linha+1][currPixel->coluna].b <= b+d)) && (*m)[currPixel->linha+1][currPixel->coluna].flag==0){
												
				pilha= push(pilha, (currPixel->linha)+1,currPixel->coluna);
												
		}
		
		if((((*m)[currPixel->linha][currPixel->coluna-1].r >= r-d) && ((*m)[currPixel->linha][currPixel->coluna-1].r <= r+d)) &&
			(((*m)[currPixel->linha][currPixel->coluna-1].g >= g-d) && ((*m)[currPixel->linha][currPixel->coluna-1].g <= g+d))&&
			(((*m)[currPixel->linha][currPixel->coluna-1].b >= b-d) && ((*m)[currPixel->linha][currPixel->coluna-1].b <= b+d)) && (*m)[currPixel->linha][currPixel->coluna-1].flag==0){
												
				pilha= push(pilha, currPixel->linha,(currPixel->coluna)-1);
												
		}
		
		if((((*m)[currPixel->linha][currPixel->coluna+1].r >= r-d) && ((*m)[currPixel->linha][currPixel->coluna+1].r <= r+d)) &&
			(((*m)[currPixel->linha][currPixel->coluna+1].g >= g-d) && ((*m)[currPixel->linha][currPixel->coluna+1].g <= g+d))&&
			(((*m)[currPixel->linha][currPixel->coluna+1].b >= b-d) && ((*m)[currPixel->linha][currPixel->coluna+1].b <= b+d)) && (*m)[currPixel->linha][currPixel->coluna+1].flag==0){
												
				pilha= push(pilha, currPixel->linha,(currPixel->coluna)+1);
				
												
		}
		
		
	
		
	}
	
		//nv->altura=( nv->altura)/nv->n;//dividir
		//nv->largura=( nv->largura)/nv->n;
		
		
		
	
	//nv->altura = (nv->altura)/nv->n;
	//nv->largura = (nv->largura)/nv->n;
	return(nv);
}



	



